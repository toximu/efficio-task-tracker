#include "notelist.h"
#include <QHBoxLayout>
#include <QObject>
#include <QWidget>
#include <vector>
#include "client_implementation.h"
#include "model-proto/model.pb.h"

using Efficio_proto::Note;

namespace Ui {
NoteList::NoteList(
    ClientImplementation *client,
    QWidget *parent,
    const Note::Type::States type
)
    : QWidget(parent),
      main_layout_(new QHBoxLayout(this)),
      vertical_layouts_(std::vector<QVBoxLayout *>()),
      client_(client) {
    type_.set_value(type);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("NoteList");
    this->setLayout(main_layout_);
    vertical_layouts_.resize(2, nullptr);
    for (auto &layout : vertical_layouts_) {
        layout = new QVBoxLayout(this);

        main_layout_->addLayout(layout);
    }
}

void NoteList::add_note_widget(Note *note, QListWidgetItem *p) {
    const auto current_layout = vertical_layouts_[note_counter_ % 2];
    if (current_layout->count() > 1) {
        current_layout->removeItem(
            current_layout->itemAt(current_layout->count() - 1)
        );
    }
    auto *new_note = new NoteWidget(client_, this, note, this->type_, p);
    vertical_layouts_[note_counter_ % 2]->addWidget(new_note, 0, Qt::AlignTop);
    current_layout->addStretch();
    connect(
        new_note, &NoteWidget::change_type_requested, this,
        &NoteList::change_note_type_request
    );
    note_counter_++;
}

void NoteList::change_note_type_request(
    QListWidgetItem *project,
    Note::Type::States old_type,
    Note::Type::States new_type
) {
    emit change_note_type_requested(project, old_type, new_type);
}

int NoteList::load_project_notes(QListWidgetItem *project) {
    auto *p = dynamic_cast<ProjectItem *>(project);

    this->clear_note_list();
    note_counter_ = 0;
    auto &notes = *p->project_->mutable_notes();
    int notes_size = notes.size();

    for (int i = 0; i < notes_size; ++i) {
        auto &note = notes[i];
        if (note.type().value() == this->type_.value()) {
            this->add_note_widget(&note, project);
        }
    }

    return note_counter_;
}

void NoteList::clear_note_list() {
    for (const auto &layout : vertical_layouts_) {
        while (layout->count()) {
            const auto item = layout->takeAt(0);
            const auto widget = item->widget();
            if (widget) {
                widget->deleteLater();
            }
        }
    }
}
}  // namespace Ui