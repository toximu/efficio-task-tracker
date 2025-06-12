#ifndef PROJECTLIST_H
#define PROJECTLIST_H

#include <model-proto/model.pb.h>
#include <QListWidget>
#include <QWidget>
#include "projectitem.h"

using namespace Efficio_proto;

namespace Ui {
class ProjectList : public QListWidget {
    Q_OBJECT
    friend class MainWindow;
    void add_project(Project *project);
    void load_projects(Storage *storage);
private slots:
    void showContextMenu(const QPoint &pos);
public:
    explicit ProjectList(QWidget *parent = nullptr);
signals:
    void leave_project(ProjectItem *project_item);


signals:
};
}  // namespace Ui
#endif  // PROJECTLIST_H