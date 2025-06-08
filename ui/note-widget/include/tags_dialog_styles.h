#ifndef TAGS_DIALOG_STYLES_H
#define TAGS_DIALOG_STYLES_H

#include "tags_dialog.h"

namespace Ui {
QString tags_dialog_light_autumn_theme = R"(
    QDialog {
        background-color: #f5f5f5;
    }

    /* Чекбоксы */
    QCheckBox {
        font-family: 'Arial';
        color: #727272;
        spacing: 5px;
        background-color: transparent;
    }

    QCheckBox::indicator {
        width: 16px;
        height: 16px;
        border-radius: 3px;
        border: 1px solid #727272;
        background-color: transparent; 
    }

    QCheckBox::indicator:checked {
        background-color: #727272;
    }

    QCheckBox::indicator:hover {
        background-color: rgb(33, 44, 50);
    }

    /* Выпадающие списки цветов */
    QComboBox {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #ffffff;
        color: #727272;
        padding: 5px 10px;
        border: 1px solid #dadada;
    }

    QComboBox:hover {
        border: 1px solid #089083;
    }

    QComboBox::drop-down {
        width: 20px;
        border: none;
    }

    QComboBox::down-arrow {
        image: url(:/images/down_arrow.png);
    }

    QComboBox QAbstractItemView {
        background-color: #ffffff;
        color: #727272;
        selection-background-color: #fea36b;
        selection-color: white;
        border: 1px solid #dadada;
        border-radius: 5px;
    }

    /* Поля ввода имени тега */
    QLineEdit {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #ffffff;
        color: #727272;
        padding: 5px 10px;
        border: 1px solid #dadada;
    }

    QLineEdit:hover,
    QLineEdit:focus {
        border: 1px solid #089083;
    }

    QLineEdit::placeholder {
        color: #a0a0a0;
    }

    /* Кнопка OK */
    QPushButton#ok_button {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #fea36b;
        color: white;
        padding: 5px 10px;
        font-weight: bold;
        width: 30px;
        height: 25px;
    }

    QPushButton#ok_button:hover {
        background-color: #d58745;
    }

    /* Кнопка Отмена */
    QPushButton#cancel_button {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: white;
        color: #fea36b;
        padding: 5px 10px;
    }

    QPushButton#cancel_button:hover {
        background-color: #dadada;
    }
)";

QString tags_dialog_dark_autumn_theme = R"(
    QDialog {
        background-color: #202020;
    }

    /* Чекбоксы */
    QCheckBox {
        font-family: 'Arial';
        color: #727272;
        spacing: 5px;
        background-color: transparent;
    }
    QCheckBox::indicator {
        width: 16px;
        height: 16px;
        border-radius: 3px;
        border: 1px solid #727272;
        background-color: transparent; 
    }
    QCheckBox::indicator:hover {
        background-color: #727272;
    }
    QCheckBox::indicator:checked {
        background-color:rgb(0, 0, 0);
    }   

    /* Выпадающие списки цветов */
    QComboBox {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #363636;
        color: #BDD1BD;
        padding: 5px 10px;
        border: 1px solid #505050;
    }

    QComboBox:hover {
        border: 1px solid #fea36b;
    }

    QComboBox::drop-down {
        width: 20px;
        border: none;
    }

    QComboBox::down-arrow {
        image: url(:/images/down_arrow_light.png);
    }

    QComboBox QAbstractItemView {
        background-color: #363636;
        color: #BDD1BD;
        selection-background-color: #089083;
        selection-color: white;
        border: 1px solid #505050;
        border-radius: 5px;
    }

    /* Поля ввода имени тега */
    QLineEdit {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #363636;
        color: #BDD1BD;
        padding: 5px 10px;
        border: 1px solid #505050;
    }

    QLineEdit:hover,
    QLineEdit:focus {
        border: 1px solid #fea36b;
    }

    QLineEdit::placeholder {
        color: #727272;
    }

    /* Кнопка OK */
    QPushButton#ok_button {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #fea36b;
        color: #263238;
        padding: 5px 10px;
        font-weight: bold;
        width: 30px;
        height: 25px;
    }

    QPushButton#ok_button:hover {
        background-color: #d58745;
    }

    /* Кнопка Отмена */
    QPushButton#cancel_button {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #089083;
        color: white;
        padding: 5px 10px;
    }

    QPushButton#cancel_button:hover {
        background-color: #01635d;
    }

)";

QString tags_dialog_light_purple_theme = R"(
    QDialog {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,
            stop:0 #9882B9, stop:0.5 rgb(176, 157, 205), stop:1 rgb(125, 109, 148));
    }

    /* Чекбоксы */
    QCheckBox {
        font-family: 'Arial';
        color: rgb(42, 10, 25);
        spacing: 5px;
        background-color: transparent;
    }
    QCheckBox::indicator {
        width: 16px;
        height: 16px;
        border-radius: 3px;
        border: 1px solid rgb(42, 10, 25);
        background-color: transparent; 
    }
    QCheckBox::indicator:hover {
        background-color: rgb(218, 207, 235);
    }
    QCheckBox::indicator:checked {
        background-color: rgb(42, 10, 25);
    }

    /* Выпадающие списки цветов */
    QComboBox {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #E8C9E1;
        color: #221932;
        padding: 5px 10px;
        border: 1px solid #C98BB8;
    }

    QComboBox:hover {
        border: 1px solid #722548;
    }

    QComboBox::drop-down {
        width: 20px;
        border: none;
    }

    QComboBox::down-arrow {
        image: url(:/images/down_arrow_purple.png);
    }

    QComboBox QAbstractItemView {
        background-color: #E8C9E1;
        color: #221932;
        selection-background-color: #722548;
        selection-color: white;
        border: 1px solid #C98BB8;
        border-radius: 5px;
    }

    /* Поля ввода имени тега */
    QLineEdit {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #E8C9E1;
        color: #221932;
        padding: 5px 10px;
        border: 1px solid #C98BB8;
    }

    QLineEdit:hover,
    QLineEdit:focus {
        border: 1px solid #722548;
    }

    QLineEdit::placeholder {
        color: #7A6A9A;
    }

    /* Кнопка OK */
    QPushButton#ok_button {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #722548;
        color: #E8C9E1;
        padding: 5px 10px;
        font-weight: bold;
        width: 30px;
        height: 25px;
    }

    QPushButton#ok_button:hover {
        background-color: #5A1538;
    }

    /* Кнопка Отмена */
    QPushButton#cancel_button {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: rgb(42, 10, 25);
        color: rgb(218, 207, 235);
        padding: 5px 10px;
    }

    QPushButton#cancel_button:hover {
        background-color: rgb(27, 6, 16);
    }
)";

