#include "login_window.h"
#include <QApplication>
#include <QLocale>
#include <QMainWindow>
#include <QScreen>
#include <QStyle>
#include <QTimer>
#include "applicationwindow.h"
#include "bottombar.h"
#include "database_manager.hpp"
#include "login_window_style_sheet.h"
#include "lr_dao.hpp"
#include "mainwindow.h"
#include "notelist.h"
#include "registration_window.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::LoginWindow) {
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
    QWidget *parent = this->parentWidget();

    QMainWindow *app_window = qobject_cast<QMainWindow *>(parent);

    if (QWidget *old = app_window->centralWidget()) {
        old->deleteLater();
    }
    project_storage_model::Storage storage;
    RegistrationWindow *registration_window =
        new RegistrationWindow(app_window);

    app_window->setCentralWidget(registration_window);
    QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    int x = (screenGeometry.width() - registration_window->width()) / 2;
    int y = (screenGeometry.height() - registration_window->height()) / 2;
    app_window->move(x, y);

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
            QWidget *parent = this->parentWidget();

            QMainWindow *app_window = qobject_cast<QMainWindow *>(parent);

            if (QWidget *old = app_window->centralWidget()) {
                old->deleteLater();
            }
            // todo load all projects of user to storage
            Ui::MainWindow *main_window =
                new Ui::MainWindow(app_window, login.toStdString(), std::make_unique<project_storage_model::Storage>());

            app_window->setCentralWidget(main_window);
            app_window->resize(800,600);
            // QRect screenGeometry =
            //     QApplication::primaryScreen()->availableGeometry();
            // int x = (screenGeometry.width() - main_window->width()) / 2;
            // int y = (screenGeometry.height() - main_window->height()) / 2;
            // app_window->move(x, y);

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