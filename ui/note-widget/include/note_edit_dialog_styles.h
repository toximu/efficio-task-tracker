#ifndef NOTE_EDIT_DIALOG_STYLES_H
#define NOTE_EDIT_DIALOG_STYLES_H

#include <ui_note_edit_dialog.h>

namespace Ui {
QString note_edit_dialog_light_autumn_theme = R"(
    QDialog {
        background-color: #f5f5f5;
    }

    /* Заголовок и название проекта */

    QLineEdit#titleLineEdit {
        font-family: 'Arial';
        font-size: 25px;
        font-weight: bold;
        color: #089083;
        border: none;
        padding: 0;
        background: transparent;
    }

    QLabel#projectNameLabel {
        font-family: 'Arial';
        font-size: 13px;
        color: #727272;
        padding: 1px;
    }

    /* Описание заметки */

    QLabel#descriptionLabel {
        font-family: 'Arial';
        font-size: 18px;
        font-weight: bold;
        color: black;
    }

    QTextEdit#descriptionTextEdit {
        border-radius: 10px;
        border: 1px solid #ffffff;
        background: #ffffff;
        color: black;
        padding: 5px;
    }

    QTextEdit#descriptionTextEdit::placeholder {
        color: #727272;
    }

    /* Основные кнопки */

    QHBoxLayout#buttonsLayout {
        align: left;
    }

    QPushButton#saveButton {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #fea36b;
        color: white;
        padding: 5px 10px;
    }

    QPushButton#saveButton:hover {
        background-color: #d58745;
    }

    QPushButton#cancelButton {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: white;
        color: #fea36b;
        padding: 5px 10px;
    }

    QPushButton#cancelButton:hover {
        background-color: #dadada;
    }

    /* Боковое меню */

    QPushButton#joinButton,
    QPushButton#addMembersButton,
    QPushButton#addDateButton,
    QPushButton#addTagsButton {
        font-family: 'Arial';
        background-color: #089083;
        color: #ffffff;
        padding: 5px 10px;
        border-radius: 10px;
        font-weight: bold;
        text-align: left;
    }

    QPushButton#joinButton:hover,
    QPushButton#addMembersButton:hover,
    QPushButton#addDateButton:hover,
    QPushButton#addTagsButton:hover {
        background-color: #01635d;
    }

    QLabel#sidePanelLabel,
    QLabel#sidePanelLabel_2 {
        font-family: 'Arial';
        font-size: 14px;
        font-weight: bold;
        color: #727272;
    }

    QLabel#membersLabel,
    QLabel#tagsLabel,
    QLabel#dateLabel {
        color: #727272;
    }

    /* Дополнительные элементы заметки */

    QDateEdit#dateEdit {
        font-family: 'Arial';
        border-radius: 5px;
        background-color: #ffdda2;
        color: #050505;
        padding: 5px 5px;
        border: none;
        width: 70px;
        height: 22px;
        text-align: center;
        font-weight: bold;
    }
    QDateEdit#dateEdit::drop-down {
        border: none;
        width: 20px;
    }

    /* Окно с сообщением */

    QMessageBox {
        background-color: #ffffff;
    }

    QMessageBox QLabel {
        font-family: 'Arial';
        font-size: 14px;
        color: #000000;
    }

    QMessageBox QPushButton {
        font-family: 'Arial';
        font-size: 13px;
        font-weight: bold;
        color: white;
        background-color: #fea36b;
        border-radius: 10px;
        padding: 5px 15px;
        min-width: 60px;
        min-height: 25px;
    }

    QMessageBox QPushButton:hover {
        background-color: #d58745;
        color: white;
    }

    QMessageBox QPushButton:pressed {
        background-color: #d58745;
        border-color: #d58745;
    }
        
    QPushButton#switch_theme {
        background-color: transparent;
        border-radius: 9px;
        border: 2px solid #089083;
        padding: 5px;
    }
    QPushButton::hover#switch_theme {
        background-color: #089083;
    }
    QPushButton::pressed#switch_theme {
        background-color:rgb(7, 110, 100);
    }
)";

}  // namespace Ui

#endif  // NOTE_EDIT_DIALOG_STYLES_H