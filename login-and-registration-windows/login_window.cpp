#include "login_window.h"
#include "database_manager.hpp"
#include "login_window_style_sheet.h"
#include "lr_dao.hpp"
#include "registration_window.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    setFixedSize(380, 480);
    ui->inputLogin->setPlaceholderText("Введите логин:");
    ui->inputPassword->setPlaceholderText("Введите пароль:");
    setStyleSheet(Ui::login_window_light_theme);
    ui->inputPassword->setEchoMode(QLineEdit::Password);

    connect(
        ui->switchMode, &QPushButton::clicked, this,
        &LoginWindow::on_switch_mode_clicked
    );
    connect(
        ui->pushEnter, &QPushButton::clicked, this,
        &LoginWindow::on_push_enter_clicked
    );
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::on_switch_mode_clicked() {
    hide();
    RegistrationWindow registration_window;
    registration_window.show();
    registration_window.exec();
    this->close();
}

void LoginWindow::on_push_enter_clicked() {
    QString login = ui->inputLogin->text();
    QString password = ui->inputPassword->text();

    if (!login.isEmpty() && !password.isEmpty()) {
        if (login.size() > 50) {
            QMessageBox::warning(
                this, "Ошибка",
                "Длина логина не должна превышать пятидесяти символов"
            );
        } else if (password.size() > 50) {
            QMessageBox::warning(
                this, "Ошибка",
                "Длина пароля не должна превышать пятидесяти символов"
            );
        } else if (LRDao::validate_user(login, password)) {
            QMessageBox::information(
                this, "Вход", "Вы успешно вошли! Добро пожаловать :)"
            );
            hide();
            //      here should be switch to main window? smth like this i
            //      guess:
            // MainWindow main_window;
            // main_window.show();
            // main_window.exec();
            this->close();
        } else {
            QMessageBox::warning(
                this, "Ошибка ввода данных", "Неверный логин или пароль!"
            );
        }
    } else {
        QMessageBox::warning(
            this, "Ошибка ввода данных", "Пожалуйста, заполните все поля!"
        );
    }
}
