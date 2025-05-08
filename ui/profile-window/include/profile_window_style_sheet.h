#ifndef PROFILE_WINDOW_STYLE_HPP
#define PROFILE_WINDOW_STYLE_HPP

#include <QString>

namespace Ui {

QString profile_window_light_autumn_theme = R"(
    QDialog {
        background-color: #f5f5f5;
    }

    QPushButton {
        font-family: 'Arial';
        font-size: 13px;
        font-weight: bold;
        border-radius: 10px;
        padding: 5px 10px;
        width: 60px;
        height: 25px;
    }

    QPushButton#logout_button {
        background-color: #fea36b;
        color: white;
    }

    QPushButton#logout_button:hover {
        background-color:rgb(245, 148, 89);
    }

    QPushButton#logout_button:pressed {
        background-color:rgb(238, 122, 50);
    }

    QPushButton#delete_button {
        background-color: #fea36b;
        color: white;
    }

    QPushButton#delete_button:hover {
        background-color:rgb(245, 148, 89);
    }

    QPushButton#delete_button:pressed {
        background-color:rgb(238, 122, 50);
    }
    
    QPushButton#stats_button {
        background-color: #089083;
        color: #f5f5f5;
        border: none;
        padding: 10px;
        margin: 2px;
    }
    
    QPushButton#stats_button:hover {
        background-color:rgb(8, 82, 74);
    }

    QPushButton#stats_button:pressed {
        background-color: #089083;
    }
    
    QPushButton#settings_button {
        background-color: rgb(33, 44, 50);
        color: #f5f5f5;
        padding: 2px;
        font-size: 35px;
        border-radius: 15px;
        width: 30px;
        height: 30px;
    }
    
    QPushButton#settings_button:hover {
        background-color: rgb(14, 17, 19);
    }

    QPushButton#settings_button:pressed {
        background-color: rgb(4, 4, 5);
    }
)";

QString profile_window_dark_autumn_theme = R"(
    QDialog {
        background-color:rgb(43, 43, 43);
    }

    QPushButton {
        font-family: 'Arial';
        font-size: 13px;
        font-weight: bold;
        border-radius: 10px;
        padding: 5px 10px;
        width: 60px;
        height: 25px;
    }
    
    QPushButton#logout_button {
        background-color:rgb(211, 139, 95);
        color: #263238;
    }
    
    QPushButton#logout_button:hover {
        background-color:rgb(181, 114, 59);
    }

    QPushButton#logout_button:pressed {
        background-color:rgb(158, 94, 45);
    }

    QPushButton#delete_button {
        background-color:rgb(211, 139, 95);
        color: #263238;
    }
    
    QPushButton#delete_button:hover {
        background-color:rgb(181, 114, 59);
    }

    QPushButton#delete_button:pressed {
        background-color:rgb(158, 94, 45);
    }
    
    QPushButton#stats_button {
        background-color: #089083;
        color: #f5f5f5;
        border: none;
        padding: 10px;
        margin: 2px;
    }
    
    QPushButton#stats_button:hover {
        background-color:rgb(12, 114, 104);
    }

    QPushButton#stats_button:pressed {
        background-color:rgb(14, 101, 92);
    }
    
    QPushButton#settings_button {
        background-color:rgb(0, 0, 0);
        color:  #f5f5f5;
        padding: 2px;
        font-size: 35px;
        border-radius: 15px;
        width: 30px;
        height: 30px;
    }
    
    QPushButton#settings_button:hover {
        background-color:rgb(54, 54, 54);
    }

    QPushButton#settings_button:pressed {
        background-color: rgb(99, 99, 99);
    }
)";

