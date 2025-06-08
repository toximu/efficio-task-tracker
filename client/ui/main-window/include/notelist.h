#ifndef NOTELIST_H
#define NOTELIST_H
#include <model-proto/model.pb.h>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>
#include "client_implementation.h"

using namespace Efficio_proto;

namespace Ui {
class NoteList : public QWidget {
    friend class MainWindow;
    Q_OBJECT

    QHBoxLayout *main_layout_;

    std::vector<QVBoxLayout *> vertical_layouts_;

    ClientImplementation *client_;

    int note_counter_ = 0;

    const std::size_t notes_per_row = 3;

public:
    void add_note_widget(Note *note);
    void clear_note_list();
    NoteList(QWidget *parent, ClientImplementation *client);

public slots:
    void load_project_notes(QListWidgetItem *project);
};
}  // namespace Ui
#endif  // NOTELIST_H