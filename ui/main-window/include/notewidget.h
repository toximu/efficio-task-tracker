#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
#include "note.hpp"
#include "projectitem.h"

namespace Ui {
class NoteWidget : public QWidget {
    Q_OBJECT
    const project_storage_model::Note *model_note_;
    QVBoxLayout *main_layout_;
    QPushButton *open_button_;
    QPushButton *delete_button_;
    QLabel *title_label_;
    QLabel *text_label_;

public:
    explicit NoteWidget(
        QWidget *parent = nullptr,
        const project_storage_model::Note *model_note = nullptr,
        const std::string type = "actual",
        QListWidgetItem *p = nullptr
    );
    std::string type_;
    QListWidgetItem *project_;
    void handle_font_size_changed(std::string font_size_);
    void handle_language_changed(std::string new_language);
    QListWidgetItem* get_project() const;

private slots:

    void open_note_window() const;
    void delete_note();
    void change_type(std::string new_type);
signals:
    void change_type_requested(QListWidgetItem *project);
};
}  // namespace Ui
#endif  // NOTEWIDGET_H