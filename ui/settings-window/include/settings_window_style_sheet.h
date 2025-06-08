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
        
        QLabel#title_label {
            font-size: 28px;
        }

        QLabel#font_size_label {
            font-size: 35px;
        }

        QPushButton#theme_button {
            background-color: #fea36b;
            width: 50px;
            height: 30px;
            color: #f5f5f5;
            padding: 2px;
            font-size: 15px;
            border-radius: 7px;
        }

        QPushButton#theme_button:hover {
            background-color:rgb(245, 148, 89);
        }
        QPushButton#theme_button:pressed {
            background-color:rgb(238, 122, 50);
        }

        QPushButton#language_button {  
            background-color: #089083;
            width: 50px;      
            height: 30px;
            color: #f5f5f5;
            padding: 2px;    
            font-size: 20px;
            border-radius: 7px;
        }
        QPushButton#language_button:hover {
            background-color: rgb(8, 82, 74);
            color: #f5f5f5;
        }

        QPushButton::pressed#language_button {
            background-color:rgb(3, 58, 54);
            color: #f5f5f5;
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
            background-color: transparent; 
        }
        QRadioButton::indicator:hover {
            background-color: #727272;
        }
        QRadioButton::indicator:checked {
            background-color: rgb(33, 44, 50);
        }        
    )";

    QString settings_window_dark_autumn_theme = R"(
        QWidget {
            background-color: #202020;
        }

        QLabel {
            font-weight: bold;
            font-family: 'Arial';
            color: #089083;
            background-color: transparent;
        }
        
        QLabel#title_label {
            font-size: 28px;
        }

        QLabel#font_size_label {
            font-size: 35px;
        }

        QPushButton#language_button {
            background-color: #fea36b;
            width: 50px;
            height: 30px;
            color: #263238;
            padding: 2px;
            font-size: 20px;
            border-radius: 7px;
        }

        QPushButton#language_button:hover {
            background-color: #d58745;
        }
        QPushButton#language_button:pressed {
            background-color: #b87338;
        }

        QPushButton#theme_button {  
            background-color: #089083;
            color: #f5f5f5;
            width: 50px;      
            height: 30px;
            padding: 2px;    
            font-size: 15px;
            border-radius: 7px;
        }
        QPushButton#theme_button:hover {
            background-color:rgb(8, 82, 74);
        }

        QPushButton::pressed#switch_theme {
            background-color: #089083;
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
            background-color: transparent; 
        }
        QRadioButton::indicator:hover {
            background-color: #727272;
        }
        QRadioButton::indicator:checked {
            background-color:rgb(0, 0, 0);
        }    
    )";

    QString settings_window_light_purple_theme = R"(
        QWidget {
            background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,
                stop:0 #9882B9, stop:0.5 rgb(176, 157, 205), stop:1 rgb(125, 109, 148));
        }

        QLabel {
            font-weight: bold;
            font-family: 'Arial';
            color: rgb(42, 10, 25);
            background-color: transparent;
        }
        
        QLabel#title_label {
            font-size: 28px;
        }

        QLabel#font_size_label {
            font-size: 35px;
        }

        QPushButton#language_button {
            background-color: #722548;
            width: 50px;
            height: 30px;
            color: rgb(206, 193, 224);
            padding: 2px;
            font-size: 20px;
            border-radius: 7px;
        }

        QPushButton#language_button:hover {
            background-color: rgb(98, 27, 59);
        }
        QPushButton#language_button:pressed {
            background-color: rgb(78, 21, 47);
        }

        QPushButton#theme_button {  
            background-color: rgb(42, 10, 25);
            color: rgb(163, 148, 184);
            width: 50px;      
            height: 30px;
            padding: 2px;    
            font-size: 15px;
            border-radius: 7px;
        }
        QPushButton#theme_button:hover {
            background-color: rgb(21, 5, 12);
        }

        QPushButton#theme_button:pressed{
            background-color: rgb(2, 0, 1);
        }

        QRadioButton {
            font-family: 'Arial';
            color: rgb(42, 10, 25);
            spacing: 5px;
            background-color: transparent;
        }
        QRadioButton::indicator {
            width: 16px;
            height: 16px;
            border-radius: 3px;
            border: 1px solid rgb(42, 10, 25);
            background-color: transparent; 
        }
        QRadioButton::indicator:hover {
            background-color: rgb(42, 10, 25);
        }
        QRadioButton::indicator:checked {
            background-color: rgb(218, 207, 235);
        }
    )";

    QString settings_window_dark_purple_theme = R"(
        QWidget {
            background-color: rgb(9, 6, 10);
        }

        QLabel {
            font-weight: bold;
            font-family: 'Arial';
            color: #9882B9;
            background-color: transparent;
        }
        
        QLabel#title_label {
            font-size: 28px;
        }

        QLabel#font_size_label {
            font-size: 35px;
        }

        QPushButton#language_button {
            background-color: #722548;
            color: #060407;
            width: 50px;
            height: 30px;
            padding: 2px;
            font-size: 20px;
            border-radius: 7px;
        }

        QPushButton#language_button:hover {
            background-color: rgb(79, 25, 50);
        }
        QPushButton#language_button:pressed {
             background-color:rgb(59, 16, 35);
        }

        QPushButton#theme_button {  
            background-color: rgb(42, 10, 25);
            color: #9882B9;
            width: 50px;      
            height: 30px;
            padding: 2px;    
            font-size: 15px;
            border-radius: 7px;
        }
        QPushButton#theme_button:hover {
            background-color:rgb(22, 5, 13);
        }

        QPushButton#theme_button:pressed {
            background-color:rgb(11, 3, 7);
        }

        QRadioButton {
            font-family: 'Arial';
            color: #9882B9;
            spacing: 5px;
            background-color: transparent;
        }
        QRadioButton::indicator {
            width: 16px;
            height: 16px;
            border-radius: 3px;
            border: 1px solid #9882B9;
            background-color: transparent; 
        }
        QRadioButton::indicator:hover {
            background-color: #221932;
        }
        QRadioButton::indicator:checked {
            background-color: #9882B9;
        }
    )";

    QString settings_window_blue_theme = R"(
        QWidget {
            background: #173C4C;
        }

        QLabel {
            font-weight: bold;
            font-family: 'Arial';
            color: #BDD1BD;
            background-color: transparent;
        }
        
        QLabel#title_label {
            font-size: 28px;
        }

        QLabel#font_size_label {
            font-size: 35px;
        }

        QPushButton#language_button {
            background-color: #BDD1BD;
            color: #173C4C;
            width: 50px;
            height: 30px;
            padding: 2px;
            font-size: 20px;
            border-radius: 7px;
        }

        QPushButton#language_button:hover {
            background-color:rgb(158, 176, 158);
        }
        QPushButton#language_button:pressed {
            background-color:rgb(141, 157, 141);
        }

        QPushButton#theme_button {  
            background-color: #326D6C;
            color: #BDD1BD;
            width: 50px;      
            height: 30px;
            color: #BDD1BD;
            padding: 2px;    
            font-size: 15px;
            border-radius: 7px;
        }
        QPushButton#theme_button:hover {
            background-color:rgb(47, 89, 89);
        }

        QPushButton#theme_button:pressed {
            background-color:rgb(31, 69, 85);
        }

        QRadioButton {
            font-family: 'Arial';
            color: #BDD1BD;
            spacing: 5px;
            background-color: transparent;
        }
        QRadioButton::indicator {
            width: 16px;
            height: 16px;
            border-radius: 3px;
            border: 1px solid #BDD1BD;
            background-color: transparent; 
        }
        QRadioButton::indicator:hover {
            background-color: #BDD1BD;
        }
        QRadioButton::indicator:checked {
            background-color: #07142B;
        }
    )";

} // namespace Ui