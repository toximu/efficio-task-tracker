#include "notelist.h"
#include <QHBoxLayout>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>
#include<vector>
#include"projectitem.h"
#include"note.hpp"
#include "notewidget.h"

namespace Ui {
NoteList::NoteList(QWidget *parent)
    : QWidget(parent), main_layout_(new QHBoxLayout(this)),
    vertical_layouts_(std::vector<QVBoxLayout *>())
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("NoteList");
    this->setLayout(main_layout_);
    vertical_layouts_.resize(4, nullptr);
    for (auto &layout : vertical_layouts_){
        layout = new QVBoxLayout(this);

        main_layout_->addLayout(layout);
    }

}

void NoteList::add_note_widget(const project_storage_model::Note* note){
    vertical_layouts_[note_counter%4]->addWidget(new NoteWidget(this, note),0,Qt::AlignTop);
    note_counter++;
}

void NoteList::load_project_notes(QListWidgetItem * project){
    ProjectItem * p = dynamic_cast<ProjectItem *>(project);
    for (const auto & note : p->project_->get_notes()){
        this->add_note_widget(&note);
    }
}
}
