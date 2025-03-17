#ifndef TAGS_DIALOG_STYLES_H
#define TAGS_DIALOG_STYLES_H

#include "tags_dialog.h"

namespace Ui {
QString tags_dialog_light_theme = R"(
    QDialog {
        background-color: #f5f5f5;
    }

    /* Чекбоксы */
    QCheckBox {
        font-family: 'Arial';
        color: #727272;
        spacing: 5px;
    }

    QCheckBox::indicator {
        width: 16px;
        height: 16px;
        border-radius: 3px;
        border: 1px solid #727272;
        background-color: #ffffff;
    }

    QCheckBox::indicator:checked {
        background-color: #fea36b;
        border: 1px solid #fea36b;
        image: url(:/images/check.png);
    }

    QCheckBox::indicator:hover {
        border: 1px solid #fea36b;
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
        font-weight: bold;
        border: 1px solid #fea36b;
        width: 30px;
        height: 25px;
    }

    QPushButton#cancel_button:hover {
        background-color: #dadada;
    }
)";
}

#endif  // TAGS_DIALOG_STYLES_H
