#include "projectlist.h"
#include <QListWidget>
#include "mainwindow.h"
#include "project.hpp"
#include "projectitem.h"

namespace Ui {

ProjectList::ProjectList(QWidget *parent) : QListWidget{parent} {
    this->setObjectName("ProjectList");
    this->setFixedWidth(200);
}

void ProjectList::add_project(project_storage_model::Project *project) {
    this->addItem(new ProjectItem(static_cast<QListWidget *>(this), project));
}

void ProjectList::load_projects(project_storage_model::Storage* storage) {
    for (project_storage_model::Project &pr : storage->get_projects()) {
        add_project(&pr);
    }
}

}  // namespace Ui
