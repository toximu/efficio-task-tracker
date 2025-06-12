#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <model-proto/model.pb.h>
#include <QListWidget>
#include "notelist.h"

using namespace Efficio_proto;

namespace Ui {
class ProjectItem : public QListWidgetItem {
    Project *project_;
    friend class NoteList;
    friend class MainWindow;
    friend class NoteWidget;
    friend class ProjectList;
private slots:
    void showContextMenu(const QPoint &pos);
public:
    ProjectItem(QListWidget *listview, Project *project);
};
}  // namespace Ui
#endif  // PROJECTITEM_H