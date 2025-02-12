#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bottombar.h"
#include "projectitem.h"
#include "projectlist.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QWidget>
#include <string>

class MainWindow : public QWidget {
  Q_OBJECT
  QVBoxLayout *main_layout;
  BottomBar *bottom_bar;
  QHBoxLayout *content_layout;
  ProjectList *project_list;

public:
  explicit MainWindow(QWidget *parent = nullptr, std::string username = "none");
  void add_project(std::string text);
signals:
};

#endif // MAINWINDOW_H
