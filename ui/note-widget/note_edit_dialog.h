#ifndef NOTE_EDIT_DIALOG_H
#define NOTE_EDIT_DIALOG_H

#include <QLabel>
#include <memory>
#include "note.hpp"
#include "note_dao.hpp"
#include "tags_dialog.h"

using namespace project_storage_model;

QT_BEGIN_NAMESPACE

namespace Ui {
class NoteEditDialog;
}

QT_END_NAMESPACE

class NoteEditDialog final : public QDialog {
    Q_OBJECT

public:
    explicit NoteEditDialog(
        QWidget *parent = nullptr,
        Note *note = new Note(0, "NULL", "NULL")
    );
    ~NoteEditDialog() override;

private slots:
    void on_save_button_click();
    void on_join_button_click();
    void on_add_members_button_click();
    void on_add_tags_button_click();

private:
    Ui::NoteEditDialog *ui_;
    std::unique_ptr<QLabel> avatar_label_;
    std::vector<std::unique_ptr<QLabel>> tag_labels_;
    QList<TagsDialog::Tag> selected_tags_;
    Note *note_;

    [[nodiscard]] bool try_save_note() const;
};

#endif  // NOTE_EDIT_DIALOG_H
