#include "projectlist.h"
#include "mainwindow.h"
#include <QListWidget>

namespace Ui {

ProjectList::ProjectList(QWidget *parent) : QListWidget{parent} {
  this->setObjectName("ProjectList");
  this->setFixedWidth(200);
}

void ProjectList::add_project(project_storage_model::Project *project) {
  this->addItem(new ProjectItem(static_cast<QListWidget *>(this), project));
}

} // namespace Ui
