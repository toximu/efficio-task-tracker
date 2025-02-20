#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include "note.hpp"
#include<QVBoxLayout>
#include<QHBoxLayout>

class NoteWidget : public QWidget {
  Q_OBJECT
  const  project_storage_model::Note * model_note_;
  QVBoxLayout * main_layout_;
public:
  explicit NoteWidget(QWidget *parent = nullptr,const project_storage_model::Note * model_note = nullptr);

signals:
};

#endif // NOTEWIDGET_H
