#include "notewidget.h"
#include "note.hpp"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace Ui {
NoteWidget::NoteWidget(QWidget *parent,
                       const project_storage_model::Note *model_note)
    : QWidget(parent), model_note_(model_note),
      main_layout_(new QVBoxLayout(this)),
      open_button_(new QPushButton("Открыть")) {
  this->setObjectName("NoteWidget");
  this->setMinimumWidth(100);
  this->setMinimumHeight(80);
  QLabel *title = new QLabel(model_note_->get_title().c_str(), this);
  QLabel *text = new QLabel(model_note_->get_text().c_str(), this);
  main_layout_->addWidget(title);
  main_layout_->addWidget(text);
  main_layout_->addWidget(open_button_);

  connect(open_button_, &QPushButton::clicked, this,
          &NoteWidget::open_note_window);
  this->setLayout(main_layout_);
  this->setAttribute(Qt::WA_StyledBackground);
}
} // namespace Ui
