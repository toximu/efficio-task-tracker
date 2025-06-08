#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <QListWidget>
#include <QObject>
#include "notelist.h"
#include "project.hpp"

namespace Ui {

class NoteWidget;

class ProjectItem : public QListWidgetItem {
    project_storage_model::Project *project_;
    friend class NoteList;
    friend class MainWindow;
    friend class NoteWidget;

public:
    ProjectItem(QListWidget *listview, project_storage_model::Project *project);
};
}  // namespace Ui
#endif  // PROJECTITEM_H