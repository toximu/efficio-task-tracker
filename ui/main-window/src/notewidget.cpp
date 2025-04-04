#include "notewidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "note.hpp"
#include "note_edit_dialog.h"

namespace Ui {
NoteWidget::NoteWidget(
    QWidget *parent,
    const project_storage_model::Note *model_note
)
    : QWidget(parent),
      model_note_(model_note),
      main_layout_(new QVBoxLayout(this)),
      open_button_(new QPushButton("Открыть")) {
    this->setObjectName("NoteWidget");
    this->setMinimumWidth(100);
    this->setFixedHeight(100);
    title_label_ = new QLabel(model_note_->get_title().c_str(), this);
    text_label_ = new QLabel(model_note_->get_text().c_str(), this);
    main_layout_->addWidget(title_label_);
    main_layout_->addWidget(text_label_);

    text_label_->setWordWrap(false);
    title_label_->setWordWrap(false);
    text_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);
   

    main_layout_->addWidget(open_button_);

    connect(
        open_button_, &QPushButton::clicked, this, &NoteWidget::open_note_window
    );
    this->setLayout(main_layout_);
    this->setAttribute(Qt::WA_StyledBackground);
}

void NoteWidget::open_note_window() const {
    auto dialog = new ::NoteEditDialog(
        const_cast<QWidget *>(qobject_cast<const QWidget *>(this)),
        const_cast<Note *>(model_note_)
    );
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
    text_label_->setText(model_note_->get_text().c_str());
    title_label_->setText(model_note_->get_title().c_str());
    main_layout_->update();
}
}  // namespace Ui
