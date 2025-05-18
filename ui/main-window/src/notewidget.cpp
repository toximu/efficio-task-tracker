#include "notewidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "note.hpp"
#include "note_edit_dialog.h"
#include "style_manager.h"

namespace Ui {
NoteWidget::NoteWidget(
    QWidget *parent,
    const project_storage_model::Note *model_note, 
    int number_of_theme_
)
    : QWidget(parent),
      model_note_(model_note),
      main_layout_(new QVBoxLayout(this)),
      open_button_(new QPushButton(tr("Открыть"))),
      number_of_theme(number_of_theme_) {
    this->setObjectName("NoteWidget");
    this->setMinimumWidth(100);
    this->setFixedHeight(100);
    title_label_ = new QLabel(QString::fromStdString(model_note_->get_title()), this);
    text_label_ = new QLabel(QString::fromStdString(model_note_->get_text()), this);
    
    title_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 15px;");
    text_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 15px;");
    
    main_layout_->addWidget(title_label_);
    main_layout_->addWidget(text_label_);

    text_label_->setWordWrap(false);
    title_label_->setWordWrap(false);
    text_label_->setTextInteractionFlags(Qt::TextSelectableByMouse);

    main_layout_->addWidget(open_button_);

    connect(
        open_button_, &QPushButton::clicked, this, &NoteWidget::open_note_window
    );
    connect(
        StyleManager::instance(), &StyleManager::font_size_changed,
        this, &NoteWidget::handle_font_size_changed
    );
    this->setLayout(main_layout_);
    this->setAttribute(Qt::WA_StyledBackground);
}

void NoteWidget::handle_font_size_changed(std::string font_size_){
    QString font_rule;
    if (font_size_ == "small") {
        title_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 13px;");
        text_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 11px;");
    }
    else if (font_size_ == "medium") {
        title_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 15px;");
        text_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 13px;");
    }
    else if (font_size_ == "big") {
        title_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 17px;");
        text_label_->setStyleSheet("color: rgb(33, 44, 50); font-size: 15px;");
    }
}

void NoteWidget::open_note_window() const {
    auto dialog = new ::NoteEditDialog(
        const_cast<QWidget *>(qobject_cast<const QWidget *>(this)),
        const_cast<Note *>(model_note_)
    );
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
    text_label_->setText(QString::fromStdString(model_note_->get_text()));
    title_label_->setText(QString::fromStdString(model_note_->get_title()));
    main_layout_->update();
}
}  // namespace Ui