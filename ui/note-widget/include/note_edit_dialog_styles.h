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
        border-radius: 5px;
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
       width: 20px;          
        height: 20px;        
        min-width: 20px;      
        min-height: 20px;
        max-width: 20px;     
        max-height: 20px;
        background-color: transparent;
        border-radius: 7px;
        border: 2px solid #089083;
        padding: 0;
    }
    QPushButton::hover#switch_theme {
        background-color: #089083;
    }
    QPushButton::pressed#switch_theme {
        background-color:rgb(7, 110, 100);
    }
)";

QString note_edit_dialog_dark_autumn_theme = R"(
    QDialog {
        background-color: #202020;
    }

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

    QLabel#descriptionLabel {
        font-family: 'Arial';
        font-size: 18px;
        font-weight: bold;
        color:rgb(202, 202, 202);
    }

    QTextEdit#descriptionTextEdit {
        border-radius: 10px;
        border: 1px solid #000000;
        background: #000000;
        color: #727272;
        padding: 5px;
    }

    QHBoxLayout#buttonsLayout {
        align: left;
    }

    QPushButton#saveButton {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #fea36b;
        color: #263238;
        padding: 5px 10px;
    }

    QPushButton#saveButton:hover {
        background-color: #d58745;
    }

    QPushButton#cancelButton {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #089083;
        color: white;
        padding: 5px 10px;
    }

    QPushButton#cancelButton:hover {
        background-color: #01635d;
    }

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

    QMessageBox {
        background-color: #263238;
    }

    QMessageBox QLabel {
        font-family: 'Arial';
        font-size: 14px;
        color: #ffffff;
    }

    QMessageBox QPushButton {
        font-family: 'Arial';
        font-size: 13px;
        font-weight: bold;
        color: #263238;
        background-color: #fea36b;
        border-radius: 10px;
        padding: 5px 15px;
        min-width: 60px;
        min-height: 25px;
    }

    QMessageBox QPushButton:hover {
        background-color: #d58745;
    }

    QMessageBox QPushButton:pressed {
        background-color: #d58745;
        border-color: #d58745;
    }
        
    QPushButton#switch_theme {
        width: 20px;          
        height: 20px;        
        min-width: 20px;      
        min-height: 20px;
        max-width: 20px;     
        max-height: 20px;
        background-color: transparent;
        border-radius: 7px;
        border: 2px solid #089083;
        padding: 0;
    }
    QPushButton::hover#switch_theme {
        background-color: #089083;
    }
    QPushButton::pressed#switch_theme {
        background-color:rgb(7, 110, 100);
    }
)";

QString note_edit_dialog_light_purple_theme = R"(
    QDialog {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,
            stop:0 #9882B9, stop:0.5 rgb(176, 157, 205), stop:1 rgb(125, 109, 148));
    }

    QLineEdit#titleLineEdit {
        font-family: 'Arial';
        font-size: 25px;
        font-weight: bold;
        color: rgb(42, 10, 25);
        border: none;
        padding: 0;
        background: transparent;
    }

    QLabel#projectNameLabel {
        font-family: 'Arial';
        font-size: 13px;
        color: rgb(218, 207, 235);
        padding: 1px;
    }

    QLabel#descriptionLabel {
        font-family: 'Arial';
        font-size: 18px;
        font-weight: bold;
        color: rgb(42, 10, 25);
    }

    QTextEdit#descriptionTextEdit {
        border-radius: 10px;
        border: 1px solid rgb(221, 210, 238);
        background: rgb(221, 210, 238);
        color: #221932;
        padding: 5px;
    }

    QHBoxLayout#buttonsLayout {
        align: left;
    }

    QPushButton#saveButton {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #722548;
        color: rgb(206, 193, 224);
        padding: 5px 10px;
    }

    QPushButton#saveButton:hover {
        background-color: rgb(98, 27, 59);
    }

    QPushButton#cancelButton {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: rgb(42, 10, 25);
        color: rgb(218, 207, 235);
        padding: 5px 10px;
    }

    QPushButton#cancelButton:hover {
        background-color: rgb(27, 6, 16);
    }

    QPushButton#joinButton,
    QPushButton#addMembersButton,
    QPushButton#addDateButton,
    QPushButton#addTagsButton {
        font-family: 'Arial';
        background-color: rgb(42, 10, 25);
        color: rgb(218, 207, 235);
        padding: 5px 10px;
        border-radius: 10px;
        font-weight: bold;
        text-align: left;
    }

    QPushButton#joinButton:hover,
    QPushButton#addMembersButton:hover,
    QPushButton#addDateButton:hover,
    QPushButton#addTagsButton:hover {
        background-color: rgb(27, 6, 16);
    }

    QLabel#sidePanelLabel,
    QLabel#sidePanelLabel_2 {
        font-family: 'Arial';
        font-size: 14px;
        font-weight: bold;
        color: rgb(218, 207, 235);
    }

    QLabel#membersLabel,
    QLabel#tagsLabel,
    QLabel#dateLabel {
        color: rgb(218, 207, 235);
    }

    QDateEdit#dateEdit {
        font-family: 'Arial';
        border-radius: 5px;
        background-color: #C98BB8;
        color: rgb(42, 10, 25);
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

    QMessageBox {
        background-color: rgb(221, 210, 238);
    }

    QMessageBox QLabel {
        font-family: 'Arial';
        font-size: 14px;
        color: #221932;
    }

    QMessageBox QPushButton {
        font-family: 'Arial';
        font-size: 13px;
        font-weight: bold;
        color: rgb(206, 193, 224);
        background-color: #722548;
        border-radius: 10px;
        padding: 5px 15px;
        min-width: 60px;
        min-height: 25px;
    }

    QMessageBox QPushButton:hover {
        background-color: rgb(98, 27, 59);
    }

    QMessageBox QPushButton:pressed {
        background-color: rgb(98, 27, 59);
        border-color: rgb(98, 27, 59);
    }
        
    QPushButton#switch_theme {
       width: 20px;          
        height: 20px;        
        min-width: 20px;      
        min-height: 20px;
        max-width: 20px;     
        max-height: 20px;
        background-color: transparent;
        border-radius: 7px;
        border: 2px solid rgb(42, 10, 25);
        padding: 0;
    }
    QPushButton::hover#switch_theme {
        background-color: rgb(42, 10, 25);
    }
    QPushButton::pressed#switch_theme {
        background-color:rgb(26, 6, 15);
    }
)";