QString profile_window_light_purple_theme = R"(
    QDialog {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,
            stop:0 #9882B9, stop:0.5 rgb(176, 157, 205), stop:1 rgb(103, 88, 126));
    }

    QPushButton {
        font-family: 'Arial';
        font-size: 13px;
        font-weight: bold;
        border-radius: 10px;
        padding: 5px 10px;
        width: 60px;
        height: 25px;
    }

    QPushButton#logout_button {
        background-color: #722548;
        color: #9882B9;
    }

    QPushButton#logout_button:hover {
        background-color:rgb(82, 27, 51);
    }

    QPushButton#logout_button:pressed {
        background-color:rgb(64, 21, 40);
    }

    QPushButton#delete_button {
        background-color: #722548;
        color: #9882B9;
    }

    QPushButton#delete_button:hover {
        background-color:rgb(84, 27, 53);
    }

    QPushButton#delete_button:pressed {
        background-color:rgb(64, 21, 40);
    }
    
    QPushButton#stats_button {
        background-color: rgb(42, 10, 25);
        color: rgb(163, 148, 184);
        border: none;
        padding: 10px;
        margin: 2px;
    }
    
    QPushButton#stats_button:hover {
        background-color: rgb(19, 5, 11);
    }

    QPushButton#stats_button:pressed {
        background-color:rgb(42, 10, 25);
    }
    
    QPushButton#settings_button {
        background-color: rgb(221, 210, 238);
        color: rgb(42, 10, 25);
        padding: 2px;
        font-size: 35px;
        border-radius: 15px;
        width: 30px;
        height: 30px;
    }
    
    QPushButton#settings_button:hover {
        background-color: rgb(177, 166, 194);
    }

    QPushButton#settings_button:pressed {
        background-color: rgb(152, 140, 170);
    }
)";

QString profile_window_dark_purple_theme = R"(
    QDialog {
        background-color: rgb(9, 6, 10);
    }

    QPushButton {
        font-family: 'Arial';
        font-size: 13px;
        font-weight: bold;
        border-radius: 10px;
        padding: 5px 10px;
        width: 60px;
        height: 25px;
    }

    QPushButton#logout_button {
        background-color: #722548;
        color: #060407;
    }

    QPushButton#logout_button:hover {
        background-color: #722548;
    }

    QPushButton#logout_button:pressed {
        background-color:rgb(79, 24, 49);
    }

    QPushButton#delete_button {
        background-color: #722548;
        color: #060407;
    }

    QPushButton#delete_button:hover {
        background-color: #722548;
    }

    QPushButton#delete_button:pressed {
        background-color:rgb(79, 24, 49);
    }
    
    QPushButton#stats_button {
        background-color: rgb(42, 10, 25);
        color: #9882B9;
        border: none;
        padding: 10px;
        margin: 2px;
    }
    
    QPushButton#stats_button:hover {
        background-color:rgb(22, 5, 13);
    }

    QPushButton#stats_button:pressed {
        background-color:rgb(11, 3, 7);
    }
    
    QPushButton#settings_button {
        background-color: #221932;
        color: #9882B9;
        padding: 2px;
        font-size: 35px;
        border-radius: 15px;
        width: 30px;
        height: 30px;
    }
    
    QPushButton#settings_button:hover {
        background-color:rgb(21, 16, 31);
    }

    QPushButton#settings_button:pressed {
        background-color:rgb(4, 3, 5);
    }
)";

QString profile_window_blue_theme = R"(
    QDialog {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,
            stop:0 #173C4C, stop:0.5 #326D6C, stop:1 #07142B);
    }

    QPushButton {
        font-family: 'Arial';
        font-size: 13px;
        font-weight: bold;
        border-radius: 10px;
        padding: 5px 10px;
        width: 60px;
        height: 25px;
        border: none;
    }

    QPushButton#logout_button {
        background-color: #BDD1BD;
        color: #173C4C;
    }

    QPushButton#logout_button:hover {
        background-color:rgb(158, 176, 158);
    }

    QPushButton#logout_button:pressed {
        background-color:rgb(141, 157, 141);
    }

    QPushButton#delete_button {
        background-color: #BDD1BD;
        color: #173C4C;
    }

    QPushButton#delete_button:hover {
        background-color:rgb(158, 176, 158);
    }

    QPushButton#delete_button:pressed {
        background-color:rgb(141, 157, 141);
    }
    
    QPushButton#stats_button {
        background-color: #326D6C;
        color: #BDD1BD;
        border: none;
        padding: 10px;
        margin: 2px;
    }
    
    QPushButton#stats_button:hover {
        background-color:rgb(47, 89, 89);
    }

    QPushButton#stats_button:pressed {
        background-color:rgb(31, 69, 85);
    }
    
    QPushButton#settings_button {
        background-color: #07142B;
        color: #BDD1BD;
        padding: 2px;
        font-size: 35px;
        border-radius: 15px;
        width: 30px;
        height: 30px;
    }
    
    QPushButton#settings_button:hover {
        background-color:rgb(4, 12, 26);
    }

    QPushButton#settings_button:pressed {
        background-color:rgb(2, 3, 5);
    }
)";

} // namespace Ui

#endif // PROFILE_WINDOW_STYLE_HPP