#include "registration_window.h"
#include "./login_window.h"
#include "./login_window_style_sheet.h"


LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    setFixedSize(380, 480);
    ui->inputLogin->setPlaceholderText("Введите логин:");
    ui->inputPassword->setPlaceholderText("Введите пароль:");
    setStyleSheet(Ui::login_window_light_theme);
    ui->inputPassword->setEchoMode(QLineEdit::Password);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_switchMode_clicked()
{
    hide();
    RegistrationWindow registration_window;
    registration_window.show();
    registration_window.exec();
    this->close();
}

void LoginWindow::on_pushEnter_clicked()
{
    QString login = ui->inputLogin->text();
    QString password = ui->inputPassword->text();
    if (login.size()!=0  && password.size()!= 0){
        QMessageBox::information(this, "Вход", "Вы успешно вошли! Добро пожаловать:)");
        this->close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
    }
}
