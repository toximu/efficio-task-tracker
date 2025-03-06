#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include "note.hpp"
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

namespace Ui {
class NoteWidget : public QWidget {
  Q_OBJECT
  const project_storage_model::Note *model_note_;
  QVBoxLayout *main_layout_;
  QPushButton *open_button_;

public:
  explicit NoteWidget(QWidget *parent = nullptr,
                      const project_storage_model::Note *model_note = nullptr);

private slots:
  void open_note_window() const {
    std::cout << this->model_note_->get_text() << std::endl;
  }
};
} // namespace Ui
#endif // NOTEWIDGET_H
