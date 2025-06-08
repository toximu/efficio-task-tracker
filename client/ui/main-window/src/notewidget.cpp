#include "notewidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
// #include
// "../../../../cmake-build-just-run/client/ui/note-widget/NoteWidget_autogen/include/ui_note_edit_dialog.h"
#include <QMainWindow>
#include "note_edit_dialog.h"

namespace Ui {
NoteWidget::NoteWidget(
    QWidget *parent,
    Note *model_note,
    ClientImplementation *client
)
    : QWidget(parent),
      model_note_(model_note),
      main_layout_(new QVBoxLayout(this)),
      open_button_(new QPushButton("Открыть")),
      tags_layout_(new QHBoxLayout(this)),
      tag_labels_(),
      client_(client) {
    this->setObjectName("NoteWidget");
    this->setMinimumWidth(100);

    this->setFixedHeight(110);
    title_label_ = new QLabel(model_note_->title().c_str(), this);

    title_label_->setStyleSheet(
        "color: rgb(33, 44, 50);"
    );

    main_layout_->addWidget(title_label_);
    main_layout_->addLayout(tags_layout_);
    update_tags();
    // title_label_->setWordWrap(true);

    main_layout_->addWidget(open_button_);

    connect(
        open_button_, &QPushButton::clicked, this, &NoteWidget::open_note_window
    );
    this->setLayout(main_layout_);
    this->setAttribute(Qt::WA_StyledBackground);
}

void NoteWidget::open_note_window() {
    client_->try_fetch_note(model_note_);
    auto dialog = new ::NoteEditDialog(
        client_, const_cast<QWidget *>(qobject_cast<const QWidget *>(this)),
        const_cast<Note *>(model_note_)
    );
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    update_tags();
    dialog->exec();

    title_label_->setText(model_note_->title().c_str());
    update_tags();
    main_layout_->update();
}

void NoteWidget::update_tags() {
    for (auto tag : tag_labels_) {
        tags_layout_->removeWidget(tag);
        delete tag;
    }
    tag_labels_.clear();

    for (auto tag : model_note_->tags()) {
        QLabel *tag_label = new QLabel(this);
        tag_label->setText(tag.text().c_str());
        tag_label->setStyleSheet(
            ::NoteEditDialog::create_tag_style_sheet(tag.color())
        );
        tag_label->resize(tag_label->sizeHint());
        tag_labels_.push_back(tag_label);
        tags_layout_->addWidget(tag_label);
    }
}

void NoteWidget::good_resize() {
    setMaximumWidth(reinterpret_cast<QWidget *>(parent())->width() / 3);
}

}  // namespace Ui
