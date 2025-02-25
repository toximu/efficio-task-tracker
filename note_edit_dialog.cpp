#include "note_edit_dialog.h"
#include <QDialog>
#include <QFile>
#include <QMenu>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QTextStream>
#include "./ui_note_edit_dialog.h"
#include "note_edit_dialog_styles.h"
#include "tags_dialog.h"

NoteEditDialog::NoteEditDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::NoteEditDialog), avatar_label(nullptr) {
    ui->setupUi(this);

    setFixedSize(700, 480);
    setStyleSheet(Ui::light_theme);
    ui->buttonsLayout->setAlignment(Qt::AlignLeft);

    connect(
        ui->saveButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_save_button_click
    );
    connect(
        ui->cancelButton, &QPushButton::clicked, this, &NoteEditDialog::reject
    );
    connect(
        ui->joinButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_join_button_click
    );
    connect(
        ui->addMembersButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_add_members_button_click
    );
    connect(ui->addDateButton, &QPushButton::clicked, this, [=]() {
        bool isVisible = ui->dateLabel->isVisible();
        ui->dateLabel->setVisible(!isVisible);
        ui->dateEdit->setVisible(!isVisible);
    });
    connect(
        ui->addTagsButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_add_tags_button_click
    );
}

NoteEditDialog::~NoteEditDialog() {
    delete ui;
}

void NoteEditDialog::on_save_button_click() {
    QString title = ui->titleLineEdit->text();
    QString content = ui->descriptionTextEdit->toPlainText();

    QString message =
        QString("Заголовок: %1\nСодержимое: %2").arg(title, content);
    QMessageBox::information(this, "Заметка сохранена", message);
}

void NoteEditDialog::on_join_button_click() {
    bool isJoined = ui->membersLabel->isVisible();

    if (!isJoined) {
        ui->membersLabel->setVisible(true);

        QPixmap pixmap(32, 32);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setBrush(Qt::black);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(0, 0, 32, 32);

        avatar_label = new QLabel(this);
        avatar_label->setPixmap(pixmap);
        avatar_label->setFixedSize(32, 32);
        ui->avatarsLayout->addWidget(avatar_label);

        ui->joinButton->setText("Покинуть");
    } else {
        ui->membersLabel->setVisible(false);

        if (avatar_label) {
            ui->avatarsLayout->removeWidget(avatar_label);
            delete avatar_label;
            avatar_label = nullptr;
        }

        ui->joinButton->setText("Присоединиться");
    }
}

void NoteEditDialog::on_add_members_button_click() {
    QMessageBox::information(this, "Ошибка", "Другие участники не найдены :(");
}

void NoteEditDialog::on_add_tags_button_click() {
    TagsDialog tags_dialog(selected_tags, this);
    if (tags_dialog.exec() == QDialog::Accepted) {
        selected_tags = tags_dialog.get_selected_tags();

        if (!ui->tagsLabel->isVisible()) {
            ui->tagsLabel->setVisible(true);
        }

        qDeleteAll(tag_labels);
        tag_labels.clear();

        for (const TagsDialog::Tag &tag : selected_tags) {
            QLabel *tag_label = new QLabel(tag.name, this);
            tag_label->setStyleSheet(QString("background-color: %1; "
                                             "color: white; "
                                             "padding: 9px 10px; "
                                             "border-radius: 5px; "
                                             "font-family: 'Arial'; "
                                             "font-size: 12px; "
                                             "font-weight: bold;"
                                             "width: 40px;"
                                             "height: 25px;")
                                         .arg(tag.color));
            ui->tagsLayout->addWidget(tag_label);
            tag_labels.append(tag_label);
        }
    }

    if (selected_tags.empty()) {
        ui->tagsLabel->setVisible(false);
    }
}
