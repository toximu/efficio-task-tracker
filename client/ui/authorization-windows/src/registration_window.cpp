#include "registration_window.h"
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QScreen>
#include <QStyle>
#include <vector>
#include "login_window.h"
#include "lr_dao.hpp"
#include "registration_window_style_sheet.h"
#include "theme_manager.h"

using Efficio_proto::Storage;

const std::vector<QString> RegistrationWindow::THEMES = {
        Ui::registration_window_light_autumn_theme,
        Ui::registration_window_dark_autumn_theme,
        Ui::registration_window_dark_purple_theme,
        Ui::registration_window_light_purple_theme,
        Ui::registration_window_blue_theme
    };

RegistrationWindow::RegistrationWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::RegistrationWindow) {
    ui->setupUi(this);

    setFixedSize(380, 480);

    ui->create_login->setPlaceholderText("Введите логин:");
    ui->create_password->setPlaceholderText("Введите пароль:");
    ui->repeat_password->setPlaceholderText("Повторите пароль:");
    ui->create_password->setEchoMode(QLineEdit::Password);
    ui->repeat_password->setEchoMode(QLineEdit::Password);

    setAttribute(Qt::WA_StyledBackground, true);

    connect(
        ui->switch_theme, &QPushButton::clicked, this, 
        &RegistrationWindow::on_switch_theme_clicked
        , Qt::UniqueConnection);

    connect(
        ui->push_registration, &QPushButton::clicked, this,
        &RegistrationWindow::on_push_registration_clicked
        , Qt::UniqueConnection);
    connect(
        ui->switch_mode, &QPushButton::clicked, this,
        &RegistrationWindow::on_switch_mode_clicked
        , Qt::UniqueConnection);
    connect(ThemeManager::get_instance(), &ThemeManager::on_theme_changed,
            this, &RegistrationWindow::handle_theme_changed);
    handle_theme_changed(ThemeManager::get_instance()->get_current_theme());
}


void RegistrationWindow::handle_theme_changed(const int theme) {
    this->setStyleSheet(THEMES[theme]);
}

void RegistrationWindow::on_switch_theme_clicked() {
    if ((this->counter_on_switch_theme_clicks++)%2){
        int next_theme = (ThemeManager::get_instance()->get_current_theme() + 1) % 5;
        ThemeManager::get_instance()->apply_theme(next_theme);
    }
}


RegistrationWindow::~RegistrationWindow() {
    delete ui;
}

void RegistrationWindow::on_switch_mode_clicked() {
    QWidget *parent = this->parentWidget();

    auto *app_window = qobject_cast<QMainWindow *>(parent);

    if (QWidget *old = app_window->centralWidget()) {
        old->deleteLater();
    }
    Storage storage;
    auto *login_window = new LoginWindow(app_window);

    app_window->setCentralWidget(login_window);
    const QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    const int x = (screenGeometry.width() - login_window->width()) / 2;
    const int y = (screenGeometry.height() - login_window->height()) / 2;
    app_window->move(x, y);

    this->close();
}

bool RegistrationWindow::is_strong_and_valid_password(const QString &password) {
    if (password.length() < 8) {
        QMessageBox::warning(
            nullptr, "Ошибка: недостаточно надежный пароль",
            "Пароль должен содержать не менее восьми символов"
        );
        return false;
    }

    bool has_digit = false;
    bool has_latin_letter = false;

    for (const QChar symbol : password) {
        if (!symbol.isLetter() && !symbol.isDigit()) {
            QMessageBox::warning(
                nullptr, "Ошибка",
                "Пароль должен содержать только символы латиницы и цифры"
            );
            return false;
        }

        if (symbol.isLetter()) {
            has_latin_letter = true;
        } else if (symbol.isDigit()) {
            has_digit = true;
        }
    }

    if (!has_latin_letter) {
        QMessageBox::warning(
            nullptr, "Ошибка: недостаточно надежный пароль",
            "Пароль должен содержать хотя бы одну букву"
        );
        return false;
    }
    if (!has_digit) {
        QMessageBox::warning(
            nullptr, "Ошибка: недостаточно надежный пароль",
            "Пароль должен содержать хотя бы одну цифру"
        );
        return false;
    }

    return true;
}

void RegistrationWindow::on_push_registration_clicked() {
    if (this->counter_on_switch_theme_clicks++ % 2) {
        const QString created_login = ui->create_login->text();
        const QString created_password = ui->create_password->text();
        const QString repeated_password = ui->repeat_password->text();

        if (!created_login.isEmpty() && !created_password.isEmpty() &&
            !repeated_password.isEmpty()) {
            if (created_password != repeated_password) {
                QMessageBox::warning(this, "Ошибка", "Пароли не совпадают!");
            } else if (created_login.size() > 50) {
                QMessageBox::warning(
                    this, "Ошибка",
                    "Длина логина не должна превышать пятидесяти символов"
                );
            } else if (created_password.size() > 50) {
                QMessageBox::warning(
                    this, "Ошибка",
                    "Длина пароля не должна превышать пятидесяти символов"
                );
            } else if (is_strong_and_valid_password(created_password)) {
                const int try_register_user =
                    LRDao::try_register_user(created_login, created_password);
                if (try_register_user == 0) {
                    QMessageBox::warning(
                        this, "Ошибка",
                        "Извините, внутренняя ошибка с базами данных."
                    );
                } else if (try_register_user == -1) {
                    QMessageBox::warning(
                        this, "Ошибка",
                        "Пользователь с таким именем уже существует. "
                        "Пожалуйста, "
                        "придумайте другое!"
                    );
                } else {
                    QMessageBox::information(
                        this, "Регистрация",
                        "Вы успешно зарегистрировались! Пожалуйста, выполните "
                        "вход."
                    );
                    on_switch_mode_clicked();
                }
            }
        } else {
            QMessageBox::warning(
                this, "Ошибка", "Пожалуйста, заполните все поля."
            );
        }
    }
}
