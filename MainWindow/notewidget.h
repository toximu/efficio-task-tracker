#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include "note.hpp"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<iostream>
class NoteWidget : public QWidget {
  Q_OBJECT
  const  project_storage_model::Note * model_note_;
  QVBoxLayout * main_layout_;
  QPushButton * open_button_;
public:
  explicit NoteWidget(QWidget *parent = nullptr,const project_storage_model::Note * model_note = nullptr);


private slots:
  void open_note_window() const {
        std::cout << this->model_note_->get_text() << std::endl;
    }
};

#endif // NOTEWIDGET_H
