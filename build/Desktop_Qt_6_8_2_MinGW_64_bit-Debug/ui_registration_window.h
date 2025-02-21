/********************************************************************************
** Form generated from reading UI file 'registration_window.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_WINDOW_H
#define UI_REGISTRATION_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_registration_window
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_2;

    void setupUi(QDialog *registration_window)
    {
        if (registration_window->objectName().isEmpty())
            registration_window->setObjectName("registration_window");
        registration_window->resize(374, 531);
        registration_window->setStyleSheet(QString::fromUtf8("background-color: #202020"));
        pushButton = new QPushButton(registration_window);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(90, 350, 191, 41));
        pushButton->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Arial\"; \n"
"background-color: rgb(213, 135, 69); \n"
"color: rgb(0, 0, 0);\n"
"border-radius: 10px;"));
        pushButton_2 = new QPushButton(registration_window);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(190, 400, 93, 29));
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 700 8pt \"Arial\"; \n"
"background-color: rgb(255, 255, 255); \n"
"color: rgb(0, 0, 0);\n"
"border-radius: 10px;"));
        label = new QLabel(registration_window);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 400, 131, 20));
        label->setStyleSheet(QString::fromUtf8("color = rgb(255, 255, 255)"));
        lineEdit = new QLineEdit(registration_window);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(90, 230, 191, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("background: #000; border-radius: 10px;"));
        lineEdit_2 = new QLineEdit(registration_window);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(90, 290, 191, 41));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background: #000; border-radius: 10px;"));
        label_2 = new QLabel(registration_window);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 170, 91, 41));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 9pt \"Arial\"; color = rgb(255, 255, 255)"));

        retranslateUi(registration_window);

        QMetaObject::connectSlotsByName(registration_window);
    } // setupUi

    void retranslateUi(QDialog *registration_window)
    {
        registration_window->setWindowTitle(QCoreApplication::translate("registration_window", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("registration_window", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("registration_window", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        label->setText(QCoreApplication::translate("registration_window", "\320\243\320\266\320\265 \320\265\321\201\321\202\321\214 \320\260\320\272\320\272\320\260\321\203\320\275\321\202?", nullptr));
        label_2->setText(QCoreApplication::translate("registration_window", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registration_window: public Ui_registration_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_WINDOW_H
