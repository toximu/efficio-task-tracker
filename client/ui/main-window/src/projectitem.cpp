#include "projectitem.h"
#include <QListWidget>

namespace Ui {
ProjectItem::ProjectItem(QListWidget *list_view, Project *project)
    : project_(project), QListWidgetItem(project->title().c_str(), list_view) {
}

}  // namespace Ui