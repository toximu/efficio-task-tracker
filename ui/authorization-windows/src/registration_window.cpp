#include "registration_window.h"
#include <QApplication>
#include <QChar>
#include <QLocale>
#include <QMainWindow>
#include <QScreen>
#include <QMessageBox>
#include <QStyle>
#include <QTimer>
#include "applicationwindow.h"
#include "bottombar.h"
#include "database_manager.hpp"
#include "login_window.h"
#include "lr_dao.hpp"
#include "notelist.h"
#include "registration_window_style_sheet.h"
#include "ui_registration_window.h"
#include <vector>
#include "theme_manager.h"

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
    connect(ThemeManager::instance(), &ThemeManager::theme_changed,
            this, &RegistrationWindow::handle_theme_changed);
    handle_theme_changed(ThemeManager::instance()->current_theme());
}


void RegistrationWindow::handle_theme_changed(int theme) {
    this->setStyleSheet(THEMES[theme]);
}

void RegistrationWindow::on_switch_theme_clicked() {
    if ((this->counter_on_switch_theme_clicks++)%2){
        int next_theme = (ThemeManager::instance()->current_theme() + 1) % 5;
        ThemeManager::instance()->apply_theme(next_theme);
    }
}


RegistrationWindow::~RegistrationWindow() = default;

void RegistrationWindow::on_switch_mode_clicked() {
    QWidget *parent = this->parentWidget();

    QMainWindow *app_window = qobject_cast<QMainWindow *>(parent);

    if (QWidget *old = app_window->centralWidget()) {
        old->deleteLater();
    }
    LoginWindow *login_window = new LoginWindow(app_window);

    app_window->setCentralWidget(login_window);
    QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    int x = (screenGeometry.width() - login_window->width()) / 2;
    int y = (screenGeometry.height() - login_window->height()) / 2;
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

    for (const QChar ch : password) {
        if (!ch.isLetter() && !ch.isDigit()) {
            QMessageBox::warning(
                nullptr, "Ошибка",
                "Пароль должен содержать только символы латиницы и цифры"
            );
            return false;
        } else if (ch.isLetter()) {
            has_latin_letter = true;
        } else if (ch.isDigit()) {
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
    if ((this->counter_on_switch_theme_clicks++)%2){
        QString created_login = ui->create_login->text();
        QString created_password = ui->create_password->text();
        QString repeated_password = ui->repeat_password->text();

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
                int try_register_user =
                    LRDao::try_register_user(created_login, created_password);
                if (try_register_user == 0) {
                    QMessageBox::warning(
                        this, "Ошибка",
                        "Извините, внутренняя ошибка с базами данных."
                    );
                } else if (try_register_user == -1) {
                    QMessageBox::warning(
                        this, "Ошибка",
                        "Пользователь с таким именем уже существует. Пожалуйста, "
                        "придумайте другое!"
                    );
                } else {
                    QMessageBox::information(
                        this, "Регистрация",
                        "Вы успешно зарегистрировались! Пожалуйста, выполните вход."
                    );
                    on_switch_mode_clicked();
                }
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        }
    }
}