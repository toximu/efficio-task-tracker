#pragma once

#include <QWidget>
#include <vector>
#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
    namespace Ui {
        class LoginWindow;
    }
QT_END_NAMESPACE

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow() override;

    static const std::vector<QString> THEMES;
    void handle_theme_changed(int theme);

private slots:
    void on_switch_mode_clicked();
    void on_push_enter_clicked();
    void on_switch_theme_clicked();

private:
    std::shared_ptr<Ui::LoginWindow> ui;
    int counter_on_switch_theme_clicks = 0;
    void switch_window(QMainWindow *app_window, QWidget *new_window, int width, int height);
    void switch_to_login_window(QMainWindow *app_window);
    void switch_to_registration_window(QMainWindow *app_window);
};