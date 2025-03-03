#include "projectlist.h"
#include <QListWidget>
#include"notelist.h"
#include"mainwindow.h"
#include<QDebug>

namespace Ui {

ProjectList::ProjectList(QWidget *parent) : QListWidget{parent} {
  this->setObjectName("ProjectList");
  this->setFixedWidth(200);
  MainWindow* main_window = dynamic_cast<MainWindow *>(parent);


}
}
