#include "note_edit_dialog.h"
#include <QDialog>
#include <QFile>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QTextStream>
#include "./ui_note_edit_dialog.h"
#include "note_edit_dialog_styles.h"
#include "tags_dialog.h"

NoteEditDialog::NoteEditDialog(QWidget *parent, std::unique_ptr<Note> note)
    : QDialog(parent),
      ui_(new Ui::NoteEditDialog),
      avatar_label_(nullptr),
      note_(std::move(note)) {
    ui_->setupUi(this);

    setFixedSize(700, 480);
    setStyleSheet(Ui::light_theme);
    ui_->buttonsLayout->setAlignment(Qt::AlignLeft);

    connect(
        ui_->saveButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_save_button_click
    );
    connect(
        ui_->cancelButton, &QPushButton::clicked, this, &NoteEditDialog::reject
    );
    connect(
        ui_->joinButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_join_button_click
    );
    connect(
        ui_->addMembersButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_add_members_button_click
    );
    connect(ui_->addDateButton, &QPushButton::clicked, this, [=]() {
        const bool is_visible = ui_->dateLabel->isVisible();
        ui_->dateLabel->setVisible(!is_visible);
        ui_->dateEdit->setVisible(!is_visible);
    });
    connect(
        ui_->addTagsButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_add_tags_button_click
    );
}

NoteEditDialog::~NoteEditDialog() {
    delete ui_;
}

void NoteEditDialog::on_save_button_click() {
    QString title = ui_->titleLineEdit->text();
    QString content = ui_->descriptionTextEdit->toPlainText();

    const QString message =
        QString("Заголовок: %1\nСодержимое: %2").arg(title, content);

    if (try_save_note()) {
        QMessageBox::information(this, "Заметка сохранена", message);
    }
}

void NoteEditDialog::on_join_button_click() {
    const bool is_joined = ui_->membersLabel->isVisible();

    if (!is_joined) {
        ui_->membersLabel->setVisible(true);

        QPixmap pixmap(32, 32);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setBrush(Qt::black);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(0, 0, 32, 32);

        avatar_label_ = std::make_unique<QLabel>(this);
        avatar_label_->setPixmap(pixmap);
        avatar_label_->setFixedSize(32, 32);
        ui_->avatarsLayout->addWidget(avatar_label_.get());

        ui_->joinButton->setText("Покинуть");
    } else {
        ui_->membersLabel->setVisible(false);

        if (avatar_label_) {
            ui_->avatarsLayout->removeWidget(avatar_label_.get());
            avatar_label_.reset();
        }

        ui_->joinButton->setText("Присоединиться");
    }
}

void NoteEditDialog::on_add_members_button_click() {
    QMessageBox::information(this, "Ошибка", "Другие участники не найдены :(");
}

void NoteEditDialog::on_add_tags_button_click() {
    TagsDialog tags_dialog(selected_tags_, this);
    if (tags_dialog.exec() == Accepted) {
        selected_tags_ = tags_dialog.get_selected_tags();

        if (!ui_->tagsLabel->isVisible()) {
            ui_->tagsLabel->setVisible(true);
        }

        tag_labels_.clear();

        for (const auto &[is_checked, color, name] : selected_tags_) {
            auto tag_label = std::make_unique<QLabel>(name, this);
            tag_label->setStyleSheet(QString("background-color: %1; "
                                             "color: white; "
                                             "padding: 9px 10px; "
                                             "border-radius: 5px; "
                                             "font-family: 'Arial'; "
                                             "font-size: 12px; "
                                             "font-weight: bold;"
                                             "width: 40px;"
                                             "height: 25px;")
                                         .arg(color));
            ui_->tagsLayout->addWidget(tag_label.get());
            tag_labels_.push_back(std::move(tag_label));
        }
    }

    if (selected_tags_.empty()) {
        ui_->tagsLabel->setVisible(false);
    }
}

bool NoteEditDialog::try_save_note() const {
    note_->set_title(ui_->titleLineEdit->text().toStdString());
    note_->set_text(ui_->descriptionTextEdit->toPlainText().toStdString());
    return NoteDao::create_note(*note_);
}
