#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <model-proto/model.pb.h>
#include <QListWidget>
#include <QObject>
#include "notelist.h"

using namespace Efficio_proto;

namespace Ui {
class ProjectItem : public QListWidgetItem {
    Project *project_;
    friend NoteList;
    friend class MainWindow;

public:
    ProjectItem(QListWidget *listview, Project *project);
};
}  // namespace Ui
#endif  // PROJECTITEM_H