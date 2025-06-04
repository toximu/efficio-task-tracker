#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <model-proto/model.pb.h>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "client_implementation.h"

using namespace Efficio_proto;

namespace Ui {
class NoteWidget : public QWidget {
    Q_OBJECT
    const Note *model_note_;
    QVBoxLayout *main_layout_;
    QPushButton *open_button_;
    QLabel *title_label_;
    QLabel *text_label_;
    ClientImplementation *client_;

public:
    explicit NoteWidget(
        QWidget *parent,
        const Note *model_note,
        ClientImplementation *client
    );

private slots:

    void open_note_window() const;
};
}  // namespace Ui
#endif  // NOTEWIDGET_H