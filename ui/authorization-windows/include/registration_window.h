#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "database_manager.hpp"
#include "lr_dao.hpp"
#include <vector>

QT_BEGIN_NAMESPACE

namespace Ui {
class RegistrationWindow;
}

QT_END_NAMESPACE

class RegistrationWindow : public QWidget {
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();
    bool is_strong_and_valid_password(const QString &password);
    static const std::vector<QString> THEMES;
    void handle_theme_changed(int theme);

private slots:
    void on_switch_mode_clicked();
    void on_push_registration_clicked();
    void on_switch_theme_clicked();

private:
    Ui::RegistrationWindow *ui;
    int counter_on_switch_theme_clicks = 0;
};