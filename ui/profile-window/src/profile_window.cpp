#include "profile_window.h"
#include "profile_window_style_sheet.h"
#include <QScreen>
#include "database_manager.hpp"
#include "lr_dao.hpp"
#include "settings_window.h"
#include "analytics_window.h"

namespace Ui {

const std::vector<QString> ProfileWindow::themes = {
    profile_window_light_autumn_theme,
    profile_window_dark_autumn_theme,
    profile_window_dark_purple_theme,
    profile_window_light_purple_theme,
    profile_window_blue_theme
};

ProfileWindow::ProfileWindow(const QString& username, QWidget* parent)
    : QDialog(parent), current_username(username) {
    main_layout = new QVBoxLayout(this);

    logout_button = new QPushButton("Выйти из аккаунта", this);
    logout_button->setObjectName("logout_button");
    main_layout->addWidget(logout_button);

    delete_button = new QPushButton("Удалить аккаунт", this);
    delete_button->setObjectName("delete_button");
    main_layout->addWidget(delete_button);

    QHBoxLayout* bottom_layout = new QHBoxLayout();
    
    stats_button = new QPushButton("Моя статистика", this);
    stats_button->setObjectName("stats_button");
    bottom_layout->addWidget(stats_button);

    settings_button = new QPushButton("⚙", this);
    settings_button->setObjectName("settings_button");
    settings_button->setFixedSize(45, 45);
    bottom_layout->addWidget(settings_button);

    main_layout->addLayout(bottom_layout);
    setFixedSize(250, 160);
    
    connect(
        logout_button, &QPushButton::clicked, 
        this, &Ui::ProfileWindow::on_logout_clicked
    );
    connect(
        delete_button, &QPushButton::clicked, 
        this, &Ui::ProfileWindow::on_delete_account_clicked
    );
    connect(
        stats_button, &QPushButton::clicked, 
        this, &Ui::ProfileWindow::on_stats_clicked
    );
    connect(settings_button, &QPushButton::clicked, 
        this, &Ui::ProfileWindow::on_settings_clicked
    );
    connect(ThemeManager::instance(), &ThemeManager::theme_changed,
            this, &Ui::ProfileWindow::handle_theme_changed
    );
    handle_theme_changed(ThemeManager::instance()->current_theme());
}

void ProfileWindow::handle_theme_changed(int theme) {
    setStyleSheet(themes[theme]);
}

void ProfileWindow::on_logout_clicked() {
    emit logout_requested();
    this->deleteLater();
}

void ProfileWindow::on_delete_account_clicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, 
        "Удаление аккаунта",
        "Вы уверены, что хотите удалить аккаунт? Все данные будут потеряны!",
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes && LRDao::try_delete_user(current_username)) {
        QMessageBox::information(this, "Успех", "Аккаунт успешно удалён");
        emit delete_account_requested();
        this->deleteLater();
    } else if (reply == QMessageBox::Yes) {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить аккаунт");
    }
}

void ProfileWindow::on_stats_clicked() {
    this->setEnabled(false);
    AnalyticsWindow *new_analytics_window = new AnalyticsWindow(this->parentWidget());
    new_analytics_window->setAttribute(Qt::WA_DeleteOnClose);
    connect(new_analytics_window, &AnalyticsWindow::destroyed, 
        this, [this]() { this->setEnabled(true); });   
    new_analytics_window->show();
    new_analytics_window->raise();  
    new_analytics_window->activateWindow();
}

void ProfileWindow::on_settings_clicked() {
    this->setEnabled(false);
    SettingsWindow *new_settings_window = new SettingsWindow(this->parentWidget());
    new_settings_window->setAttribute(Qt::WA_DeleteOnClose);
    connect(new_settings_window, &SettingsWindow::destroyed, 
        this, [this]() { this->setEnabled(true); });   
    new_settings_window->show();
    new_settings_window->raise();  
    new_settings_window->activateWindow();
}

} // namespace Ui