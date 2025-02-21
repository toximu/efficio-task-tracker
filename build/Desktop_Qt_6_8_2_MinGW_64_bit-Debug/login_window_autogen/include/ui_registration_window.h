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

class Ui_RegistrationWindow
{
public:
    QPushButton *pushRegistration;
    QPushButton *switchMode;
    QLineEdit *createLogin;
    QLineEdit *createPassword;
    QLineEdit *repeatPassword;
    QLabel *registrationLabel;

    void setupUi(QDialog *RegistrationWindow)
    {
        if (RegistrationWindow->objectName().isEmpty())
            RegistrationWindow->setObjectName("RegistrationWindow");
        RegistrationWindow->resize(390, 562);
        pushRegistration = new QPushButton(RegistrationWindow);
        pushRegistration->setObjectName("pushRegistration");
        pushRegistration->setGeometry(QRect(90, 290, 201, 51));
        pushRegistration->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Arial\";\n"
"border-radius: 10px;"));
        switchMode = new QPushButton(RegistrationWindow);
        switchMode->setObjectName("switchMode");
        switchMode->setGeometry(QRect(110, 350, 161, 31));
        switchMode->setStyleSheet(QString::fromUtf8("font: 7pt \"Arial\";\n"
"border-radius: 10px;"));
        createLogin = new QLineEdit(RegistrationWindow);
        createLogin->setObjectName("createLogin");
        createLogin->setGeometry(QRect(60, 140, 261, 41));
        createPassword = new QLineEdit(RegistrationWindow);
        createPassword->setObjectName("createPassword");
        createPassword->setGeometry(QRect(60, 190, 261, 41));
        repeatPassword = new QLineEdit(RegistrationWindow);
        repeatPassword->setObjectName("repeatPassword");
        repeatPassword->setGeometry(QRect(60, 240, 261, 41));
        registrationLabel = new QLabel(RegistrationWindow);
        registrationLabel->setObjectName("registrationLabel");
        registrationLabel->setGeometry(QRect(100, 90, 201, 51));
        registrationLabel->setStyleSheet(QString::fromUtf8("font: 700 19pt \"Arial\";"));

        retranslateUi(RegistrationWindow);

        QMetaObject::connectSlotsByName(RegistrationWindow);
    } // setupUi

    void retranslateUi(QDialog *RegistrationWindow)
    {
        RegistrationWindow->setWindowTitle(QCoreApplication::translate("RegistrationWindow", "Dialog", nullptr));
        pushRegistration->setText(QCoreApplication::translate("RegistrationWindow", "\320\227\320\260\321\200\320\265\320\263\320\265\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        switchMode->setText(QCoreApplication::translate("RegistrationWindow", "\320\243\320\266\320\265 \320\265\321\201\321\202\321\214 \320\260\320\272\320\272\320\260\321\203\320\275\321\202? \320\222\320\276\320\271\320\264\320\270\321\202\320\265!", nullptr));
        registrationLabel->setText(QCoreApplication::translate("RegistrationWindow", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegistrationWindow: public Ui_RegistrationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_WINDOW_H
