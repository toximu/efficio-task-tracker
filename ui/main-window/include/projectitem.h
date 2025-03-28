#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <QListWidget>
#include <QObject>
#include "notelist.h"
#include "project.hpp"

namespace Ui {
class ProjectItem : public QListWidgetItem {
    project_storage_model::Project *project_;
    friend NoteList;
    friend class MainWindow;

public:
    ProjectItem(QListWidget *listview, project_storage_model::Project *project);
};
}  // namespace Ui
#endif  // PROJECTITEM_H
