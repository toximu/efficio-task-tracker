#include "projectlist.h"
#include <QAction>
#include <QContextMenuEvent>
#include <QListWidget>
#include <QMenu>
#include "mainwindow.h"
#include "projectitem.h"

namespace Ui {

ProjectList::ProjectList(QWidget *parent) : QListWidget{parent} {
    this->setObjectName("ProjectList");
    this->setFixedWidth(300);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(
        this, &QListWidget::customContextMenuRequested, this,
        &ProjectList::showContextMenu
    );
}

void ProjectList::add_project(Project *project) {
    this->addItem(new ProjectItem(static_cast<QListWidget *>(this), project));
}

void ProjectList::load_projects(Storage *storage) {
    for (Project &project : *storage->mutable_projects()) {
        add_project(&project);
    }
}

void ProjectList::showContextMenu(const QPoint &pos) {
    QListWidgetItem *item = this->itemAt(pos);
    if (!item) {
        return;
    }
    ProjectItem *project_item = dynamic_cast<ProjectItem *>(item);
    if (!project_item) {
        return;
    }
    QMenu menu;

    std::string code_string = "Код проекта: " + project_item->project_->code();
    QAction *code = menu.addSection(code_string.c_str());
    code->setCheckable(false);
    QAction *leave = menu.addAction("Покинуть");

    if (leave == menu.exec(QCursor::pos())) {
        emit leave_project(project_item);
    }
}

}  // namespace Ui