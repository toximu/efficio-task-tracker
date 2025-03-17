#include "../include/projectlist.h"
#include "../include/mainwindow.h"
#include "../../project-storage-model/include/project.hpp"
#include "../include/projectitem.h"
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
