#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QWidget>
#include <string>
class BottomBar : public QWidget {
  QHBoxLayout *main_layout;
  QLabel *project_name;
  QLabel *username;

public:
  BottomBar(QWidget *parent_, std::string username_, std::string project_name_);
};

#endif // BOTTOMBAR_H
