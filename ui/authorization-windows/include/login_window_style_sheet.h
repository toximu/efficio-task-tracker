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
    
        QPushButton#pushEnter {
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
    
        QPushButton#pushEnter:hover {
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

        QPushButton#switch_theme {
            background-color: rgb(163, 162, 162);
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

    QString login_window_dark_autumn_theme = R"(
        QWidget {
            background-color: #202020;
        }
    
        QLabel {
            background-color: transparent;
            font-family: 'Arial';
            font-size: 13px;
            color: #089083;
            padding: 1px;
        }
    
        QPushButton#pushEnter {
            font-family: 'Arial';
            border-radius: 10px;
            background-color: #fea36b;
            color: #263238;
            padding: 5px 10px;
        }

        QPushButton#pushEnter:hover {
            background-color:rgb(225, 133, 76);
        }

        QPushButton#switchMode {
            font-family: 'Arial';
            border-radius: 10px;
            background-color: #089083;
            color: white;
            padding: 5px 10px;
        }
    
        QPushButton#switchMode:hover {
            background-color: #01635d;
        }

        QLineEdit {
            border-radius: 10px;
            border: 1px solid rgb(0, 0, 0);
            background:rgb(0, 0, 0);
            color: #727272;
            padding: 5px;
        }
    
        QLineEdit::placeholder {
            color: #727272;
        }

        QPushButton#switch_theme {
            background-color: #202020;
            border-radius: 9px;
            border: 2px solid #089083;
            padding: 5px;
        }
        QPushButton::hover#switch_theme {
            background-color:  #089083;
        }
        QPushButton::pressed#switch_theme {
            background-color:rgb(13, 93, 85);
        }  
    )";

    

    QString login_window_light_purple_theme = R"(
        QWidget {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #9882B9, stop:0.5 rgb(176, 157, 205), stop:1 rgb(103, 88, 126));
            margin: 0;
            padding: 0;
            border: none;
        }
    
        QLabel {
            background-color: transparent;
            font-family: 'Arial';
            font-size: 13px;
            color: rgb(42, 10, 25);
            padding: 1px;
        }
    
        QPushButton#pushEnter {
            font-family: 'Arial';
            border-radius: 10px;
            background-color: #722548;
            color:rgb(206, 193, 224);
            padding: 5px 10px;
        }

        QPushButton#pushEnter:hover {
            background-color:rgb(98, 27, 59)
        }

        QPushButton#switchMode {
            font-family: 'Arial';
            border-radius: 10px;
            background-color: rgb(42, 10, 25);
            color: rgb(218, 207, 235);
            padding: 5px 10px;
        }
    
        QPushButton#switchMode:hover {
            background-color:rgb(27, 6, 16);
        }

        QLineEdit {
            border-radius: 10px;
            border: 1px solid rgb(221, 210, 238);
            background: rgb(221, 210, 238);
            color: #221932; 
            padding: 5px;
        }
    
        QLineEdit::placeholder {
            color: white;
        }

        QPushButton#switch_theme {
            background-color: #9882B9;
            border-radius: 9px;
            border: 2px solid #060407;
            padding: 5px;
        }
        QPushButton::hover#switch_theme {
            background-color: #060407;
        }
        QPushButton::pressed#switch_theme {
            background-color:rgb(2, 0, 2);
        }  
    )";   

    QString login_window_dark_purple_theme = R"(
        QWidget {
            background-color:rgb(9, 6, 10);
        }
    
        QLabel {
            background-color: transparent;
            font-family: 'Arial';
            font-size: 13px;
            color: #9882B9;
            padding: 1px;
        }
    
        QPushButton#pushEnter {
            font-family: 'Arial';
            border-radius: 10px;
            background-color: #722548;
            color: #060407;
            padding: 5px 10px;
        }

        QPushButton#pushEnter:hover {
            background-color:rgb(98, 27, 59)
        }

        QPushButton#switchMode {
            font-family: 'Arial';
            border-radius: 10px;
            background-color: rgb(42, 10, 25);
            color: #9882B9;
            padding: 5px 10px;
        }
    
        QPushButton#switchMode:hover {
            background-color:rgb(27, 6, 16);
        }

        QLineEdit {
            border-radius: 10px;
            border: 1px solid #221932; 
            background: #221932; 
            color: #9882B9;
            padding: 5px;
        }
    
        QLineEdit::placeholder {
            color: white;
        }
    
        QPushButton#switch_theme {
            background-color: #060407;
            border-radius: 9px;
            border: 2px solid #9882B9;
            padding: 5px;
        }
        QPushButton::hover#switch_theme {
            background-color: #9882B9;
        }
        QPushButton::pressed#switch_theme {
            background-color:rgb(113, 93, 143);
        }  
    
    )";
    
    QString login_window_nature_flat_theme = R"(
        QWidget {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #173C4C, stop:0.5 #326D6C, stop:1 #07142B);
            margin: 0;
            padding: 0;
            border: none;
        }
        
        QLabel {
            background-color: transparent;
            font-family: 'Arial';
            font-size: 13px;
            color: #BDD1BD;
            padding: 1px;
        }
        
        QPushButton#pushEnter {
            font-family: 'Arial';
            border-radius: 10px;
            background-color: #568F7C;
            color: #BDD1BD;
            padding: 5px 10px;
            border: none;
            font-weight: bold;
        }
        
        QPushButton#pushEnter:hover {
            background-color: #326D6C;
        }
        
        QPushButton#pushEnter:pressed {
            background-color: #07142B;
        }
        
        QPushButton#switchMode {
            font-family: 'Arial';
            border-radius: 10px;
            background-color: #326D6C;
            color: #BDD1BD;
            padding: 5px 10px;
            border: 1px solid #568F7C;
        }
        
        QPushButton#switchMode:hover {
            background-color: #568F7C;
            color: #07142B;
        }
        
        QLineEdit {
            border-radius: 10px;
            border: 1px solid #568F7C;
            background: #07142B;
            color: #BDD1BD;
            padding: 5px;
            selection-background-color: #326D6C;
        }
        
        QLineEdit::placeholder {
            color: #85B093;
            opacity: 0.7;
        }
        
        QPushButton#switch_theme {
            background-color: #173C4C;
            border-radius: 9px;
            border: 2px solid #85B093;
            padding: 5px;
            color: #BDD1BD;
        }
        
        QPushButton#switch_theme:hover {
            background-color: #85B093;
        }
        
        QPushButton#switch_theme:pressed {
            background-color:rgb(107, 141, 118);
        }
    )";    
}  // namespace Ui