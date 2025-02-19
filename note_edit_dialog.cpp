#include "note_edit_dialog.h"
#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include "./ui_note_edit_dialog.h"
#include "style_sheet.h"

NoteEditDialog::NoteEditDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::NoteEditDialog) {
    ui->setupUi(this);

    setFixedSize(700, 500);
    setStyleSheet(Ui::style_sheet);

    connect(
        ui->saveButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_save_button_click
    );
    connect(
        ui->cancelButton, &QPushButton::clicked, this, &NoteEditDialog::reject
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
