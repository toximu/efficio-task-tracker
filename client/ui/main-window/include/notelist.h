#ifndef NOTELIST_H
#define NOTELIST_H

#include <vector>
#include "client_implementation.h"
#include "model-proto/model.pb.h"
#include "notewidget.h"
#include "projectitem.h"

using Efficio_proto::Note;

namespace Ui {
class NoteList final : public QWidget {
    friend class MainWindow;
    Q_OBJECT

    QHBoxLayout *main_layout_;

    std::vector<QVBoxLayout *> vertical_layouts_;
    Note::Type type_;
    ClientImplementation *client_;

public:
    void add_note_widget(const Note *note, QListWidgetItem *p);
    void clear_note_list();
    NoteList(
        ClientImplementation *client,
        QWidget *parent,
        Note::Type::States type
    );
    void NoteList::change_note_type_requested(QListWidgetItem *project);
    
public slots:
    int load_project_notes(QListWidgetItem *project);
signals:
    void change_note_type_requested(QListWidgetItem *project);
};
}  // namespace Ui
#endif  // NOTELIST_H