#include "login_window.h"
#include <QApplication>
#include <QLocale>
#include <QMainWindow>
#include <QScreen>
#include <QStyle>
#include <QTimer>
#include <iostream>
#include <ostream>
#include "applicationwindow.h"
#include "bottombar.h"
#include "database_manager.hpp"
#include "lr_dao.hpp"
#include "mainwindow.h"
#include "notelist.h"
#include "registration_window.h"
#include "serialization.hpp"
#include "login_window_style_sheet.h"

const std::vector<QString> LoginWindow::THEMES = {
    Ui::login_window_light_autumn_theme,
    Ui::login_window_dark_autumn_theme,
    Ui::login_window_dark_purple_theme,
    Ui::login_window_light_purple_theme,
    Ui::login_window_nature_flat_theme
};

LoginWindow::LoginWindow(QWidget *parent, int number_of_theme_)
    : QWidget(parent), ui(new Ui::LoginWindow), number_of_theme(number_of_theme_) {
    ui->setupUi(this);

    setFixedSize(380, 480);
    ui->input_login->setPlaceholderText("Введите логин:");
    ui->input_password->setPlaceholderText("Введите пароль:");

    ui->input_password->setEchoMode(QLineEdit::Password);
    setStyleSheet(THEMES[number_of_theme_]);

    connect(
        ui->switch_theme, &QPushButton::clicked, this, 
        &LoginWindow::on_switch_theme_clicked
    );

    connect(
        ui->switch_mode, &QPushButton::clicked, this,
        &LoginWindow::on_switch_mode_clicked
    );
    connect(
        ui->push_enter, &QPushButton::clicked, this,
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
        new RegistrationWindow(app_window, this->number_of_theme);

    app_window->setCentralWidget(registration_window);
    QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    int x = (screenGeometry.width() - registration_window->width()) / 2;
    int y = (screenGeometry.height() - registration_window->height()) / 2;
    app_window->move(x, y);

    this->close();
}

void LoginWindow::on_push_enter_clicked() {
    QString login = ui->input_login->text();
    QString password = ui->input_password->text();

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
            project_storage_model::Storage *storage =
                new project_storage_model::Storage();
            Serialization::get_storage(*storage, login.toStdString());

            Ui::MainWindow *main_window =
                new Ui::MainWindow(app_window, login.toStdString(), storage, this->number_of_theme);

            app_window->setCentralWidget(main_window);
            app_window->resize(800, 600);
            QRect screenGeometry =
                QApplication::primaryScreen()->availableGeometry();
            int x = (screenGeometry.width() - main_window->width()) / 2;
            int y = (screenGeometry.height() - main_window->height()) / 2;
            app_window->move(x, y);

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

void LoginWindow::on_switch_theme_clicked() {
    // Attention: костыль. 
    // Почему-то кнопка switch_theme дважды кликается, 
    // из-за чего темы переключаются не подряд, а через одну.
    // Поэтому ведем счетчик кликов и только на нечетных переключаем тему.
    if ((this->counter_on_switch_theme_clicks++)%2){
        this->number_of_theme = (this->number_of_theme+1)%THEMES.size();
        setStyleSheet(THEMES[this->number_of_theme]);
    }
}