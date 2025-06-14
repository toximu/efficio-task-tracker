#include "notewidget.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include "language_manager.h"
#include "model-proto/model.pb.h"
#include "note_edit_dialog.h"
#include "style_manager.h"
#include <QIcon>
#include <QPainter>

using Efficio_proto::Note;

namespace Ui {
NoteWidget::NoteWidget(
    ClientImplementation *client,
    QWidget *parent,
    Note *model_note,
    const Note::Type &type,
    QListWidgetItem *p
)
    : client_(client),
      QWidget(parent),
      model_note_(model_note),
      main_layout_(new QVBoxLayout(this)),
      open_button_(new QPushButton(tr("Открыть"))),
      tags_layout_(new QHBoxLayout(this)),
      delete_button_(new QPushButton(tr("Удалить"))),
      complete_button_(new QPushButton()),
      type_(type),
      project_(p) {
    this->setObjectName("NoteWidget");
    this->setMinimumWidth(100);
    this->setFixedHeight(100);

    title_label_ =
        new QLabel(QString::fromStdString(model_note_->title()), this);

    title_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 13px;");

    main_layout_->addWidget(title_label_);
    main_layout_->addLayout(tags_layout_);
    update_tags();

    // title_label_->setWordWrap(false);

    QHBoxLayout *buttons_layout = new QHBoxLayout;

    buttons_layout->addWidget(open_button_);
    buttons_layout->addWidget(delete_button_);

    if (type_.value() == Note::Type::completed) {
        buttons_layout->addWidget(complete_button_);
        complete_button_->setStyleSheet(
            "QPushButton {"
            "   border-radius: 7px;"
            "   min-width: 13px; "
            "   min-height: 13px; "
            "   max-width: 13px; "
            "   max-height: 13px; "
            "   border: 2px solid #089083;"
            "   background-color: #089083;"
            "}"
            "QPushButton:hover {"
            "   background-color: #089083;"
            "}"
        );
    } else if (type_.value() == Note::Type::actual) {
        buttons_layout->addWidget(complete_button_);
        complete_button_->setStyleSheet(
            "QPushButton {"
            "   border-radius: 7px;"
            "   min-width: 13px; "
            "   min-height: 13px; "
            "   max-width: 13px; "
            "   max-height: 13px; "
            "   border: 2px solid #089083;"
            "   background-color: transparent;"
            "}"
            "QPushButton:hover {"
            "   background-color: #089083; "
            "}"
        );
    } else if (type_.value() == Note::Type::deleted) {
        delete_button_->setText("Восстановить");
    }

    QPixmap checkIcon(16, 16);
    checkIcon.fill(Qt::transparent);
    QPainter painter(&checkIcon);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black, 2);
    painter.setPen(pen);
    painter.drawLine(4, 8, 7, 11);
    painter.drawLine(7, 11, 12, 4);
    complete_button_->setIcon(QIcon(checkIcon));
    complete_button_->setIconSize(QSize(16, 16));

    main_layout_->addLayout(buttons_layout);

    connect(
        open_button_, &QPushButton::clicked, this, &NoteWidget::open_note_window
    );
    connect(
        complete_button_, &QPushButton::clicked, this, &NoteWidget::complete_note
    );
    connect(
        delete_button_, &QPushButton::clicked, this, &NoteWidget::delete_note
    );
    connect(
        StyleManager::instance(), &StyleManager::font_size_changed, this,
        &NoteWidget::handle_font_size_changed
    );
    this->setLayout(main_layout_);
    this->setAttribute(Qt::WA_StyledBackground);
    connect(
        LanguageManager::instance(), &LanguageManager::language_changed, this,
        &NoteWidget::handle_language_changed
    );
    handle_language_changed(LanguageManager::instance()->current_language());
    handle_font_size_changed(StyleManager::instance()->current_font_size());
}

void NoteWidget::good_resize() {
    setMaximumWidth(reinterpret_cast<QWidget *>(parent())->width() / 3);
}

