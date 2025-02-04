#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bottombar.h"
#include "widget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QWidget>
#include<QListWidget>
#include"projectlist.h"
class MainWindow : public Widget {
  Q_OBJECT
  QVBoxLayout *main_layout;
  BottomBar *bottom_bar;
  QHBoxLayout * content_layout;
  ProjectList * project_list;
public:
  explicit MainWindow(Widget *parent = nullptr);

signals:
};

#endif // MAINWINDOW_H
