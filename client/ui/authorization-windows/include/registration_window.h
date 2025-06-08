#pragma once

#include <QWidget>
#include <vector>
#include "client_implementation.h"

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QWidget {
    Q_OBJECT

public:
    explicit RegistrationWindow(
        ClientImplementation *client,
        QWidget *parent = nullptr
    );
    ~RegistrationWindow() override;

    bool is_strong_and_valid_password(const QString &password);
    void handle_language_changed(std::string new_language);

private slots:
    void on_switch_mode_clicked();
    void on_push_registration_clicked();
    void on_switch_language_clicked();

private:
    int counter_on_switch_theme_clicks = 0;
    ClientImplementation *client_;
    std::shared_ptr<Ui::RegistrationWindow> ui;
};