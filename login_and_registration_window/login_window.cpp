#include "login_window.h"
#include "login_window_style_sheet.h"
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
        QMessageBox::information(
            this, "Вход", "Вы успешно вошли! Добро пожаловать:)"
        );
        this->close();
    } else if (true) {  // here login and password validation will be added
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
    }
}
