#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include "widget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <string>
#include<QPalette>
class BottomBar : public Widget {
  QHBoxLayout *main_layout;
    QLabel *project_name;
  QLabel *username;
  QPalette *palette;

public:
  BottomBar(Widget *parent_, std::string username_, std::string project_name_);
};

#endif // BOTTOMBAR_H
