#include "notelist.h"
#include <QHBoxLayout>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>
#include<vector>
#include"note.hpp"
#include "notewidget.h"

NoteList::NoteList(QWidget *parent)
    : QWidget(parent), main_layout_(new QHBoxLayout(this)),
    vertical_layouts_(std::vector<QVBoxLayout *>())
{
    main_layout_->addStretch();
    this->setObjectName("NoteList");
    this->setLayout(main_layout_);
    vertical_layouts_.resize(4, nullptr);
    for (auto &layout : vertical_layouts_){
        layout = new QVBoxLayout(this);
        // layout->addStretch();
        main_layout_->addLayout(layout,2);
    }



}

void NoteList::add_note_widget(const project_storage_model::Note* note){
    vertical_layouts_[note_counter%4]->addWidget(new NoteWidget(this, note), Qt::AlignTop);
    note_counter++;

}
