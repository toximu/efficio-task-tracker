#include "profile_window.h"
#include "analytics_window.h"
#include "database_manager.hpp"
#include "language_manager.h"
#include "profile_window_style_sheet.h"
#include "settings_window.h"

namespace Ui {

const std::vector<QString> ProfileWindow::THEMES = {
    profile_window_light_autumn_theme, profile_window_dark_autumn_theme,
    profile_window_dark_purple_theme, profile_window_light_purple_theme,
    profile_window_blue_theme
};

ProfileWindow::ProfileWindow(
    ClientImplementation *client,
    User *user,
    QWidget *parent, 
    int actual_notes_amount,
    int overdue_notes_amount,
    int completed_notes_amount
)
    : client_(client), 
    user_(user), 
    QDialog(parent), 
    actual_notes_amount_(actual_notes_amount),
    overdue_notes_amount_(overdue_notes_amount),
    completed_notes_amount_(completed_notes_amount)
    {
    main_layout = new QVBoxLayout(this);

    logout_button = new QPushButton(tr("Выйти из аккаунта"), this);
    logout_button->setObjectName("logout_button");
    main_layout->addWidget(logout_button);

    delete_button = new QPushButton(tr("Удалить аккаунт"), this);
    delete_button->setObjectName("delete_button");
    main_layout->addWidget(delete_button);

    QHBoxLayout *bottom_layout = new QHBoxLayout();

    stats_button = new QPushButton(tr("Моя статистика"), this);
    stats_button->setObjectName("stats_button");
    bottom_layout->addWidget(stats_button);

    settings_button = new QPushButton("⚙", this);
    settings_button->setObjectName("settings_button");
    settings_button->setFixedSize(45, 45);
    bottom_layout->addWidget(settings_button);

    setWindowTitle(tr("Профиль"));

    main_layout->addLayout(bottom_layout);
    setFixedSize(250, 160);

    connect(
        logout_button, &QPushButton::clicked, this,
        &Ui::ProfileWindow::on_logout_clicked
    );
    connect(
        delete_button, &QPushButton::clicked, this,
        &Ui::ProfileWindow::on_delete_account_clicked
    );
    connect(
        stats_button, &QPushButton::clicked, this,
        &Ui::ProfileWindow::on_stats_clicked
    );
    connect(
        settings_button, &QPushButton::clicked, this,
        &Ui::ProfileWindow::on_settings_clicked
    );
    connect(
        StyleManager::instance(), &StyleManager::theme_changed, this,
        &Ui::ProfileWindow::handle_theme_changed
    );
    handle_theme_changed(StyleManager::instance()->current_theme());
    connect(
        StyleManager::instance(), &StyleManager::font_size_changed, this,
        &Ui::ProfileWindow::handle_font_size_changed
    );
    handle_font_size_changed(StyleManager::instance()->current_font_size());
}

void ProfileWindow::handle_font_size_changed(std::string font_size) {
    QString font_rule;
    if (font_size == "small") {
        font_rule = "QPushButton { font-size: 11px; }";
    } else if (font_size == "medium") {
        font_rule = "QPushButton { font-size: 13px; }";
    } else if (font_size == "big") {
        font_rule = "QPushButton { font-size: 15px; }";
    }

    this->setStyleSheet(
        THEMES[StyleManager::instance()->current_theme()] + font_rule
    );
    connect(
        LanguageManager::instance(), &LanguageManager::language_changed, this,
        &ProfileWindow::handle_language_changed
    );
    handle_language_changed(LanguageManager::instance()->current_language());
}

void ProfileWindow::handle_language_changed(std::string new_language) {
    if (new_language == "RU") {
        setWindowTitle(tr("Профиль"));
        logout_button->setText(tr("Выйти из аккаунта"));
        delete_button->setText(tr("Удалить аккаунт"));
        stats_button->setText(tr("Моя статистика"));
    } else if (new_language == "EN") {
        setWindowTitle(tr("Profile"));
        logout_button->setText(tr("Log out"));
        delete_button->setText(tr("Delete account"));
        stats_button->setText(tr("My statistics"));
    }
}

void ProfileWindow::handle_theme_changed(int theme) {
    setStyleSheet(THEMES[theme]);
}

void ProfileWindow::on_logout_clicked() {
    emit logout_requested();
    this->deleteLater();
}

void ProfileWindow::on_delete_account_clicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, tr("Удаление аккаунта"),
        tr(
            "Вы уверены, что хотите удалить аккаунт? Все данные будут потеряны!"
        ),
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes && client_->try_delete_user(user_)) {
        QMessageBox::information(
            this, tr("Успех"), tr("Аккаунт успешно удалён")
        );
        emit delete_account_requested();
        this->deleteLater();
    } else if (reply == QMessageBox::Yes) {
        QMessageBox::critical(
            this, tr("Ошибка"), tr("Не удалось удалить аккаунт")
        );
    }
}

void ProfileWindow::on_stats_clicked() {
    AnalyticsWindow *new_analytics_window =
        new AnalyticsWindow(
            this->parentWidget(),  
            this->actual_notes_amount,
            this->completed_notes_amount, 
            this->overdue_notes_amount
        );
    this->switch_window(new_analytics_window);
}

void ProfileWindow::on_settings_clicked() {
    auto new_settings_window = new SettingsWindow(this->parentWidget());
    this->switch_window(new_settings_window);
}

void ProfileWindow::switch_window(QWidget *new_window) {
    this->setEnabled(false);
    new_window->setAttribute(Qt::WA_DeleteOnClose);
    connect(new_window, &AnalyticsWindow::destroyed, this, [this]() {
        this->setEnabled(true);
    });
    new_window->show();
    new_window->raise();
    new_window->activateWindow();
}

}  // namespace Ui