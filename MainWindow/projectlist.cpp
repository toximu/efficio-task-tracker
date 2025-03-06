#include "projectlist.h"
#include "mainwindow.h"
#include "notelist.h"
#include <QDebug>
#include <QListWidget>

namespace Ui {

ProjectList::ProjectList(QWidget *parent) : QListWidget{parent} {
  this->setObjectName("ProjectList");
  this->setFixedWidth(200);
  MainWindow *main_window = dynamic_cast<MainWindow *>(parent);
}
} // namespace Ui
