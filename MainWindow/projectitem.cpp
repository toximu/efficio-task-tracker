#include "projectitem.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QWidget>
#include <string>

namespace Ui {
ProjectItem::ProjectItem(QListWidget *list_view,
                         project_storage_model::Project *project)
    : project_(project),
      QListWidgetItem(project->get_name().c_str(), list_view) {}
} // namespace Ui
