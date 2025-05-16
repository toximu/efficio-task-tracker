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
    width: 7px;
}
QScrollBar:horizontal {
    height: 7px;
}
QScrollBar:vertical, QScrollBar:horizontal {
    border: none;
    background: transparent;
    margin: 0;
}
QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
    background: #c0c0c0;
    border-radius: 3px;
    min-height: 20px;
    min-width: 20px;
}
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal,
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical,
QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
    background: none;
    height: 0;
    width: 0;
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
    width: 7px;
}
#ProjectList QScrollBar:horizontal {
    height: 7px;
}
#ProjectList QScrollBar:vertical, 
#ProjectList QScrollBar:horizontal {
    border: none;
    background: transparent;
    margin: 0;
}
#ProjectList QScrollBar::handle:vertical, 
#ProjectList QScrollBar::handle:horizontal {
    background: #c0c0c0;
    border-radius: 3px;
    min-height: 20px;
    min-width: 20px;
}
#ProjectList QScrollBar::add-line:vertical,
#ProjectList QScrollBar::sub-line:vertical,
#ProjectList QScrollBar::add-line:horizontal,
#ProjectList QScrollBar::sub-line:horizontal,
#ProjectList QScrollBar::add-page:vertical,
#ProjectList QScrollBar::sub-page:vertical,
#ProjectList QScrollBar::add-page:horizontal,
#ProjectList QScrollBar::sub-page:horizontal {
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

#BottomBar QPushButton {
    background-color: transparent;
    color:  white;
    font-family: 'Arial';
    font-size: 13px;
    padding: 0px 0px;
    min-width: 0px;
    min-height: 0px;
}

#BottomBar QPushButton:hover {
    color:rgb(182, 181, 181);
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
    background-color: rgb(185, 117, 61);
}
)";

QString main_window_dark_autumn_theme = R"(
    #main-window {
        background-color: #202020;
    }
    
    #main-window QLabel {
        font-weight: bold;
        color: #BDD1BD;
    }
    
    QScrollBar:vertical {
        width: 7px;
    }
    QScrollBar:horizontal {
        height: 7px;
    }
    QScrollBar:vertical, QScrollBar:horizontal {
        border: none;
        background: transparent;
        margin: 0;
    }
    QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
        background: #c0c0c0;
        border-radius: 3px;
        min-height: 20px;
        min-width: 20px;
    }
    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
    QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal,
    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical,
    QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
        background: none;
        height: 0;
        width: 0;
    }
    
    QScrollArea {
        border: none;
        background: transparent;
    }
    
    #ProjectList {
        background-color: black;
        border-radius: 8px;
        padding: 8px;
        outline: 0;
        font-family: 'Arial';
        font-weight: bold;
        font-size: 13px;
        color: #BDD1BD;
    } 
    
    #ProjectList::item {
        background-color: rgb(32, 53, 51);
        color: #ffffff;
        border: none;
        padding: 10px;
        margin: 2px;
        border-radius: 6px;
    }
    
    #ProjectList::item:hover {
        background-color: rgb(64, 89, 87);
    }
    
    #ProjectList::item:selected {
        background-color: #089083;
        color: rgb(33, 44, 50);
    }
    
    #ProjectList QScrollBar:vertical {
        width: 7px;
    }
    #ProjectList QScrollBar:horizontal {
        height: 7px;
    }
    #ProjectList QScrollBar:vertical, 
    #ProjectList QScrollBar:horizontal {
        border: none;
        background: transparent;
        margin: 0;
    }
    #ProjectList QScrollBar::handle:vertical, 
    #ProjectList QScrollBar::handle:horizontal {
        background: #c0c0c0;
        border-radius: 3px;
        min-height: 20px;
        min-width: 20px;
    }
    #ProjectList QScrollBar::add-line:vertical,
    #ProjectList QScrollBar::sub-line:vertical,
    #ProjectList QScrollBar::add-line:horizontal,
    #ProjectList QScrollBar::sub-line:horizontal,
    #ProjectList QScrollBar::add-page:vertical,
    #ProjectList QScrollBar::sub-page:vertical,
    #ProjectList QScrollBar::add-page:horizontal,
    #ProjectList QScrollBar::sub-page:horizontal {
        background: none;
    }
    
    #BottomBar {
        background-color:rgb(0, 0, 0);
        border-radius: 8px;
        padding: 8px;
        outline: 0;
    }
    
    #BottomBar QLabel {
        color: #c0c0c0;
        font-family: 'Arial';
        font-size: 13px;
    }
    
    #BottomBar QPushButton {
    background-color: transparent;
        color: #c0c0c0;
        font-family: 'Arial';
        font-size: 13px;
        padding: 0px 0px;
        min-width: 0px;
        min-height: 0px;
    }

    #BottomBar QPushButton:hover {
        color:rgb(236, 234, 234);
        font-family: 'Arial';
        font-size: 13px;
    }
    

    #NoteList {
        border-radius: 8px;
        background-color: black;
    }
    
    #NoteWidget {
        background-color:rgb(179, 156, 116);
        border-radius: 8px;
    }
    
    #NoteWidget QPushButton {
        font-family: 'Arial';
        font-size: 13px;
        font-weight: bold;
        border-radius: 10px;
        background-color: #ffdda2;
        color: #202020;
        padding: 5px 10px;
    }
    
    #NoteWidget QPushButton:hover {
        background-color:rgb(255, 236, 203);
    }
    
    QPushButton {
        font-family: 'Arial';
        font-size: 13px;
        font-weight: bold;
        border-radius: 10px;
        background-color:rgb(211, 139, 95);
        color: #263238;
        padding: 5px 10px;
        min-width: 60px;
        min-height: 25px;
    }
    
    QPushButton:hover {
        background-color:rgb(181, 114, 59);
    }
    
    QPushButton:pressed {
        background-color:rgb(143, 88, 44);
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
        border: 2px solid rgb(211, 139, 95);
        background-color: transparent;
    }
    QPushButton::hover#switch_theme_button_ {
        background-color: rgb(211, 139, 95);
    }
    QPushButton::pressed#switch_theme_button_ {
        background-color: rgb(211, 139, 95);
    }
    )";


