#ifndef STYLE_SHEET_H
#define STYLE_SHEET_H

#include <ui_note_edit_dialog.h>

namespace Ui {
QString style_sheet = R"(
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
        color: #898989;
        padding: 1px;
    }

    QLabel#descriptionLabel {
        font-family: 'Arial';
        font-size: 18px;
        font-weight: bold;
        color: white;
    }

    QTextEdit#descriptionTextEdit {
        border-radius: 10px;
        border: 1px solid #131313;
        background: #131313;
        color: white;
        padding: 5px;
    }

    QTextEdit#descriptionTextEdit::placeholder {
        color: #898989;
    }

    QPushButton#saveButton {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #fea36b;
        color: black;
        padding: 5px 10px;
    }

    QPushButton#saveButton:hover {
        background-color: #d58745;
    }

    QPushButton#cancelButton {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #131313;
        color: #fea36b;
        padding: 5px 10px;
    }

    QPushButton#cancelButton:hover {
        background-color: black;
    }

    QPushButton#joinButton,
    QPushButton#membersButton,
    QPushButton#checklistButton,
    QPushButton#datesButton,
    QPushButton#attachmentButton,
    QPushButton#tagsButton {
        font-family: 'Arial';
        background-color: #131313;
        color: #fea36b;
        padding: 5px 10px;
        border-radius: 5px;
        font-weight: bold;
        text-align: left;
    }

    QPushButton#joinButton:hover,
    QPushButton#membersButton:hover,
    QPushButton#checklistButton:hover,
    QPushButton#datesButton:hover,
    QPushButton#attachmentButton:hover,
    QPushButton#tagsButton:hover {
        background-color: black;
    }

    QLabel#sidePanelLabel,
    QLabel#sidePanelLabel_2 {
        font-family: 'Arial';
        font-size: 14px;
        font-weight: bold;
        color: #898989;
    }
)";

}  // namespace Ui

#endif  // STYLE_SHEET_H