QString note_edit_dialog_dark_purple_theme = R"(
    QDialog {
        background-color:rgb(9, 6, 10);
    }

    QLineEdit#titleLineEdit {
        font-family: 'Arial';
        font-size: 25px;
        font-weight: bold;
        color: #9882B9;
        border: none;
        padding: 0;
        background: transparent;
    }

    QLabel#projectNameLabel {
        font-family: 'Arial';
        font-size: 13px;
        color: rgb(176, 170, 185);
        padding: 1px;
    }

    QLabel#descriptionLabel {
        font-family: 'Arial';
        font-size: 18px;
        font-weight: bold;
        color: #9882B9;
    }

    QTextEdit#descriptionTextEdit {
        border-radius: 10px;
        border: 1px solid #221932;
        background: #221932;
        color: rgb(176, 170, 185);
        padding: 5px;
    }

    QHBoxLayout#buttonsLayout {
        align: left;
    }

    QPushButton#saveButton {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #722548;
        color: #060407;
        padding: 5px 10px;
    }

    QPushButton#saveButton:hover {
        background-color: rgb(98, 27, 59);
    }

    QPushButton#cancelButton {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: rgb(42, 10, 25);
        color: #9882B9;
        padding: 5px 10px;
    }

    QPushButton#cancelButton:hover {
        background-color: rgb(27, 6, 16);
    }

    QPushButton#joinButton,
    QPushButton#addMembersButton,
    QPushButton#addDateButton,
    QPushButton#addTagsButton {
        font-family: 'Arial';
        background-color: rgb(42, 10, 25);
        color: #9882B9;
        padding: 5px 10px;
        border-radius: 10px;
        font-weight: bold;
        text-align: left;
    }

    QPushButton#joinButton:hover,
    QPushButton#addMembersButton:hover,
    QPushButton#addDateButton:hover,
    QPushButton#addTagsButton:hover {
        background-color: rgb(27, 6, 16);
    }

    QLabel#sidePanelLabel,
    QLabel#sidePanelLabel_2 {
        font-family: 'Arial';
        font-size: 14px;
        font-weight: bold;
        color: #9882B9;
    }

    QLabel#membersLabel,
    QLabel#tagsLabel,
    QLabel#dateLabel {
        color: #9882B9;
    }

    QDateEdit#dateEdit {
        font-family: 'Arial';
        border-radius: 5px;
        background-color: rgb(113, 97, 137);
        color: #221932;
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

    QMessageBox {
        background-color: #221932;
    }

    QMessageBox QLabel {
        font-family: 'Arial';
        font-size: 14px;
        color: #9882B9;
    }

    QMessageBox QPushButton {
        font-family: 'Arial';
        font-size: 13px;
        font-weight: bold;
        color: #060407;
        background-color: #722548;
        border-radius: 10px;
        padding: 5px 15px;
        min-width: 60px;
        min-height: 25px;
    }

    QMessageBox QPushButton:hover {
        background-color: rgb(98, 27, 59);
    }

    QMessageBox QPushButton:pressed {
        background-color: rgb(98, 27, 59);
        border-color: rgb(98, 27, 59);
    }
        
    QPushButton#switch_theme {
       width: 20px;          
        height: 20px;        
        min-width: 20px;      
        min-height: 20px;
        max-width: 20px;     
        max-height: 20px;
        background-color: transparent;
        border-radius: 7px;
        border: 2px solid #9882B9;
        padding: 0;
    }
    QPushButton::hover#switch_theme {
        background-color: #9882B9;
    }
    QPushButton::pressed#switch_theme {
        background-color:rgb(116, 99, 140);
    }
)";

