#ifndef NOTELIST_H
#define NOTELIST_H

#include "note.hpp"
#include <QHBoxLayout>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>
#include<vector>
class NoteList : public QWidget {

  Q_OBJECT

  QHBoxLayout *main_layout_;
  std::vector<QVBoxLayout *> vertical_layouts_;
  int note_counter = 0;

public:
  void add_note_widget(const project_storage_model::Note *note);
  NoteList(QWidget *parent);
};

#endif // NOTELIST_H
