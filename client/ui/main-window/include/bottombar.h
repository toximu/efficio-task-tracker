#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <string>

namespace Ui {
class BottomBar : public QWidget {
    Q_OBJECT

public:
    BottomBar(
        QWidget *parent,
        const std::string &username,
        QString project_name
    );

signals:
    void profile_button_clicked();

private:
    QHBoxLayout *main_layout_;
    QLabel *project_name_;
    QLabel *username_;
    QPushButton *profile_button_;
};
}  // namespace Ui

#endif  // BOTTOMBAR_H