QString note_edit_dialog_blue_theme = R"(
    QDialog {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,
            stop:0 #173C4C, stop:0.5 rgb(30, 66, 65), stop:1 #07142B);
    }

    QLineEdit#titleLineEdit {
        font-family: 'Arial';
        font-size: 25px;
        font-weight: bold;
        color: #BDD1BD;
        border: none;
        padding: 0;
        background: transparent;
    }

    QLabel#projectNameLabel {
        font-family: 'Arial';
        font-size: 13px;
        color: #BDD1BD;
        padding: 1px;
    }

    QLabel#descriptionLabel {
        font-family: 'Arial';
        font-size: 18px;
        font-weight: bold;
        color: #BDD1BD;
    }

    QTextEdit#descriptionTextEdit {
        border-radius: 10px;
        border: 1px solid #568F7C;
        background: #07142B;
        color: #BDD1BD;
        padding: 5px;
    }

    QHBoxLayout#buttonsLayout {
        align: left;
    }

    QPushButton#saveButton {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #568F7C;
        color: #BDD1BD;
        padding: 5px 10px;
        border: none;
        font-weight: bold;
    }

    QPushButton#saveButton:hover {
        background-color: #326D6C;
    }

    QPushButton#saveButton:pressed {
        background-color: #07142B;
    }

    QPushButton#cancelButton {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #326D6C;
        color: #BDD1BD;
        padding: 5px 10px;
        border: 1px solid #568F7C;
    }

    QPushButton#cancelButton:hover {
        background-color: #568F7C;
        color: #07142B;
    }

    QPushButton#joinButton,
    QPushButton#addMembersButton,
    QPushButton#addDateButton,
    QPushButton#addTagsButton {
        font-family: 'Arial';
        background-color: #326D6C;
        color: #BDD1BD;
        padding: 5px 10px;
        border-radius: 10px;
        font-weight: bold;
        text-align: left;
    }

    QPushButton#joinButton:hover,
    QPushButton#addMembersButton:hover,
    QPushButton#addDateButton:hover,
    QPushButton#addTagsButton:hover {
        background-color: #568F7C;
        color: #07142B;
    }

    QLabel#sidePanelLabel,
    QLabel#sidePanelLabel_2 {
        font-family: 'Arial';
        font-size: 14px;
        font-weight: bold;
        color: #BDD1BD;
    }

    QLabel#membersLabel,
    QLabel#tagsLabel,
    QLabel#dateLabel {
        color: #BDD1BD;
    }

    QDateEdit#dateEdit {
        font-family: 'Arial';
        border-radius: 5px;
        background-color: rgb(61, 104, 122);
        color: #BDD1BD;
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

    QMessageBox {
        background-color: #07142B;
    }

    QMessageBox QLabel {
        font-family: 'Arial';
        font-size: 14px;
        color: #BDD1BD;
    }

    QMessageBox QPushButton {
        font-family: 'Arial';
        font-size: 13px;
        font-weight: bold;
        color: #BDD1BD;
        background-color: #568F7C;
        border-radius: 10px;
        padding: 5px 15px;
        min-width: 60px;
        min-height: 25px;
    }

    QMessageBox QPushButton:hover {
        background-color: #326D6C;
    }

    QMessageBox QPushButton:pressed {
        background-color: #07142B;
        border-color: #07142B;
    }
        
    QPushButton#switch_theme {
       width: 20px;          
        height: 20px;        
        min-width: 20px;      
        min-height: 20px;
        max-width: 20px;     
        max-height: 20px;
        background-color: transparent;
        border-radius: 7px;
        border: 2px solid #326D6C;
        padding: 0;
    }
    QPushButton::hover#switch_theme {
        background-color: #326D6C;
    }
    QPushButton::pressed#switch_theme {
        background-color:rgb(33, 74, 74);
    }
)";

}  // namespace Ui

#endif  // NOTE_EDIT_DIALOG_STYLES_H