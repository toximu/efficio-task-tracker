#ifndef PROJECTLIST_H
#define PROJECTLIST_H

#include "../../project-storage-model/include/project.hpp"
#include <QListWidget>
#include <QWidget>

namespace Ui {
class ProjectList : public QListWidget {
  Q_OBJECT
  friend class MainWindow;
  void add_project(project_storage_model::Project *project);

public:
  explicit ProjectList(QWidget *parent = nullptr);

signals:
};
} // namespace Ui
#endif // PROJECTLIST_H
