/********************************************************************************
** Form generated from reading UI file 'login_window.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_WINDOW_H
#define UI_LOGIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushEnter;
    QLabel *enterLabel;
    QLineEdit *inputLogin;
    QLineEdit *inputPassword;
    QPushButton *switchMode;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QDialog *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(362, 600);
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(0, 0, 375, 501));
        pushEnter = new QPushButton(centralwidget);
        pushEnter->setObjectName("pushEnter");
        pushEnter->setGeometry(QRect(120, 280, 131, 51));
        pushEnter->setStyleSheet(QString::fromUtf8("font: 700 13pt \"Arial\";\n"
"border-radius: 10px;"));
        enterLabel = new QLabel(centralwidget);
        enterLabel->setObjectName("enterLabel");
        enterLabel->setGeometry(QRect(140, 130, 91, 41));
        enterLabel->setStyleSheet(QString::fromUtf8("font: 700 21pt \"Arial\";"));
        inputLogin = new QLineEdit(centralwidget);
        inputLogin->setObjectName("inputLogin");
        inputLogin->setGeometry(QRect(62, 175, 251, 41));
        inputLogin->setStyleSheet(QString::fromUtf8("border-radius: 10px;"));
        inputPassword = new QLineEdit(centralwidget);
        inputPassword->setObjectName("inputPassword");
        inputPassword->setGeometry(QRect(62, 225, 251, 41));
        inputPassword->setStyleSheet(QString::fromUtf8("border-radius: 10px;"));
        switchMode = new QPushButton(centralwidget);
        switchMode->setObjectName("switchMode");
        switchMode->setGeometry(QRect(80, 340, 211, 31));
        switchMode->setStyleSheet(QString::fromUtf8("font: 7pt \"Arial\";\n"
"border-radius: 10px;"));
        menubar = new QMenuBar(LoginWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 362, 26));
        statusbar = new QStatusBar(LoginWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(0, 0, 16, 25));

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QDialog *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Dialog", nullptr));
        pushEnter->setText(QCoreApplication::translate("LoginWindow", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        enterLabel->setText(QCoreApplication::translate("LoginWindow", "\320\222\321\205\320\276\320\264", nullptr));
        inputLogin->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        inputPassword->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        switchMode->setText(QCoreApplication::translate("LoginWindow", "\320\225\321\211\320\265 \320\275\320\265\321\202 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260? \320\227\320\260\321\200\320\265\320\263\320\265\321\201\321\202\321\200\320\270\321\200\321\203\320\271\321\202\320\265\321\201\321\214!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_WINDOW_H
