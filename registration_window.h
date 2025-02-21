#ifndef REGISTRATION_WINDOW_H
#define REGISTRATION_WINDOW_H

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>


QT_BEGIN_NAMESPACE

namespace Ui {
class RegistrationWindow;
}

QT_END_NAMESPACE

class RegistrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:
    void on_switchMode_clicked();

    void on_pushRegistration_clicked();

private:
    Ui::RegistrationWindow *ui;
};

#endif // REGISTRATION_WINDOW_H
