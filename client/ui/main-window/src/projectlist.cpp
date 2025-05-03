#include "projectlist.h"
#include <QListWidget>
#include "mainwindow.h"
#include "projectitem.h"

namespace Ui {

ProjectList::ProjectList(QWidget *parent) : QListWidget{parent} {
    this->setObjectName("ProjectList");
    this->setFixedWidth(200);
}

void ProjectList::add_project(Project *project) {
    this->addItem(new ProjectItem(static_cast<QListWidget *>(this), project));
}

void ProjectList::load_projects(Storage *storage) {
    for (Project &project : *storage->mutable_projects()) {
        add_project(&project);
    }
}

}  // namespace Ui