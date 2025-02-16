#ifndef NOTE_EDIT_WINDOW_H
#define NOTE_EDIT_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
class NoteEditWindow;
}

QT_END_NAMESPACE

class NoteEditWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit NoteEditWindow(QWidget *parent = nullptr);
    ~NoteEditWindow();

private slots:
    void on_save_button_click();

private:
    Ui::NoteEditWindow *ui;
};

#endif  // NOTE_EDIT_WINDOW_H