QString main_window_light_purple_theme = R"(
#main-window {
    background: #9882B9;
}

#main-window QLabel {
    font-weight: bold;
    color: rgb(42, 10, 25);
}

QScrollBar:vertical {
    width: 7px;
}
QScrollBar:horizontal {
    height: 7px;
}
QScrollBar:vertical, QScrollBar:horizontal {
    border: none;
    background: transparent;
    margin: 0;
}
QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
    background: white;
    border-radius: 3px;
    min-height: 20px;
    min-width: 20px;
}
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal,
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical,
QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
    background: none;
    height: 0;
    width: 0;
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
    background-color: rgb(163, 148, 184);
}

#ProjectList::item:selected {
    background-color:rgb(121, 103, 148);
    color: rgb(221, 210, 238);
}

#ProjectList QScrollBar:vertical {
    width: 7px;
}
#ProjectList QScrollBar:horizontal {
    height: 7px;
}
#ProjectList QScrollBar:vertical, 
#ProjectList QScrollBar:horizontal {
    border: none;
    background: transparent;
    margin: 0;
}
#ProjectList QScrollBar::handle:vertical, 
#ProjectList QScrollBar::handle:horizontal {
    background: white;
    border-radius: 3px;
    min-height: 20px;
    min-width: 20px;
}
#ProjectList QScrollBar::add-line:vertical,
#ProjectList QScrollBar::sub-line:vertical,
#ProjectList QScrollBar::add-line:horizontal,
#ProjectList QScrollBar::sub-line:horizontal,
#ProjectList QScrollBar::add-page:vertical,
#ProjectList QScrollBar::sub-page:vertical,
#ProjectList QScrollBar::add-page:horizontal,
#ProjectList QScrollBar::sub-page:horizontal {
    background: none;
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

#BottomBar QPushButton {
    background-color: transparent;
    color: #9882B9;
    font-family: 'Arial';
    font-size: 13px;
    padding: 0px 0px;
    min-width: 0px;
    min-height: 0px;
}

#BottomBar QPushButton:hover {
    color:rgb(208, 193, 231);
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
    background-color:rgb(69, 24, 44);
}

QPushButton:pressed {
    background-color:rgb(47, 16, 30);
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
    background-color:rgb(86, 26, 53);
}
QPushButton::pressed#switch_theme_button_ {
    background-color: rgb(80, 27, 51);
}
)";

QString main_window_dark_purple_theme = R"(
#main-window {
    background-color: rgb(9, 6, 10);
}

#main-window QLabel {
    font-weight: bold;
    color: #9882B9;
}

QScrollBar:vertical {
    width: 7px;
}
QScrollBar:horizontal {
    height: 7px;
}
QScrollBar:vertical, QScrollBar:horizontal {
    border: none;
    background: transparent;
    margin: 0;
}
QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
    background: #775E88;
    border-radius: 3px;
    min-height: 20px;
    min-width: 20px;
}
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal,
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical,
QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
    background: none;
    height: 0;
    width: 0;
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
    background-color:rgb(50, 41, 66);
    border: none;
    padding: 10px;
    margin: 2px;
    border-radius: 6px;
}

#ProjectList::item:hover {
    background-color:rgb(97, 82, 123);
}

#ProjectList::item:selected {
    background-color:rgb(205, 146, 172);
    color: #221932;
}

