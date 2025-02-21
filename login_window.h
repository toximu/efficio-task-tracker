#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

QT_BEGIN_NAMESPACE

namespace Ui {
class LoginWindow;
}

QT_END_NAMESPACE


class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_switchMode_clicked();

    void on_pushEnter_clicked();

private:
    Ui::LoginWindow *ui;
};
#endif // LOGIN_WINDOW_H

