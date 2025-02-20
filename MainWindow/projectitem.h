#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include "project.hpp"
#include <QListWidget>
#include <QListWidgetItem>
#include <QObject>
#include <QWidget>
#include <string>

class ProjectItem : public QListWidgetItem {
  project_storage_model::Project *project_;

public:
  ProjectItem(project_storage_model::Project *project, QListWidget *listview);
};

#endif // PROJECTITEM_H
