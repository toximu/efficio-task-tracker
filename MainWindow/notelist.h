#ifndef NOTELIST_H
#define NOTELIST_H

#include <QHBoxLayout>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

class NoteList : QWidget {
  Q_OBJECT
  QHBoxLayout *main_layout_;
  QVBoxLayout *vertical_layout1_;
  QVBoxLayout *vertical_layout2_;
  QVBoxLayout *vertical_layout3_;
  QVBoxLayout *vertical_layout4_;
  int note_counter = 0;
public:
  void add_note_widget();
  NoteList(QWidget * parent);
};

#endif // NOTELIST_H
