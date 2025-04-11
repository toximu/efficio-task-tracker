#ifndef MAIN_WINDOW_STYLE_HPP
#define MAIN_WINDOW_STYLE_HPP
#include <QString>

namespace Ui {

QString main_window_light_autumn_theme = R"(
#main-window {
    background-color : #f5f5f5;
}

#main-window QLabel {
    font-weight: bold;
}

QScrollBar:vertical {
    border: none;
    background: transparent;
    width: 10px;
    margin: 0;
}
QScrollBar::handle:vertical {
    background: #c0c0c0;
    border-radius: 5px;
    min-height: 20px;
}

QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
        background: none;
        height: 0px;
    }
QScrollArea {
    border: none;
    background: transparent;
}

#ProjectList {
    background-color: white;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
    font-family: 'Arial';
    font-weight: bold;
    font-size: 13px;
    color:rgb(44, 44, 44);
}

#ProjectList::item {
    background-color:rgb(207, 236, 233);
    border: none;
    padding: 10px;
    margin: 2px;
    border-radius: 6px;
}

#ProjectList::item:hover {
    background-color: rgb(178, 226, 221);
}

#ProjectList::item:selected {
    background-color: #089083;
    color: #ffffff;
}

#ProjectList QScrollBar:vertical {
    border: none;
    background: #FED6BC;
    width: 10px;
    margin: 0;
}

#ProjectList QScrollBar::handle:vertical {
    background: #c0c0c0;
    border-radius: 5px;
    min-height: 20px;
}

#ProjectList QScrollBar::add-line:vertical,
#ProjectList QScrollBar::sub-line:vertical {
    background: none;
}

#ProjectList QScrollBar::add-page:vertical,
#ProjectList QScrollBar::sub-page:vertical {
    background: none;
}

#BottomBar {
    background-color: rgb(33, 44, 50);
    border-radius: 8px;
    padding: 8px;
    outline: 0;
}

#BottomBar QLabel {
    color : white;
    font-family: 'Arial';
    font-size: 13px;
}

#NoteList {
    border-radius : 8px;
    background-color: white;
}

#NoteWidget {
    background-color: #ffdda2;
    border-radius: 8px;
}

#NoteWidget QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color:rgb(241, 201, 132);
    color: rgb(33, 44, 50);
    padding: 5px 10px;
}


#NoteWidget QPushButton:hover {
    background-color:rgb(213, 167, 88);
}

QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color: #fea36b;
    color: white;
    padding: 5px 10px;
    min-width: 60px;
    min-height: 25px;
}

QPushButton::hover {
    background-color:rgb(245, 148, 89);
}

QPushButton::pressed {
    background-color:rgb(238, 122, 50);
}

QPushButton#switch_theme_button_ {
    width: 20px;          
    height: 20px;        
    min-width: 20px;      
    min-height: 20px;
    max-width: 20px;     
    max-height: 20px;
    border-radius: 7px; 
    padding: 0;          
    margin-bottom: 2px;
    
    border: 2px solid #fea36b;
    
    background-color: transparent;
}
QPushButton::hover#switch_theme_button_ {
    background-color: #fea36b;
}
QPushButton::pressed#switch_theme_button_ {
    background-color:#fea36b;
}
)";

QString main_window_dark_autumn_theme = R"(
#main-window {
    background-color: black;
}

#main-window QLabel {
    font-weight: bold;
    color: #BDD1BD;
}

QScrollBar:vertical {
    border: none;
    background: #202020;
    width: 10px;
    margin: 0;
}
QScrollBar::handle:vertical {
    background: #089083;
    border-radius: 5px;
    min-height: 20px;
}

QScrollArea {
    border: none;
    background: transparent;
}

#ProjectList {
    background-color: #202020;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
    font-family: 'Arial';
    font-weight: bold;
    font-size: 13px;
    color: #BDD1BD;
}

#ProjectList::item {
    background-color: #1E2A30;
    border: none;
    padding: 10px;
    margin: 2px;
    border-radius: 6px;
}

#ProjectList::item:hover {
    background-color: #2C3E44;
}

#ProjectList::item:selected {
    background-color: #089083;
    color: #263238;
}

#BottomBar {
    background-color: #202020;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
}

#BottomBar QLabel {
    color: #BDD1BD;
    font-family: 'Arial';
    font-size: 13px;
}

#NoteList {
    border-radius: 8px;
    background-color: #202020;
}

