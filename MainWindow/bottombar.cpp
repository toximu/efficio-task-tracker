#include "bottombar.h"
#include "widget.h"
#include <QColor>
#include <QHBoxLayout>
#include <QPalette>
#include <QSize>
#include <QSizePolicy>
#include <QWidget>
#include <string>

BottomBar::BottomBar(Widget *parent_, std::string username_,
                     std::string project_name_)
    : Widget(parent_), main_layout(new QHBoxLayout()),
      username(new QLabel(username_.c_str())),
      project_name(new QLabel(project_name_.c_str())), palette(new QPalette) {
  palette->setColor(QPalette::Window, QColor(64, 64, 64));
  palette->setColor(QPalette::WindowText, Qt::white);
  this->setPalette(*palette);
  this->setAutoFillBackground(true);
  this->setLayout(main_layout);
  this->setFixedHeight(40);

  project_name->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  username->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

  this->setSizePolicy(
      QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum));

  main_layout->addWidget(project_name);
  main_layout->addWidget(username);
}
