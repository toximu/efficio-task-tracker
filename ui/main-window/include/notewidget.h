#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
#include "note.hpp"

namespace Ui {
class NoteWidget : public QWidget {
    Q_OBJECT
    const project_storage_model::Note *model_note_;
    QVBoxLayout *main_layout_;
    QPushButton *open_button_;
    QLabel *title_label_;
    QLabel *text_label_;

public:
    explicit NoteWidget(
        QWidget *parent = nullptr,
        const project_storage_model::Note *model_note = nullptr
    );

private slots:

    void open_note_window() const;
};
}  // namespace Ui
#endif  // NOTEWIDGET_H