#ifndef MAIN_WINDOW_STYLE_HPP
#define MAIN_WINDOW_STYLE_HPP
#include <QString>

namespace Ui {

QString main_window_style = R"(
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
    font-size: 14px;
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
    font-size: 14px;
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

)";

}  // namespace Ui

#endif  // MAIN_WINDOW_STYLE_HPP