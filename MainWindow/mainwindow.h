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
#include <QPushButton>
#include <QWidget>
#include <string>

namespace Ui {
class MainWindow : public QWidget {
  Q_OBJECT
  QVBoxLayout *main_layout_;
  BottomBar *bottom_bar_;
  QHBoxLayout *content_layout_;
  ProjectList *project_list_;
  NoteList *note_list_;
  QWidget *content_widget_;
  QPushButton *new_project_button_;
  void create_note_list_(QListWidgetItem *project);

  friend ProjectList;

public:
  explicit MainWindow(QWidget *parent = nullptr, std::string username = "none");
  void add_project(project_storage_model::Project *project);
};
} // namespace Ui
#endif // MAINWINDOW_H