#NoteWidget {
    background-color: #ffdda2;
    border-radius: 8px;
}

#NoteWidget QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color:rgb(241, 201, 132);
    color: rgb(33, 44, 50);
    padding: 5px 10px;
}


#NoteWidget QPushButton:hover {
    background-color:rgb(213, 167, 88);
}

QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color: #fea36b;
    color: white;
    padding: 5px 10px;
    min-width: 60px;
    min-height: 25px;
}

#NoteWidget QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color: #5E3E3E;
    color: #BDD1BD;
    padding: 5px 10px;
}

#NoteWidget QPushButton:hover {
    background-color:rgb(53, 28, 28);
}

QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color: #fea36b;
    color: #263238;
    padding: 5px 10px;
    min-width: 60px;
    min-height: 25px;
}

QPushButton:hover {
    background-color: #d58745;
}

QPushButton#switch_theme_button_ {
    width: 20px;          
    height: 20px;        
    min-width: 20px;      
    min-height: 20px;
    max-width: 20px;     
    max-height: 20px;
    border-radius: 7px; 
    padding: 0;          
    margin-bottom: 2px;
    
    border: 2px solid #089083;
    
    background-color: transparent;
}
QPushButton::hover#switch_theme_button_ {
    background-color: #089083;
}
QPushButton::pressed#switch_theme_button_ {
    background-color:rgb(13, 93, 85);
}
)";

QString main_window_light_purple_theme = R"(
#main-window {
    background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,
        stop:0 #9882B9, stop:0.5 rgb(176, 157, 205), stop:1 rgb(103, 88, 126));
}

#main-window QLabel {
    font-weight: bold;
    color: rgb(42, 10, 25);
}

QScrollBar:vertical {
    border: none;
    background: transparent;
    width: 10px;
    margin: 0;
}
QScrollBar::handle:vertical {
    background: #722548;
    border-radius: 5px;
    min-height: 20px;
}

QScrollArea {
    border: none;
    background: transparent;
}

#ProjectList {
    background-color: rgb(221, 210, 238);
    border-radius: 8px;
    padding: 8px;
    outline: 0;
    font-family: 'Arial';
    font-weight: bold;
    font-size: 13px;
    color: rgb(42, 10, 25);
}

#ProjectList::item {
    background-color: rgb(206, 193, 224);
    border: none;
    padding: 10px;
    margin: 2px;
    border-radius: 6px;
}

#ProjectList::item:hover {
    background-color: rgb(168, 147, 199);
}

#ProjectList::item:selected {
    background-color:rgb(82, 69, 101);
    color: rgb(221, 210, 238);
}

#BottomBar {
    background-color: rgb(42, 10, 25);
    border-radius: 8px;
    padding: 8px;
    outline: 0;
}

#BottomBar QLabel {
    color: rgb(218, 207, 235);
    font-family: 'Arial';
    font-size: 13px;
}

#NoteList {
    border-radius: 8px;
    background-color: rgb(221, 210, 238);
}

#NoteWidget {
    background-color: #D4A5C9;
    border-radius: 8px;
}

#NoteWidget QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color: #C98BB8;
    color: rgb(42, 10, 25);
    padding: 5px 10px;
}


#NoteWidget QPushButton:hover {
    background-color:rgb(134, 82, 120); 
}

QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color: #722548;
    color: #9882B9;
    padding: 5px 10px;
    min-width: 60px;
    min-height: 25px;
}

QPushButton:hover {
    background-color: rgb(98, 27, 59);
}

QPushButton#switch_theme_button_ {
    width: 20px;          
    height: 20px;        
    min-width: 20px;      
    min-height: 20px;
    max-width: 20px;     
    max-height: 20px;
    border-radius: 7px; 
    padding: 0;          
    margin-bottom: 2px;
    
    border: 2px solid #722548;
    
    background-color: transparent;
}
    
QPushButton::hover#switch_theme_button_ {
    background-color: #722548;
}
QPushButton::pressed#switch_theme_button_ {
    background-color: #722548;
}
)";

QString main_window_dark_purple_theme = R"(
#main-window {
    background-color:rgb(9, 6, 10);
}

#main-window QLabel {
    font-weight: bold;
    color: #9882B9;
}

QScrollBar:vertical {
    border: none;
    background: #221932;
    width: 10px;
    margin: 0;
}
QScrollBar::handle:vertical {
    background: #722548;
    border-radius: 5px;
    min-height: 20px;
}

