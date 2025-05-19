#include "registration_window.h"
#include <QMessageBox>
#include <QScreen>
#include "lr_dao.hpp"
#include "login_window.h"
#include "style_manager.h"
#include "language_manager.h"
#include "registration_window_style_sheet.h"

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

    ui->create_login->setPlaceholderText(tr("Введите логин:"));
    ui->create_password->setPlaceholderText(tr("Введите пароль:"));
    ui->repeat_password->setPlaceholderText(tr("Повторите пароль:"));
    ui->create_password->setEchoMode(QLineEdit::Password);
    ui->repeat_password->setEchoMode(QLineEdit::Password);

    setAttribute(Qt::WA_StyledBackground, true);

    connect(ui->switch_theme, &QPushButton::clicked, this, 
        &RegistrationWindow::on_switch_theme_clicked, Qt::UniqueConnection);
    connect(ui->push_registration, &QPushButton::clicked, this,
        &RegistrationWindow::on_push_registration_clicked, Qt::UniqueConnection);
    connect(ui->switch_mode, &QPushButton::clicked, this,
        &RegistrationWindow::on_switch_mode_clicked, Qt::UniqueConnection);
    connect(StyleManager::instance(), &StyleManager::theme_changed,
            this, &RegistrationWindow::handle_theme_changed);
    
    handle_theme_changed(StyleManager::instance()->current_theme());
    connect(LanguageManager::instance(), &LanguageManager::language_changed,
            this, &RegistrationWindow::handle_language_changed
    );
    handle_language_changed(LanguageManager::instance()->current_language());
}

void RegistrationWindow::handle_language_changed(std::string new_language) {
    if (new_language == "RU") {
        ui->create_login->setPlaceholderText(tr("Введите логин:"));
        ui->create_password->setPlaceholderText(tr("Введите пароль:"));
        ui->repeat_password->setPlaceholderText(tr("Повторите пароль:"));
        ui->switch_mode->setText(tr("Уже есть аккаунт? Войдите!"));
        ui->switch_theme->setText(tr("Тема"));
        ui->push_registration->setText(tr("Already have an account? Login!"));
    } 
    else if (new_language == "EN") {
        ui->create_login->setPlaceholderText(tr("Enter login:"));
        ui->create_password->setPlaceholderText(tr("Enter password:"));
        ui->repeat_password->setPlaceholderText(tr("Repeat password:"));
        ui->switch_mode->setText(tr("Back"));
        ui->switch_theme->setText(tr("Theme"));
        ui->push_registration->setText(tr("Register"));
    }
}



void RegistrationWindow::handle_theme_changed(int theme) {
    this->setStyleSheet(THEMES[theme]);
}

void RegistrationWindow::on_switch_theme_clicked() {
    if ((this->counter_on_switch_theme_clicks++)%2) {
        int next_theme = (StyleManager::instance()->current_theme() + 1) % 5;
        StyleManager::instance()->apply_theme(next_theme);
    }
}

RegistrationWindow::~RegistrationWindow() = default;

void RegistrationWindow::on_switch_mode_clicked() {
    if (QMainWindow *app_window = qobject_cast<QMainWindow*>(this->parentWidget())) {
        if (QWidget *old = app_window->centralWidget()) {
            old->deleteLater();
        }
        
        LoginWindow *login_window = new LoginWindow(app_window);
        app_window->setCentralWidget(login_window);
        
        QRect screen_geometry = QApplication::primaryScreen()->availableGeometry();
        app_window->move(
            (screen_geometry.width() - login_window->width()) / 2,
            (screen_geometry.height() - login_window->height()) / 2
        );
        
        this->close();
    }
}

