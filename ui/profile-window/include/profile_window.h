#pragma once

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include "theme_manager.h"
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

    static const std::vector<QString> themes;
    void handle_theme_changed(int theme);
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