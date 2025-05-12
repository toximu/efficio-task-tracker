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
#include "theme_manager.h"

#include <QDebug>

const std::vector<QString> LoginWindow::THEMES = {
    Ui::login_window_light_autumn_theme,
    Ui::login_window_dark_autumn_theme,
    Ui::login_window_dark_purple_theme,
    Ui::login_window_light_purple_theme,
    Ui::login_window_blue_theme
};

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    setFixedSize(380, 480);
    ui->input_login->setPlaceholderText("Введите логин:");
    ui->input_password->setPlaceholderText("Введите пароль:");

    ui->input_password->setEchoMode(QLineEdit::Password);
    handle_theme_changed(ThemeManager::instance()->current_theme());

    connect(
        ui->switch_theme, &QPushButton::clicked, this, 
        &LoginWindow::on_switch_theme_clicked
        , Qt::UniqueConnection);

    connect(
        ui->switch_mode, &QPushButton::clicked, this,
        &LoginWindow::on_switch_mode_clicked);
    connect(
        ui->push_enter, &QPushButton::clicked, this,
        &LoginWindow::on_push_enter_clicked);
    connect(ThemeManager::instance(), &ThemeManager::theme_changed,
            this, &LoginWindow::handle_theme_changed);
}

void LoginWindow::handle_theme_changed(int theme) {
    this->setStyleSheet(THEMES[theme]);
}

void LoginWindow::on_switch_theme_clicked() {
    if ((this->counter_on_switch_theme_clicks++)%2){
        int next_theme = (ThemeManager::instance()->current_theme() + 1) % 5;
        ThemeManager::instance()->apply_theme(next_theme);
    }
}

LoginWindow::~LoginWindow() = default;

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
    // if ((this->counter_on_switch_theme_clicks++)%2){
    //     QString login = ui->input_login->text();
    //     QString password = ui->input_password->text();

    //     if (!login.isEmpty() && !password.isEmpty()) {
    //         if (login.size() > 50) {
    //             QMessageBox::warning(
    //                 this, "Ошибка",
    //                 "Длина логина не должна превышать пятидесяти символов"
    //             );
    //         } else if (password.size() > 50) {
    //             QMessageBox::warning(
    //                 this, "Ошибка",
    //                 "Длина пароля не должна превышать пятидесяти символов"
    //             );
    //         } else if (LRDao::validate_user(login, password)) {
    //             QMessageBox::information(
    //                 this, "Вход", "Вы успешно вошли! Добро пожаловать :)"
    //             );
                QMainWindow *app_window = qobject_cast<QMainWindow *>(this->parentWidget());
                this->deleteLater();
                project_storage_model::Storage *storage =
                    new project_storage_model::Storage();
                QString login = "user";
                Serialization::get_storage(*storage, login.toStdString());

                Ui::MainWindow *main_window =
                    new Ui::MainWindow(app_window, login.toStdString(), storage);
    
                connect(main_window, &Ui::MainWindow::logout_requested, app_window, [app_window]() {
                    LoginWindow *login_window = new LoginWindow(app_window);
                    app_window->setCentralWidget(login_window);
                    app_window->resize(380, 480);
                    QRect screenGeometry =
                    QApplication::primaryScreen()->availableGeometry();
                    int x = (screenGeometry.width() - login_window->width()) / 2;
                    int y = (screenGeometry.height() - login_window->height()) / 2;
                    app_window->move(x, y);
                    app_window->show();
                });
                connect(main_window, &Ui::MainWindow::delete_account_requested, app_window, [app_window]() {
                    RegistrationWindow *registration_window = new RegistrationWindow(app_window);
                    app_window->setCentralWidget(registration_window);
                    app_window->resize(380, 480);                    
                    QRect screenGeometry =
                    QApplication::primaryScreen()->availableGeometry();
                    int x = (screenGeometry.width() - registration_window->width()) / 2;
                    int y = (screenGeometry.height() - registration_window->height()) / 2;
                    app_window->move(x, y);
                    app_window->show();
                });
                app_window->setCentralWidget(main_window);
                app_window->resize(800, 600);
                QRect screenGeometry =
                    QApplication::primaryScreen()->availableGeometry();
                int x = (screenGeometry.width() - 800) / 2;
                int y = (screenGeometry.height() - 600) / 2;
                app_window->move(x, y);
                app_window->show();
            // } else {
            //     QMessageBox::warning(
            //         this, "Ошибка ввода данных", "Неверный логин или пароль!"
            //     );
            // }
    //     } else {
    //         QMessageBox::warning(
    //             this, "Ошибка ввода данных", "Пожалуйста, заполните все поля!"
    //         );
    //     }
    // }
}