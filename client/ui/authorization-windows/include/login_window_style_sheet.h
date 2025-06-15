#pragma once

#include "ui_login_window.h"

namespace Ui {
QString login_window_light_autumn_theme = R"(
        QWidget {
            background-color: #f5f5f5;
        }
    
        QLabel {
            background-color: transparent;
            font-family: 'Arial';
            font-size: 13px;
            color: #089083;
            padding: 1px;
        }
    
        QPushButton#push_enter {
            font-family: 'Arial';
            border-radius: 10px;
            background-color: #fea36b;
            color: white;
            padding: 5px 10px;
        }
    
        QPushButton#switch_mode {
            font-family: 'Arial';
            border-radius: 10px;
            background-color: white;
            color: #fea36b;
            padding: 5px 10px;
        }
    
        QPushButton#push_enter:hover {
            background-color: #d58745;
        }
    
        QPushButton#switch_mode:hover {
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

        QPushButton#switch_theme {  
            background-color: #089083;
            min-width: 20px;      
            min-height: 20px;
            color: #f5f5f5;
            padding: 2px;    
            font-size: 13px;
            border-radius: 7px;
            font-family: 'Arial' bold;
        }
        QPushButton#switch_theme:hover {
            background-color: rgb(8, 82, 74);
            color: #f5f5f5;
        }

        QPushButton::pressed#switch_theme {
            background-color:rgb(3, 58, 54);
            color: #f5f5f5;
        }
    )";
}  // namespace Ui