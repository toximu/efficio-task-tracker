#ifndef MAIN_WINDOW_STYLE_HPP
#define MAIN_WINDOW_STYLE_HPP
#include <QString>

namespace Ui {

QString main_window_style = R"(
#main-window {
    background-color : white;

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
    background-color: #FED6BC;
    border: 1px solid #e0e0e0;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
    font-family: 'Arial';
    font-weight: bold;
    font-size: 14px;
    color: #000000;
}

#ProjectList::item {
    background-color: transparent;
    border: none;
    padding: 10px;
    margin: 2px;
    border-radius: 6px;
}

#ProjectList::item:hover {
    background-color: #f5f5f5;
}

#ProjectList::item:selected {
    background-color: #007aff;
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
    background-color: black;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
}

#BottomBar QLabel {
    color : white;
    font-family: 'Arial';
    font-size: 14px;
}

#NoteList {
    border : none;
    margin : 0;
    background: transparent;
}

#NoteWidget {
    background-color: #A2E4B8;
    border-radius: 8px;
    margin: 0;
}

#NoteWidget QPushButton {
    font-family: 'Arial';
    border-radius: 10px;
    background-color: #4D9970;
    color: white;
    padding: 5px 10px;
}


QPushButton {
    font-family: 'Arial';
    border-radius: 10px;
    background-color: #fea36b;
    color: white;
    padding: 5px 10px;
}

)";

}

#endif