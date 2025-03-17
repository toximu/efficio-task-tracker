#include "../include/bottombar.h"
#include <QColor>
#include <QHBoxLayout>
#include <QPalette>
#include <QSize>
#include <QSizePolicy>
#include <QWidget>
#include <string>
namespace Ui {
BottomBar::BottomBar(QWidget *parent, std::string username,
                     std::string project_name)
    : QWidget(parent), main_layout_(new QHBoxLayout()),
      username_(new QLabel(username.c_str())),
      project_name_(new QLabel(project_name.c_str())) {

  this->setObjectName("BottomBar");
  this->setLayout(main_layout_);
  this->setFixedHeight(40);

  project_name_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  username_->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

  this->setSizePolicy(
      QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum));

  main_layout_->addWidget(project_name_);
  main_layout_->addWidget(username_);
}
} // namespace Ui
