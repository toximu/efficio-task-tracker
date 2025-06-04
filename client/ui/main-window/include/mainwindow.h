#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <model-proto/model.pb.h>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <string>
#include "bottombar.h"
#include "client_implementation.h"
#include "notelist.h"
#include "projectlist.h"

using namespace Efficio_proto;

namespace Ui {
class MainWindow : public QWidget {
    Q_OBJECT
    ClientImplementation *client_;
    std::unique_ptr<User> user_;
    QVBoxLayout *main_layout_;
    BottomBar *top_bar_;
    QHBoxLayout *content_layout_;
    ProjectList *project_list_;
    NoteList *note_list_;
    QWidget *content_widget_;
    QPushButton *new_project_button_;
    QPushButton *new_note_button_;



    friend ProjectList;
private slots:
    void create_project();
    void add_note();

public:
    explicit MainWindow(
        QWidget *parent,
        std::unique_ptr<User> user,
        ClientImplementation *client
    );
};
}  // namespace Ui
#endif  // MAINWINDOW_H