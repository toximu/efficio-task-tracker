#include "notelist.h"
#include <QHBoxLayout>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

NoteList::NoteList(QWidget * parent)
    : QWidget(parent),
    main_layout_(new QHBoxLayout(this)),
      vertical_layout1_(new QVBoxLayout(this)),
      vertical_layout2_(new QVBoxLayout(this)),
      vertical_layout3_(new QVBoxLayout(this)),
      vertical_layout4_(new QVBoxLayout(this)) {

    main_layout_->addLayout(vertical_layout1_);
    main_layout_->addLayout(vertical_layout2_);
    main_layout_->addLayout(vertical_layout3_);
    main_layout_->addLayout(vertical_layout4_);
}
