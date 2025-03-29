#ifndef MAIN_WINDOW_STYLE_HPP
#define MAIN_WINDOW_STYLE_HPP
#include <QString>

namespace Ui {

QString main_window_style = R"(
#main-window {
    background-color : white;
}
#ProjectList {
    background-color: #FED6BC;
    border: 1px solid #e0e0e0;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
    font-family: -apple-system, BlinkMacSystemFont, sans-serif;
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
    background: #f0f0f0;
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
    font-family: -apple-system, BlinkMacSystemFont, sans-serif;
    font-size: 14px;
}

#NoteWidget {
    background-color: #C6D8FF;
border-radius: 8px;

}

#NoteWidget QLabel {
   text-overflow: ellipsis;
}

#NoteList {
    border : 1px solid #A9A9A9;
border-radius : 8px;
}



)";

}

#endif