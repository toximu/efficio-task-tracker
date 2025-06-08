#include "login_window.h"
#include "lr_dao.hpp"
#include "mainwindow.h"
#include "registration_window.h"
#include "serialization.hpp"
#include "style_manager.h"
#include "language_manager.h"
#include "model-proto/model.pb.h"
#include "client_implementation.h"
#include <QMessageBox>
#include <QScreen>
#include <QDebug>

using Efficio_proto::Storage;

LoginWindow::LoginWindow(ClientImplementation *client, QWidget *parent)
    : QWidget(parent), ui(new Ui::LoginWindow), client_(client) {
    ui->setupUi(this);

    setFixedSize(380, 480);
    
    ui->input_password->setEchoMode(QLineEdit::Password);

    connect(
        ui->switch_mode, &QPushButton::clicked, this,
        &LoginWindow::on_switch_mode_clicked
    );
    connect(
        ui->push_enter, &QPushButton::clicked, this,
        &LoginWindow::on_push_enter_clicked
    );
    connect(
        LanguageManager::instance(), &LanguageManager::language_changed, this,
        &LoginWindow::handle_language_changed
    );
    connect(
        ui->switch_theme, &QPushButton::clicked, this,
        &LoginWindow::on_switch_language_clicked, Qt::UniqueConnection
    );
    handle_language_changed(LanguageManager::instance()->current_language());
    setStyleSheet(Ui::login_window_light_autumn_theme);
}

void LoginWindow::handle_language_changed(std::string new_language) {
    if (new_language == "RU") {
        ui->input_login->setPlaceholderText(tr("Введите логин:"));
        ui->enter_label->setText(tr("Вход"));
        ui->input_password->setPlaceholderText(tr("Введите пароль:"));
        ui->switch_mode->setText(tr("Еще нет аккаунта? Зарегестрируйтесь!"));
        ui->switch_theme->setText(tr("RU"));
        ui->push_enter->setText(tr("Войти"));
    } else if (new_language == "EN") {
        ui->input_login->setPlaceholderText(tr("Enter login:"));
        ui->enter_label->setText(tr("Enter"));
        ui->input_password->setPlaceholderText(tr("Enter password:"));
        ui->switch_mode->setText(tr("Don't have an account yet? Register!"));
        ui->switch_theme->setText(tr("EN"));
        ui->push_enter->setText(tr("Login"));
    }
}

void LoginWindow::on_switch_language_clicked() {
    if (ui->switch_theme->text() == tr("RU")) {
        ui->switch_theme->setText(tr("EN"));
        LanguageManager::instance()->apply_language("EN");
    } else {
        ui->switch_theme->setText(tr("RU"));
        LanguageManager::instance()->apply_language("RU");
    }
}

LoginWindow::~LoginWindow() = default;

void LoginWindow::on_switch_mode_clicked() {
    if (QMainWindow *app_window =
            qobject_cast<QMainWindow *>(this->parentWidget())) {
        RegistrationWindow *registration_window =
            new RegistrationWindow(app_window);
        switch_window(app_window, registration_window, 380, 480);
        this->close();
    }
}

void LoginWindow::on_push_enter_clicked() {
    if ((this->counter_on_switch_theme_clicks++) % 2) {
        QString login = ui->input_login->text().trimmed();
        QString password = ui->input_password->text();
        std::string lang = LanguageManager::instance()->current_language();

        if (login.isEmpty() || password.isEmpty()) {
            if (lang == "RU") {
                QMessageBox::warning(this, "Ошибка ввода данных", "Пожалуйста, заполните все поля!");
            } else {
                QMessageBox::warning(this, "Input Error", "Please fill in all the fields!");
            }
            return;
        }

        if (login.size() > 50) {
            if (lang == "RU") {
                QMessageBox::warning(this, "Ошибка", "Длина логина не должна превышать пятидесяти символов");
            } else {
                QMessageBox::warning(this, "Error", "Login must not exceed fifty characters");
            }
            return;
        }

        if (password.size() > 50) {
            if (lang == "RU") {
                QMessageBox::warning(this, "Ошибка", "Длина пароля не должна превышать пятидесяти символов");
            } else {
                QMessageBox::warning(this, "Error", "Password must not exceed fifty characters");
            }
            return;
        }

        auto user = new User();
        user->set_login(login.toStdString());
        user->set_hashed_password(password.toStdString());

        if (!client_->try_authenticate_user(user))  {
            if (lang == "RU") {
                QMessageBox::warning(this, "Ошибка ввода данных", "Неверный логин или пароль!");
            } else {
                QMessageBox::warning(this, "Login Error", "Incorrect login or password!");
            }
            return;
        }

        if (lang == "RU") {
            QMessageBox::information(
                this, "Вход", "Вы успешно вошли. Добро пожаловать!"
            );
        } else {
            QMessageBox::information(
                this, "Login", "You have successfully logged in. Welcome!"
            );
        }

        if (QMainWindow *app_window =
                qobject_cast<QMainWindow *>(this->parentWidget())) {
            this->deleteLater();
            project_storage_model::Storage *storage =
                new project_storage_model::Storage();
            Serialization::get_storage(*storage, login.toStdString());

            Ui::MainWindow *main_window =
                new Ui::MainWindow(app_window, login.toStdString(), storage);

            connect(
                main_window, &Ui::MainWindow::logout_requested, app_window,
                [app_window, this]() { switch_to_login_window(app_window); }
            );

            connect(
                main_window, &Ui::MainWindow::delete_account_requested,
                app_window,
                [app_window, this]() {
                    switch_to_registration_window(app_window);
                }
            );

            switch_window(app_window, main_window, 800, 600);
        }
    }
}

void LoginWindow::switch_window(
    QMainWindow *app_window,
    QWidget *new_window,
    int width,
    int height
) {
    if (QWidget *old = app_window->centralWidget()) {
        old->deleteLater();
    }

    app_window->setCentralWidget(new_window);
    app_window->resize(width, height);
    
    QRect screen_geometry = QApplication::primaryScreen()->availableGeometry();
    app_window->move(
        (screen_geometry.width() - width) / 2,
        (screen_geometry.height() - height) / 2
    );
    app_window->show();
}

void LoginWindow::switch_to_registration_window(QMainWindow *app_window) {
    RegistrationWindow *registration_window = new RegistrationWindow(client_, app_window);
    switch_window(app_window, registration_window, 380, 480);
}