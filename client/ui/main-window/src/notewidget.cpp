#include "notewidget.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include "language_manager.h"
#include "model-proto/model.pb.h"
#include "note_edit_dialog.h"
#include "style_manager.h"

using Efficio_proto::Note;

namespace Ui {
NoteWidget::NoteWidget(
    ClientImplementation *client,
    QWidget *parent,
    const Note *model_note,
    const Note::Type &type,
    QListWidgetItem *p
)
    : client_(client),
      QWidget(parent),
      model_note_(model_note),
      main_layout_(new QVBoxLayout(this)),
      open_button_(new QPushButton(tr("Открыть"))),
      delete_button_(new QPushButton(tr("Удалить"))),
      type_(type),
      project_(p) {
    this->setObjectName("NoteWidget");
    this->setMinimumWidth(100);
    this->setFixedHeight(100);

    title_label_ =
        new QLabel(QString::fromStdString(model_note_->title()), this);

    title_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 15px;");

    main_layout_->addWidget(title_label_);
    main_layout_->addLayout(tags_layout_);
    update_tags();

    // title_label_->setWordWrap(false);

    QHBoxLayout *buttons_layout = new QHBoxLayout;

    buttons_layout->addWidget(open_button_);
    buttons_layout->addWidget(delete_button_);

    if (type_.value() == Note::Type::deleted) {
        delete_button_->setText("Восстановить");
    }

    main_layout_->addLayout(buttons_layout);

    connect(
        open_button_, &QPushButton::clicked, this, &NoteWidget::open_note_window
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

void NoteWidget::handle_language_changed(std::string new_language) {
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

void NoteWidget::handle_font_size_changed(std::string font_size_) {
    QString font_rule;
    if (font_size_ == "small") {
        title_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 13px;");
    } else if (font_size_ == "medium") {
        title_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 15px;");
    } else if (font_size_ == "big") {
        title_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 17px;");
    }
}

void NoteWidget::open_note_window() const {
    auto dialog = new ::NoteEditDialog(
        client_, dynamic_cast<ProjectItem *>(project_)->project_->title(),
        const_cast<QWidget *>(qobject_cast<const QWidget *>(this)),
        const_cast<Note *>(model_note_)
    );
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
    title_label_->setText(QString::fromStdString(model_note_->title()));
    main_layout_->update();
}

void NoteWidget::change_type(Note::Type::States new_type) {
    type_.set_value(new_type);
    handle_language_changed(LanguageManager::instance()->current_language());
    main_layout_->update();
    emit change_type_requested(this->project_);
}

void NoteWidget::delete_note() {
    if (type_.value() == Note::Type::deleted) {
        this->change_type(Note::Type::actual);
    } else {
        this->change_type(Note::Type::deleted);
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

void NoteWidget::good_resize() {
    setMaximumWidth(reinterpret_cast<QWidget *>(parent())->width() / 3);
}

}  // namespace Ui