#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <string>

namespace Ui {
class BottomBar : public QWidget {
    QHBoxLayout *main_layout_;
    QLabel *project_name_;
    QLabel *username_;

public:
    BottomBar(
        QWidget *parent_,
        std::string username_,
        std::string project_name_
    );
};
}  // namespace Ui

#endif  // BOTTOMBAR_H