QScrollArea {
    border: none;
    background: transparent;
}

#ProjectList {
    background-color: #221932;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
    font-family: 'Arial';
    font-weight: bold;
    font-size: 13px;
    color: #9882B9;
}

#ProjectList::item {
    background-color: rgb(34, 25, 48);
    border: none;
    padding: 10px;
    margin: 2px;
    border-radius: 6px;
}

#ProjectList::item:hover {
    background-color: rgb(42, 31, 59);
}

#ProjectList::item:selected {
    background-color: #722548;
    color: #9882B9;
}

#BottomBar {
    background-color: rgb(42, 10, 25);
    border-radius: 8px;
    padding: 8px;
    outline: 0;
}

#BottomBar QLabel {
    color: #9882B9;
    font-family: 'Arial';
    font-size: 13px;
}

#NoteList {
    border-radius: 8px;
    background-color: #221932;
}

#NoteWidget {
    background-color: #3D2A3D;
    border-radius: 8px;
}

#NoteWidget QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color: #5D3A5D;
    color: #9882B9;
    padding: 5px 10px;
}


#NoteWidget QPushButton:hover {
    background-color:rgb(56, 35, 56);
}

QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color: #722548;
    color: #060407;
    padding: 5px 10px;
    min-width: 60px;
    min-height: 25px;
}

QPushButton:hover {
    background-color: rgb(98, 27, 59);
}
QPushButton#switch_theme_button_ {
    width: 20px;          
    height: 20px;        
    min-width: 20px;      
    min-height: 20px;
    max-width: 20px;     
    max-height: 20px;
    border-radius: 7px; 
    padding: 0;          
    margin-bottom: 2px;
    
    border: 2px solid #9882B9;
    
    background-color: transparent;
}
QPushButton::hover#switch_theme_button_ {
    background-color: #9882B9;
}
QPushButton::pressed#switch_theme_button_ {
    background-color:rgb(113, 93, 143);
}
)";

QString main_window_nature_flat_theme = R"(
#main-window {
    background:  #07142B;
}

#main-window QLabel {
    font-weight: bold;
    color: #BDD1BD;
}

QScrollBar:vertical {
    border: none;
    background: #173C4C;
    width: 10px;
    margin: 0;
}
QScrollBar::handle:vertical {
    background: #568F7C;
    border-radius: 5px;
    min-height: 20px;
}

QScrollArea {
    border: none;
    background: transparent;
}

#ProjectList {
    background-color: #173C4C;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
    font-family: 'Arial';
    font-weight: bold;
    font-size: 13px;
    color: #BDD1BD;
    border: 1px solid;
}

#ProjectList::item {
    background-color: #173C4C;
    border: none;
    padding: 10px;
    margin: 2px;
    border-radius: 6px;
}

#ProjectList::item:hover {
    background-color: #326D6C;
}

#ProjectList::item:selected {
    background-color: #568F7C;
    color: #173C4C;
}

#BottomBar {
    background-color: #173C4C;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
    border: 1px solid;
}

#BottomBar QLabel {
    color: #BDD1BD;
    font-family: 'Arial';
    font-size: 13px;
}

#NoteList {
    border-radius: 8px;
    background-color: #173C4C;
    border: 1px solid;
}

#NoteWidget {
    background-color: #2D4C3C;
    border-radius: 8px;
    border: 1px solid;
}

#NoteWidget QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color: #326D6C;
    color: #07142B;
    padding: 5px 10px;
}


#NoteWidget QPushButton:hover {
    background-color:rgb(36, 82, 81);
}

QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color: #568F7C;
    color: #07142B;
    padding: 5px 10px;
    min-width: 60px;
    min-height: 25px;
    border: none;
}

QPushButton:hover {
    background-color: #326D6C;
}

QPushButton:pressed {
    background-color: #173C4C;
}

QPushButton#switch_theme_button_ {
    width: 20px;          
    height: 20px;        
    min-width: 20px;      
    min-height: 20px;
    max-width: 20px;     
    max-height: 20px;
    border-radius: 7px; 
    padding: 0;          
    margin-bottom: 2px;
    
    border: 2px solid #85B093;
    
    background-color: transparent;
}

QPushButton::hover#switch_theme_button_ {
    background-color: #85B093;
}
QPushButton::pressed#switch_theme_button_ {
    background-color:rgb(107, 141, 118);
}
)";

}  // namespace Ui

#endif  // MAIN_WINDOW_STYLE_HPP