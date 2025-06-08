#pragma once

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include "style_manager.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {

class ProfileWindow : public QDialog {
    Q_OBJECT

    QVBoxLayout* main_layout;
    QPushButton* logout_button;
    QPushButton* delete_button;
    QPushButton* stats_button;
    QPushButton* settings_button;
    QString current_username;

    void setup_ui(QDialog* profile_window);
    void switch_window(QWidget *new_window);

public:
    explicit ProfileWindow(const QString& username, QWidget* parent = nullptr);
    ~ProfileWindow() = default;

    static const std::vector<QString> THEMES;
    void handle_theme_changed(int theme);
    void handle_font_size_changed(std::string font_size);
    void handle_language_changed(std::string new_language);
    friend class MainWindow;

signals:
    void logout_requested();
    void delete_account_requested();

private slots:
    void on_logout_clicked();
    void on_delete_account_clicked();
    void on_stats_clicked();
    void on_settings_clicked();
};

} // namespace Ui
QT_END_NAMESPACE