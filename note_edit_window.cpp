#include "note_edit_window.h"
#include <QMessageBox>
#include "./ui_note_edit_window.h"

NoteEditWindow::NoteEditWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NoteEditWindow) {
    ui->setupUi(this);

    ui->centralwidget->setStyleSheet("background-color: #202020;");

    ui->titleLineEdit->setPlaceholderText("Заголовок");
    ui->titleLineEdit->setStyleSheet(
        "QLineEdit {"
        "    border-radius: 10px;"
        "    border: 1px"
        "    solid #131313;"
        "    background: #131313;"
        "    padding: 5px 10px;"
        "}"
        "QLineEdit::placeholder {"
        "    font-family: 'Century Gothic';"
        "    font-size: 14px;"
        "    color: #898989;"
        "}"
    );

    ui->contentTextEdit->setStyleSheet(
        "QTextEdit {"
        "    border-radius: 10px;"
        "    border: 5px"
        "    solid #131313;"
        "    background: #131313;"
        "    padding: 3px 3px;"
        "}"
        );

    ui->tagsLineEdit->setPlaceholderText("Теги");
    ui->tagsLineEdit->setStyleSheet(
        "QLineEdit {"
        "    border-radius: 10px;"
        "    border: 1px"
        "    solid #131313;"
        "    background: #131313;"
        "    padding: 5px 10px;"
        "}"
        "QLineEdit::placeholder {"
        "    font-family: 'Century Gothic';"
        "    font-size: 14px;"
        "    color: #898989;"
        "}"
        );

    ui->saveButton->setStyleSheet(
        "QPushButton {"
        "    font-family: 'Century Gothic';"
        "    border-radius: 10px;"
        "    background-color: #fea36b;"
        "    color: black;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #d58745;"
        "}"
    );

    connect(
        ui->saveButton, &QPushButton::clicked, this,
        &::NoteEditWindow::on_save_button_click
    );
}

NoteEditWindow::~NoteEditWindow() {
    delete ui;
}

void NoteEditWindow::on_save_button_click() {
    QString title = ui->titleLineEdit->text();
    QString content = ui->contentTextEdit->toPlainText();
    QString tags = ui->tagsLineEdit->text();

    QString message = QString("Заголовок: %1\nСодержимое: %2\nТеги: %3")
                          .arg(title, content, tags);
    QMessageBox::information(this, "Заметка сохранена", message);
}
