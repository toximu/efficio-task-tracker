#include "./login_window.h"
#include "./registration_window.h"
#include "./registration_window_style_sheet.h"

RegistrationWindow::RegistrationWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);

    setFixedSize(380, 480);

    ui->createLogin->setPlaceholderText("Введите логин:");
    ui->createPassword->setPlaceholderText("Введите пароль:");
    ui->repeatPassword->setPlaceholderText("Повторите пароль:");
    setStyleSheet(Ui::registration_window_light_theme);
    ui->createPassword->setEchoMode(QLineEdit::Password);
    ui->repeatPassword->setEchoMode(QLineEdit::Password);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}


void RegistrationWindow::on_switchMode_clicked()
{
    hide();
    LoginWindow login_window;
    login_window.show();
    login_window.exec();
}

void RegistrationWindow::on_pushRegistration_clicked()
{
    QString created_login = ui->createLogin->text();
    QString created_password = ui->createPassword->text();
    QString repeated_password = ui->repeatPassword->text();
    if (created_login.size()!=0 && created_password.size()!= 0 && repeated_password.size()!= 0){
        if (created_password!=repeated_password){
            QMessageBox::warning(this, "Ошибка", "Пароли не совпадают!");
        } else {
            QMessageBox::information(this, "Авторизация", "Вы успешно авторизовались! Теперь, пожалуйста, еще раз выполните вход.");
            hide();
            LoginWindow login_window;
            login_window.show();
            login_window.exec();
        }
    }
}


