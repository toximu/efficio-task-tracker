#pragma once

#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>
#include "client_implementation.h"
#include "database_manager.hpp"

QT_BEGIN_NAMESPACE

namespace Ui {
class LoginWindow;
}

QT_END_NAMESPACE

class LoginWindow final : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(
        ClientImplementation *client,
        QWidget *parent = nullptr
    );
    ~LoginWindow() override;

    static const std::vector<QString> THEMES;
    void handle_theme_changed(int theme);

private slots:
    void on_switch_mode_clicked();
    void on_push_enter_clicked();
    void on_switch_theme_clicked();

private:
    Ui::LoginWindow *ui;
    int counter_on_switch_theme_clicks = 0;
    ClientImplementation *client_;
};