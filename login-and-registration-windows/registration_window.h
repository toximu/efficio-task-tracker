#pragma once

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "database_manager.hpp"
#include "lr_dao.hpp"

QT_BEGIN_NAMESPACE

namespace Ui {
class RegistrationWindow;
}

QT_END_NAMESPACE

class RegistrationWindow : public QDialog {
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();
    bool is_strong_and_valid_password(const QString &password);

private slots:
    void on_switch_mode_clicked();
    void on_push_registration_clicked();

private:
    Ui::RegistrationWindow *ui;
};
