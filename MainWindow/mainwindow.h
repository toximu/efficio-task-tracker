#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bottombar.h"
#include "notelist.h"
#include "project.hpp"
#include "projectitem.h"
#include "projectlist.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QWidget>
#include <string>

namespace Ui{
class MainWindow : public QWidget {
  Q_OBJECT
  QVBoxLayout *main_layout_;
  BottomBar *bottom_bar_;
  QHBoxLayout *content_layout_;
  ProjectList *project_list_;
  NoteList *note_list_;
  friend ProjectList;
public:
  explicit MainWindow(QWidget *parent = nullptr, std::string username = "none");
  void add_project(project_storage_model::Project *project);

};
}
#endif // MAINWINDOW_H
