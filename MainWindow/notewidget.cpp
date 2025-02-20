#include "notewidget.h"
#include "note.hpp"
#include<QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
NoteWidget::NoteWidget(QWidget *parent,const project_storage_model::Note *model_note)
    : QWidget(parent), model_note_(model_note), main_layout_(new QVBoxLayout(this))
{
    this->setObjectName("NoteWidget");
    this->setFixedSize(100,70);
    QLabel * title = new QLabel(model_note_->get_title().c_str(), this);
    QLabel * text = new QLabel(model_note_->get_text().c_str(),this);
    main_layout_->addWidget(title);
    main_layout_->addWidget(text);
    this->setLayout(main_layout_);



}
