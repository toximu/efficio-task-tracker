#pragma once

#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "database_manager.hpp"
#include "lr_dao.hpp"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    
    static const std::vector<QString> THEMES;
    void handle_theme_changed(int theme);

private slots:
    void on_switch_mode_clicked();
    void on_push_enter_clicked();
    void on_switch_theme_clicked();

private:
    Ui::LoginWindow *ui; 
    int counter_on_switch_theme_clicks = 0;
};