bool RegistrationWindow::is_strong_and_valid_password(const QString &password) {
    std::string lang = LanguageManager::instance()->current_language();

    if (password.length() < 8) {
        if (lang == "RU") {
            QMessageBox::warning(nullptr, "Ошибка: недостаточно надежный пароль", "Пароль должен содержать не менее восьми символов");
        } else {
            QMessageBox::warning(nullptr, "Error: Weak Password", "Password must be at least 8 characters long");
        }
        return false;
    }

    bool has_digit = false;
    bool has_latin_letter = false;

    for (const QChar &ch : password) {
        if (!ch.isLetter() && !ch.isDigit()) {
            if (lang == "RU") {
                QMessageBox::warning(nullptr, "Ошибка", "Пароль должен содержать только символы латиницы и цифры");
            } else {
                QMessageBox::warning(nullptr, "Error", "Password must contain only Latin letters and digits");
            }
            return false;
        } else if (ch.isLetter()) {
            has_latin_letter = true;
        } else if (ch.isDigit()) {
            has_digit = true;
        }
    }

    if (!has_latin_letter) {
        if (lang == "RU") {
            QMessageBox::warning(nullptr, "Ошибка: недостаточно надежный пароль", "Пароль должен содержать хотя бы одну букву");
        } else {
            QMessageBox::warning(nullptr, "Error: Weak Password", "Password must contain at least one letter");
        }
        return false;
    }

    if (!has_digit) {
        if (lang == "RU") {
            QMessageBox::warning(nullptr, "Ошибка: недостаточно надежный пароль", "Пароль должен содержать хотя бы одну цифру");
        } else {
            QMessageBox::warning(nullptr, "Error: Weak Password", "Password must contain at least one digit");
        }
        return false;
    }

    return true;
}

void RegistrationWindow::on_push_registration_clicked() {
    if ((this->counter_on_switch_theme_clicks++) % 2) {
        QString created_login = ui->create_login->text().trimmed();
        QString created_password = ui->create_password->text();
        QString repeated_password = ui->repeat_password->text();

        std::string lang = LanguageManager::instance()->current_language();

        if (created_login.isEmpty() || created_password.isEmpty() || repeated_password.isEmpty()) {
            if (lang == "RU") {
                QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
            } else {
                QMessageBox::warning(this, "Error", "Please fill in all the fields.");
            }
            return;
        }

        if (created_password != repeated_password) {
            if (lang == "RU") {
                QMessageBox::warning(this, "Ошибка", "Пароли не совпадают!");
            } else {
                QMessageBox::warning(this, "Error", "Passwords do not match!");
            }
            return;
        }

        if (created_login.size() > 50) {
            if (lang == "RU") {
                QMessageBox::warning(this, "Ошибка", "Длина логина не должна превышать пятидесяти символов");
            } else {
                QMessageBox::warning(this, "Error", "Login must not exceed fifty characters.");
            }
            return;
        }

        if (created_password.size() > 50) {
            if (lang == "RU") {
                QMessageBox::warning(this, "Ошибка", "Длина пароля не должна превышать пятидесяти символов");
            } else {
                QMessageBox::warning(this, "Error", "Password must not exceed fifty characters.");
            }
            return;
        }

        if (!is_strong_and_valid_password(created_password)) {
            return;
        }

        int try_register_user = LRDao::try_register_user(created_login, created_password);
        switch (try_register_user) {
            case 0:
                if (lang == "RU") {
                    QMessageBox::warning(this, "Ошибка", "Извините, внутренняя ошибка с базами данных.");
                } else {
                    QMessageBox::warning(this, "Error", "Sorry, an internal database error occurred.");
                }
                break;
            case -1:
                if (lang == "RU") {
                    QMessageBox::warning(this, "Ошибка", "Пользователь с таким именем уже существует. Пожалуйста, придумайте другое!");
                } else {
                    QMessageBox::warning(this, "Error", "A user with this name already exists. Please choose a different one!");
                }
                break;
            default:
                if (lang == "RU") {
                    QMessageBox::information(this, "Регистрация", "Вы успешно зарегистрировались! Пожалуйста, выполните вход.");
                } else {
                    QMessageBox::information(this, "Registration", "You have successfully registered! Please log in.");
                }
                on_switch_mode_clicked();
                break;
        }
    }
}
