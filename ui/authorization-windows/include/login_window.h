#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "database_manager.hpp"
#include "lr_dao.hpp"

QT_BEGIN_NAMESPACE

namespace Ui {
class LoginWindow;
}

QT_END_NAMESPACE

class LoginWindow : public QDialog {
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_switch_mode_clicked();
    void on_push_enter_clicked();

private:
    Ui::LoginWindow *ui;
};
