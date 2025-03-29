#ifndef PROJECTLIST_H
#define PROJECTLIST_H

#include <QListWidget>
#include <QWidget>
#include "project.hpp"
#include "storage.hpp"

namespace Ui {
class ProjectList : public QListWidget {
    Q_OBJECT
    friend class MainWindow;
    void add_project(project_storage_model::Project *project);
    void load_projects(project_storage_model::Storage*storage);
public:
    explicit ProjectList(QWidget *parent = nullptr);

signals:
};
}  // namespace Ui
#endif  // PROJECTLIST_H
