#pragma once

#include "ui_registration_window.h"

namespace Ui {
QString registration_window_dark_theme = R"(
    QWidget {
        background-color: #202020;
    }

    QLabel {
        font-family: 'Arial';
        font-size: 13px;
        color: #089083;
        padding: 1px;
    }

    QPushButton#pushRegistration {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #fea36b;
        color: black;
        padding: 5px 10px;
    }

    QPushButton#switchMode {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #131313;
        color: #fea36b;
        padding: 5px 10px;
    }

    QPushButton#pushRegistration:hover {
        background-color: #d58745;
    }

    QPushButton#switchMode:hover {
        background-color: black;
    }

    QLineEdit {
        border-radius: 10px;
        border: 1px solid #131313;
        background: #131313;
        color: white;
        padding: 5px;
    }

    QLineEdit::placeholder {
        color: #898989;
    }
)";

QString registration_window_light_theme = R"(
    QWidget {
        background-color: #f5f5f5;
    }

    QLabel {
        font-family: 'Arial';
        font-size: 13px;
        color: #089083;
        padding: 1px;
    }

    QPushButton#pushRegistration {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #fea36b;
        color: white;
        padding: 5px 10px;
    }

    QPushButton#switchMode {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: white;
        color: #fea36b;
        padding: 5px 10px;
    }

    QPushButton#pushRegistration:hover {
        background-color: #d58745;
    }

    QPushButton#switchMode:hover {
        background-color: #dadada;
    }

    QLineEdit {
        border-radius: 10px;
        border: 1px solid white;
        background: white;
        color: black;
        padding: 5px;
    }

    QLineEdit::placeholder {
        color: #727272;
    }

)";

}  // namespace Ui
