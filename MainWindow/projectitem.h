#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include "notelist.h"
#include "project.hpp"
#include <QListWidget>
#include <QListWidgetItem>
#include <QObject>
#include <QWidget>

namespace Ui {
class ProjectItem : public QListWidgetItem {
  project_storage_model::Project *project_;
  friend NoteList;

public:
  ProjectItem(project_storage_model::Project *project, QListWidget *listview);
};
} // namespace Ui
#endif // PROJECTITEM_H
