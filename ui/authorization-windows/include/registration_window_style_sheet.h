#pragma once

#include "ui_registration_window.h"

namespace Ui {
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