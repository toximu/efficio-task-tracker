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
    Note * const model_note_;
    QVBoxLayout *main_layout_;
    QPushButton *open_button_;
    QLabel *title_label_;
    QHBoxLayout *tags_layout_;
    std::vector<QLabel *> tag_labels_;
    ClientImplementation *client_;

public:
    explicit NoteWidget(
        QWidget *parent,
        Note *model_note,
        ClientImplementation *client
    );
private:
    void update_tags();

private slots:
    void good_resize();
    void open_note_window() ;
};
}  // namespace Ui
#endif  // NOTEWIDGET_H