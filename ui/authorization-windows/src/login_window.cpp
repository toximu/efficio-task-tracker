#include "login_window.h"
#include "applicationwindow.h"
#include "lr_dao.hpp"
#include "mainwindow.h"
#include "registration_window.h"
#include "login_window_style_sheet.h"
#include "serialization.hpp"
#include "style_manager.h"
#include <QMessageBox>
#include <QScreen>

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
    ui->input_login->setPlaceholderText(tr("Введите логин:"));
    ui->input_password->setPlaceholderText(tr("Введите пароль:"));
    ui->input_password->setEchoMode(QLineEdit::Password);

    connect(ui->switch_theme, &QPushButton::clicked, this, 
        &LoginWindow::on_switch_theme_clicked, Qt::UniqueConnection);
    connect(ui->switch_mode, &QPushButton::clicked, this,
        &LoginWindow::on_switch_mode_clicked);
    connect(ui->push_enter, &QPushButton::clicked, this,
        &LoginWindow::on_push_enter_clicked);
    connect(StyleManager::instance(), &StyleManager::theme_changed,
            this, &LoginWindow::handle_theme_changed);

    handle_theme_changed(StyleManager::instance()->current_theme());
}

void LoginWindow::handle_theme_changed(int theme) {
    this->setStyleSheet(THEMES[theme]);
}

void LoginWindow::on_switch_theme_clicked() {
    if ((this->counter_on_switch_theme_clicks++) % 2) {
        int next_theme = (StyleManager::instance()->current_theme() + 1) % 5;
        StyleManager::instance()->apply_theme(next_theme);
    }
}

LoginWindow::~LoginWindow() = default;

void LoginWindow::on_switch_mode_clicked() {
    if (QMainWindow *app_window = qobject_cast<QMainWindow*>(this->parentWidget())) {
        RegistrationWindow *registration_window = new RegistrationWindow(app_window);
        switch_window(app_window, registration_window, 380, 480);
        this->close();
    }
}

void LoginWindow::on_push_enter_clicked() {
    if ((this->counter_on_switch_theme_clicks++) % 2) {
        // QString login = ui->input_login->text().trimmed();
        // QString password = ui->input_password->text();

        // if (login.isEmpty() || password.isEmpty()) {
        //     QMessageBox::warning(this, 
        //         tr("Ошибка ввода данных"), 
        //         tr("Пожалуйста, заполните все поля!"));
        //     return;
        // }

        // if (login.size() > 50) {
        //     QMessageBox::warning(this, 
        //         tr("Ошибка"), 
        //         tr("Длина логина не должна превышать пятидесяти символов"));
        //     return;
        // }

        // if (password.size() > 50) {
        //     QMessageBox::warning(this, 
        //         tr("Ошибка"), 
        //         tr("Длина пароля не должна превышать пятидесяти символов"));
        //     return;
        // }

        // if (!LRDao::validate_user(login, password)) {
        //     QMessageBox::warning(this, 
        //         tr("Ошибка ввода данных"), 
        //         tr("Неверный логин или пароль!"));
        //     return;
        // }

        // QMessageBox::information(this, 
        //     tr("Вход"), 
        //     tr("Вы успешно вошли! Добро пожаловать :)"));
        QString login = "user";
        if (QMainWindow *app_window = qobject_cast<QMainWindow*>(this->parentWidget())) {
            this->deleteLater();
            project_storage_model::Storage *storage = new project_storage_model::Storage();
            Serialization::get_storage(*storage, login.toStdString());

            Ui::MainWindow *main_window = new Ui::MainWindow(app_window, login.toStdString(), storage);
    
            connect(main_window, &Ui::MainWindow::logout_requested, app_window, [app_window, this]() {
                switch_to_login_window(app_window);
            });
            
            connect(main_window, &Ui::MainWindow::delete_account_requested, app_window, [app_window, this]() {
                switch_to_registration_window(app_window);
            });
            
            switch_window(app_window, main_window, 800, 600);
        }
    }
}

void LoginWindow::switch_window(QMainWindow *app_window, QWidget *new_window, int width, int height) {
    if (QWidget *old = app_window->centralWidget()) {
        old->deleteLater();
    }
    
    app_window->setCentralWidget(new_window);
    if (width > 0 && height > 0) {
        app_window->resize(width, height);
    }
    
    QRect screen_geometry = QApplication::primaryScreen()->availableGeometry();
    app_window->move(
        (screen_geometry.width() - width) / 2,
        (screen_geometry.height() - height) / 2
    );
    app_window->show();
}

void LoginWindow::switch_to_login_window(QMainWindow *app_window) {
    LoginWindow *login_window = new LoginWindow(app_window);
    switch_window(app_window, login_window, 380, 480);
}

void LoginWindow::switch_to_registration_window(QMainWindow *app_window) {
    RegistrationWindow *registration_window = new RegistrationWindow(app_window);
    switch_window(app_window, registration_window, 380, 480);
}