#ProjectList QScrollBar:vertical {
    width: 7px;
}
#ProjectList QScrollBar:horizontal {
    height: 7px;
}
#ProjectList QScrollBar:vertical, 
#ProjectList QScrollBar:horizontal {
    border: none;
    background: transparent;
    margin: 0;
}
#ProjectList QScrollBar::handle:vertical, 
#ProjectList QScrollBar::handle:horizontal {
    background: #775E88;
    border-radius: 3px;
    min-height: 20px;
    min-width: 20px;
}
#ProjectList QScrollBar::add-line:vertical,
#ProjectList QScrollBar::sub-line:vertical,
#ProjectList QScrollBar::add-line:horizontal,
#ProjectList QScrollBar::sub-line:horizontal,
#ProjectList QScrollBar::add-page:vertical,
#ProjectList QScrollBar::sub-page:vertical,
#ProjectList QScrollBar::add-page:horizontal,
#ProjectList QScrollBar::sub-page:horizontal {
    background: none;
}

#BottomBar {
    background-color: #221932;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
}

#BottomBar QLabel {
    color: #9882B9;
    font-family: 'Arial';
    font-size: 13px;
}

#BottomBar QPushButton {
    background-color: transparent;
    color: #9882B9;
    font-family: 'Arial';
    font-size: 13px;
    padding: 0px 0px;
    min-width: 0px;
    min-height: 0px;
}

#BottomBar QPushButton:hover {
    color:rgb(198, 183, 221);
    font-family: 'Arial';
    font-size: 13px;
}

#NoteList {
    border-radius: 8px;
    background-color: #221932;
}

#NoteWidget {
    background-color: #9882B9;
    border-radius: 8px;
}

#NoteWidget QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color:rgb(113, 97, 137);
    color: #221932;
    padding: 5px 10px;
}

#NoteWidget QPushButton:hover {
    background-color:rgb(69, 58, 87);
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
    background-color: rgb(79, 25, 50);
}

QPushButton:pressed {
    background-color:rgb(59, 16, 35);
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
    background-color:rgb(80, 27, 51);
}
)";

QString main_window_blue_theme = R"(
#main-window {
    background: #173C4C;
}

#main-window QLabel {
    font-weight: bold;
    color: #BDD1BD;
}

QScrollBar:vertical {
    width: 7px;
}
QScrollBar:horizontal {
    height: 7px;
}
QScrollBar:vertical, QScrollBar:horizontal {
    border: none;
    background: transparent;
    margin: 0;
}
QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
    background: rgb(103, 155, 177);
    border-radius: 3px;
    min-height: 20px;
    min-width: 20px;
}
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal,
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical,
QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
    background: none;
    height: 0;
    width: 0;
}

QScrollArea {
    border: none;
    background: transparent;
}

#ProjectList {
    background-color: #07142B;
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
    background-color:rgb(37, 92, 115);
}

#ProjectList::item:selected {
    background-color:rgb(73, 159, 158);
    color: #07142B;
}

#ProjectList QScrollBar:vertical {
    width: 7px;
}
#ProjectList QScrollBar:horizontal {
    height: 7px;
}
#ProjectList QScrollBar:vertical, 
#ProjectList QScrollBar:horizontal {
    border: none;
    background: transparent;
    margin: 0;
}
#ProjectList QScrollBar::handle:vertical, 
#ProjectList QScrollBar::handle:horizontal {
    background: rgb(103, 155, 177);
    border-radius: 3px;
    min-height: 20px;
    min-width: 20px;
}
#ProjectList QScrollBar::add-line:vertical,
#ProjectList QScrollBar::sub-line:vertical,
#ProjectList QScrollBar::add-line:horizontal,
#ProjectList QScrollBar::sub-line:horizontal,
#ProjectList QScrollBar::add-page:vertical,
#ProjectList QScrollBar::sub-page:vertical,
#ProjectList QScrollBar::add-page:horizontal,
#ProjectList QScrollBar::sub-page:horizontal {
    background: none;
}

#BottomBar {
    background-color: #07142B;
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

#BottomBar QPushButton {
    background-color: transparent;
    color: #BDD1BD;
    font-family: 'Arial';
    font-size: 13px;
    padding: 0px 0px;
    min-width: 0px;
    min-height: 0px;
}

#BottomBar QPushButton:hover {
    color:rgb(238, 242, 238);
    font-family: 'Arial';
    font-size: 13px;
}

#NoteList {
    border-radius: 8px;
    background-color: #07142B;
    border: 1px solid;
}

#NoteWidget {
    background-color:rgb(103, 155, 177);
    border-radius: 8px;
    border: 1px solid;
}

#NoteWidget QPushButton {
    font-family: 'Arial';
    font-size: 13px;
    font-weight: bold;
    border-radius: 10px;
    background-color:rgb(61, 104, 122);
    color: #BDD1BD;
    padding: 5px 10px;
}

#NoteWidget QPushButton:hover {
    background-color:rgb(24, 54, 66);
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
    border: 2px solid #568F7C;
    background-color: transparent;
}

QPushButton::hover#switch_theme_button_ {
    background-color: #568F7C;
}
QPushButton::pressed#switch_theme_button_ {
    background-color:rgb(68, 107, 94);
}
)";

}  // namespace Ui

#endif  // MAIN_WINDOW_STYLE_HPP