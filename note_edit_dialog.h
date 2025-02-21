#ifndef NOTE_EDIT_DIALOG_H
#define NOTE_EDIT_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>

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

private:
    Ui::NoteEditDialog *ui;
};

#endif  // NOTE_EDIT_DIALOG_H
