#include "login_window.h"
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QScreen>
#include <QStyle>
#include "model-proto/model.pb.h"
#include "login_window_style_sheet.h"
#include "lr_dao.hpp"
#include "registration_window.h"
#include "theme_manager.h"

using Efficio_proto::Storage;

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
    handle_theme_changed(ThemeManager::get_instance()->get_current_theme());

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
    connect(ThemeManager::get_instance(), &ThemeManager::on_theme_changed,
            this, &LoginWindow::handle_theme_changed);
}


void LoginWindow::handle_theme_changed(int theme) {
    this->setStyleSheet(THEMES[theme]);
}

void LoginWindow::on_switch_theme_clicked() {
    if (this->counter_on_switch_theme_clicks++ % 2) {
        const int next_theme =
            (ThemeManager::get_instance()->get_current_theme() + 1) % 5;
        ThemeManager::get_instance()->apply_theme(next_theme);
    }
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::on_switch_mode_clicked() {
    QWidget *parent = this->parentWidget();

    auto *app_window = qobject_cast<QMainWindow *>(parent);

    if (QWidget *old = app_window->centralWidget()) {
        old->deleteLater();
    }
    Storage storage;
    auto *registration_window =
        new RegistrationWindow(app_window);

    app_window->setCentralWidget(registration_window);
    QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    int x = (screenGeometry.width() - registration_window->width()) / 2;
    int y = (screenGeometry.height() - registration_window->height()) / 2;
    app_window->move(x, y);

    this->close();
}

void LoginWindow::on_push_enter_clicked() {
    if (this->counter_on_switch_theme_clicks++ % 2) {
        const QString login = ui->input_login->text();
        const QString password = ui->input_password->text();

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

                const QMainWindow *app_window = qobject_cast<QMainWindow *>(parent);

                if (QWidget *old = app_window->centralWidget()) {
                    old->deleteLater();
                }

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
}
