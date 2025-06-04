#include "notelist.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QObject>
#include <QWidget>
#include <vector>
#include "notewidget.h"
#include "projectitem.h"

namespace Ui {
NoteList::NoteList(QWidget *parent, ClientImplementation *client)
    : QWidget(parent),
      client_(client),
      main_layout_(new QHBoxLayout(this)),
      vertical_layouts_(std::vector<QVBoxLayout *>()) {
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("NoteList");
    this->setLayout(main_layout_);
    vertical_layouts_.resize(4, nullptr);
    for (auto &layout : vertical_layouts_) {
        layout = new QVBoxLayout(this);

        main_layout_->addLayout(layout);
    }
}

void NoteList::add_note_widget(Note *note) {
    auto current_layout = vertical_layouts_[note_counter_ % 4];
    if (current_layout->count() > 1) {
        current_layout->removeItem(
            current_layout->itemAt(current_layout->count() - 1)
        );
    }
    vertical_layouts_[note_counter_ % 4]->addWidget(
        new NoteWidget(this, note, client_), 0, Qt::AlignTop
    );
    current_layout->addStretch();
    note_counter_++;
}

void NoteList::load_project_notes(QListWidgetItem *project) {
    ProjectItem *p = dynamic_cast<ProjectItem *>(project);
    assert(p != nullptr);
    this->clear_note_list();
    client_->get_project(p->project_, p->project_->code());
    note_counter_ = 0;
    for (Note &note : *p->project_->mutable_notes()) {
        this->add_note_widget(&note);
    }
}

void NoteList::clear_note_list() {
    for (auto &layout : vertical_layouts_) {
        while (layout->count()) {
            auto item = layout->takeAt(0);
            auto widget = item->widget();
            if (widget) {
                widget->deleteLater();
            }
        }
    }
}
}  // namespace Ui