QString tags_dialog_dark_purple_theme = R"(
    QDialog {
        background-color: rgb(9, 6, 10);
    }

    /* Чекбоксы */
    QCheckBox {
        font-family: 'Arial';
        color: #9882B9;
        spacing: 5px;
        background-color: transparent;
    }
    QCheckBox::indicator {
        width: 16px;
        height: 16px;
        border-radius: 3px;
        border: 1px solid #9882B9;
        background-color: transparent; 
    }
    QCheckBox::indicator:hover {
        background-color: #221932;
    }
    QCheckBox::indicator:checked {
        background-color: #9882B9;
    }

    /* Выпадающие списки цветов */
    QComboBox {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #322242;
        color: #9882B9;
        padding: 5px 10px;
        border: 1px solid #775E88;
    }

    QComboBox:hover {
        border: 1px solid #722548;
    }

    QComboBox::drop-down {
        width: 20px;
        border: none;
    }

    QComboBox::down-arrow {
        image: url(:/images/down_arrow_purple.png);
    }

    QComboBox QAbstractItemView {
        background-color: #322242;
        color: #9882B9;
        selection-background-color: #722548;
        selection-color: white;
        border: 1px solid #775E88;
        border-radius: 5px;
    }

    /* Поля ввода имени тега */
    QLineEdit {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #322242;
        color: #9882B9;
        padding: 5px 10px;
        border: 1px solid #775E88;
    }

    QLineEdit:hover,
    QLineEdit:focus {
        border: 1px solid #722548;
    }

    QLineEdit::placeholder {
        color: #7A6A9A;
    }

    /* Кнопка OK */
    QPushButton#ok_button {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #722548;
        color: rgb(9, 6, 10);
        padding: 5px 10px;
        font-weight: bold;
        width: 30px;
        height: 25px;
    }

    QPushButton#ok_button:hover {
        background-color: #5A1538;
    }

    /* Кнопка Отмена */
    QPushButton#cancel_button {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: rgb(42, 10, 25);
        color: #9882B9;
        padding: 5px 10px;
    }

    QPushButton#cancel_button:hover {
        background-color: rgb(27, 6, 16);
    }
)";

QString tags_dialog_blue_theme = R"(
    QDialog {
        background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,
            stop:0 #173C4C, stop:0.5 rgb(30, 66, 65), stop:1 #07142B);
    }

    /* Чекбоксы */
    QCheckBox {
        font-family: 'Arial';
        color: #BDD1BD;
        spacing: 5px;
        background-color: transparent;
    }
    QCheckBox::indicator {
        width: 16px;
        height: 16px;
        border-radius: 3px;
        border: 1px solid #BDD1BD;
        background-color: transparent; 
    }
    QCheckBox::indicator:hover {
        background-color: #BDD1BD;
    }
    QCheckBox::indicator:checked {
        background-color: #07142B;
    }

    /* Выпадающие списки цветов */
    QComboBox {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #173C4C;
        color: #BDD1BD;
        padding: 5px 10px;
        border: 1px solid #326D6C;
    }

    QComboBox:hover {
        border: 1px solid #568F7C;
    }

    QComboBox::drop-down {
        width: 20px;
        border: none;
    }

    QComboBox::down-arrow {
        image: url(:/images/down_arrow_blue.png);
    }

    QComboBox QAbstractItemView {
        background-color: #173C4C;
        color: #BDD1BD;
        selection-background-color: #568F7C;
        selection-color: white;
        border: 1px solid #326D6C;
        border-radius: 5px;
    }

    /* Поля ввода имени тега */
    QLineEdit {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #173C4C;
        color: #BDD1BD;
        padding: 5px 10px;
        border: 1px solid #326D6C;
    }

    QLineEdit:hover,
    QLineEdit:focus {
        border: 1px solid #568F7C;
    }

    QLineEdit::placeholder {
        color: #7D9CAD;
    }

    /* Кнопка OK */
    QPushButton#ok_button {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #568F7C;
        color: #BDD1BD;
        padding: 5px 10px;
        font-weight: bold;
        width: 30px;
        height: 25px;
    }

    QPushButton#ok_button:hover {
        background-color: #326D6C;
    }

    /* Кнопка Отмена */
    QPushButton#cancel_button {
        font-family: 'Arial';
        border-radius: 10px;
        background-color: #326D6C;
        color: #BDD1BD;
        padding: 5px 10px;
        border: 1px solid #568F7C;
    }

    QPushButton#cancel_button:hover {
        background-color: #568F7C;
        color: #07142B;
    }
)";
}  // namespace Ui

#endif  // TAGS_DIALOG_STYLES_H