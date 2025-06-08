#include "notelist.h"
#include <QHBoxLayout>
#include <QObject>
#include <QWidget>
#include <utility>
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
    vertical_layouts_.resize(3, nullptr);
    for (auto &layout : vertical_layouts_) {
        layout = new QVBoxLayout(this);

        main_layout_->addLayout(layout);
    }
}

void NoteList::add_note_widget(const Note *note, QListWidgetItem *project) {
    const auto current_layout = vertical_layouts_[note_counter_ % 3];
    if (current_layout->count() > 1) {
        current_layout->removeItem(
            current_layout->itemAt(current_layout->count() - 1)
        );
    }
    auto *new_note = new NoteWidget(client_, this, note, this->type_, project);
    vertical_layouts_[note_counter_ % 3]->addWidget(new_note, 0, Qt::AlignTop);
    connect(
        new_note, &NoteWidget::change_type_requested, this,
        &NoteList::load_project_notes
    );
    current_layout->addStretch();
    note_counter_++;
}

void NoteList::load_project_notes(QListWidgetItem *project) {
    auto *p = dynamic_cast<ProjectItem *>(project);
    this->clear_note_list();
    note_counter_ = 0;
    for (const auto &note : p->project_->notes()) {
        if (note.type().value() == this->type_.value()) {
            this->add_note_widget(&note, project);
        }
    }
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