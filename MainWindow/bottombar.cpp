#include "bottombar.h"
#include <QColor>
#include <QHBoxLayout>
#include <QPalette>
#include <QSize>
#include <QSizePolicy>
#include <QWidget>
#include <string>
namespace Ui {
BottomBar::BottomBar(QWidget *parent_, std::string username_,
                     std::string project_name_)
    : QWidget(parent_), main_layout(new QHBoxLayout()),
      username(new QLabel(username_.c_str())),
      project_name(new QLabel(project_name_.c_str())) {

  this->setObjectName("BottomBar");
  this->setLayout(main_layout);
  this->setFixedHeight(40);

  project_name->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  username->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

  this->setSizePolicy(
      QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum));

  main_layout->addWidget(project_name);
  main_layout->addWidget(username);
}
}
