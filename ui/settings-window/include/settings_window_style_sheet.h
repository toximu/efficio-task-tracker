#pragma once

#include <QString>

namespace Ui {
    QString settings_window_light_autumn_theme = R"(
        QWidget {
            background-color: white;
        }

        QLabel {
            font-weight: bold;
            font-family: 'Arial';
            color: #089083;
            background-color: transparent;
        }

        QLabel#font_size_label {
            font-size: 30px;
        }

        QLabel#title_label {
            font-size: 20px;
        }

        QPushButton#language_button {
            background-color: rgb(33, 44, 50);
            color: #f5f5f5;
            padding: 2px;
            font-size: 20px;
            border-radius: 7px;
            width: 40px;
            height: 30px;
        }

        QPushButton#language_button:hover {
            background-color: rgb(14, 17, 19);
        }
        QPushButton#language_button:pressed {
            background-color: rgb(4, 4, 5);
        }

        QPushButton#theme_button {   
            width: 40px;      
            height: 30px;
            color: #089083;
            font-size: 15px;
            border-radius: 7px; 
            padding: 0;          
            margin-bottom: 2px;
            background-color: transparent;
            border: 2px solid #089083;
        }
        QPushButton#theme_button:hover {
            background-color: #089083;
            color: white;
        }

        QPushButton::pressed#switch_theme {
            background-color:rgb(7, 110, 100);
            color: white;
        }

        QRadioButton {
            font-family: 'Arial';
            color: #727272;
            spacing: 5px;
            background-color: transparent;
        }
        QRadioButton::indicator {
            width: 16px;
            height: 16px;
            border-radius: 3px;
            border: 1px solid #727272;
            background-color: #ffffff;
        }
        QRadioButton::indicator:hover {
            border: 1px solid #fea36b;
        }
        QRadioButton::indicator:checked {
            background-color: #fea36b;
            border: 1px solid #fea36b;
        }        
    )";

    QString settings_window_dark_autumn_theme = R"(

    )";
    QString settings_window_dark_purple_theme = R"(

    )";
    QString settings_window_light_purple_theme = R"(

    )";
    QString settings_window_blue_theme = R"(

    )";

} // namespace Ui