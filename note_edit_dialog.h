#ifndef NOTE_EDIT_DIALOG_H
#define NOTE_EDIT_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include "tags_dialog.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class NoteEditDialog;
}

QT_END_NAMESPACE

class NoteEditDialog : public QDialog {
    Q_OBJECT

public:
    explicit NoteEditDialog(QWidget *parent = nullptr);
    ~NoteEditDialog();

private slots:
    void on_save_button_click();
    void on_join_button_click();
    void on_add_members_button_click();
    void on_add_tags_button_click();

private:
    Ui::NoteEditDialog *ui;
    QLabel *avatar_label;
    QList<QLabel *> tag_labels;
    QList<TagsDialog::Tag> selected_tags;
};

#endif  // NOTE_EDIT_DIALOG_H