void NoteWidget::handle_language_changed(const std::string &new_language) {
    if (new_language == "RU") {
        open_button_->setText(tr("Открыть"));
        if (title_label_->text() == "Empty note") {
            title_label_->setText("Пустая заметка");
        }
        if (type_.value() == Note::Type::deleted) {
            delete_button_->setText("Восстановить");
        } else {
            delete_button_->setText("Удалить");
        }
    } else if (new_language == "EN") {
        open_button_->setText(tr("Open"));
        if (title_label_->text() == "Пустая заметка") {
            title_label_->setText("Empty note");
        }
        if (type_.value() == Note::Type::deleted) {
            delete_button_->setText("Восстановить");
        } else {
            delete_button_->setText("Удалить");
        }
    }
}

void NoteWidget::handle_font_size_changed(const std::string &font_size_) {
    QString font_rule;
    if (font_size_ == "small") {
        title_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 13px;");
    } else if (font_size_ == "medium") {
        title_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 13px;");
    } else if (font_size_ == "big") {
        title_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 17px;");
    }
}

void NoteWidget::open_note_window() {
    client_->try_fetch_note(model_note_);
    auto dialog = new ::NoteEditDialog(
        client_, dynamic_cast<ProjectItem *>(project_)->project_->title(),
        const_cast<QWidget *>(qobject_cast<const QWidget *>(this)),
        const_cast<Note *>(model_note_)
    );
    client_->try_update_note(model_note_);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
    update_tags();
    title_label_->setText(QString::fromStdString(model_note_->title()));
    main_layout_->update();
}

void NoteWidget::change_type(Note::Type::States new_type) {
    auto old_type = type_.value();
    type_.set_value(new_type);
    model_note_->mutable_type()->set_value(new_type);
    handle_language_changed(LanguageManager::instance()->current_language());
    if (type_.value() == Note::Type::completed) {
        complete_button_->setStyleSheet(
            "QPushButton {"
            "   border-radius: 7px;"
            "   min-width: 13px; "
            "   min-height: 13px; "
            "   max-width: 13px; "
            "   max-height: 13px; "
            "   border: 2px solid #089083;"
            "   background-color: #089083;"
            "}"
            "QPushButton:hover {"
            "   background-color: #089083;"
            "}"
        );
    } else if (type_.value() == Note::Type::actual) {
        complete_button_->setStyleSheet(
            "QPushButton {"
            "   border-radius: 7px;"
            "   min-width: 13px; "
            "   min-height: 13px; "
            "   max-width: 13px; "
            "   max-height: 13px; "
            "   border: 2px solid #089083;"
            "   background-color: transparent;"
            "}"
            "QPushButton:hover {"
            "   background-color: #089083;"
            "}"
        );
    }
    client_->try_update_note(model_note_);
    main_layout_->update();
    emit change_type_requested(this->project_, old_type, new_type);
}

void NoteWidget::delete_note() {
    if (type_.value() == Note::Type::deleted) {
        this->change_type(Note::Type::actual);
    } else {
        this->change_type(Note::Type::deleted);
    }
}

void NoteWidget::complete_note() {
    if (type_.value() == Note::Type::completed) {
        this->change_type(Note::Type::actual);
    } else {
        this->change_type(Note::Type::completed);
    }
}

QListWidgetItem *NoteWidget::get_project() const {
    return this->project_;
}

void NoteWidget::update_tags() {
    for (auto tag : tag_labels_) {
        tags_layout_->removeWidget(tag);
        delete tag;
    }
    tag_labels_.clear();

    for (auto tag : model_note_->tags()) {
        QLabel *tag_label = new QLabel(this);
        tag_label->setText(tag.text().c_str());
        tag_label->setStyleSheet(
            ::NoteEditDialog::create_tag_style_sheet(tag.color())
        );
        tag_label->resize(tag_label->sizeHint());
        tag_labels_.push_back(tag_label);
        tags_layout_->addWidget(tag_label);
    }
}

}  // namespace Ui