#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
#include "client_implementation.h"
#include "model-proto/model.pb.h"
#include "projectitem.h"

using Efficio_proto::Note;

namespace Ui {
class NoteWidget final : public QWidget {
    Q_OBJECT
    Note *model_note_;
    QVBoxLayout *main_layout_;
    QPushButton *open_button_;
    QPushButton *delete_button_;
    QPushButton *complete_button_;
    QLabel *title_label_;
    QHBoxLayout *tags_layout_;
    std::vector<QLabel *> tag_labels_;
    ClientImplementation *client_;

    void update_tags();

public:
    explicit NoteWidget(
        ClientImplementation *client,
        QWidget *parent,
        Note *model_note,
        const Note::Type &type,
        QListWidgetItem *p
    );
    Note::Type type_;
    QListWidgetItem *project_;
    void handle_font_size_changed(const std::string &font_size_);
    void handle_language_changed(const std::string &new_language);
    QListWidgetItem *get_project() const;

private slots:
    void good_resize();
    void open_note_window();
    void delete_note();
    void complete_note();
    void change_type(Note::Type::States new_type);
signals:
    void change_type_requested(
        QListWidgetItem *project,
        Note::Type::States old_type,
        Note::Type::States type_
    );
};
}  // namespace Ui
#endif  // NOTEWIDGET_H