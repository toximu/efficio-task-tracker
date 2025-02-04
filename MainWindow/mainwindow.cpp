#include "mainwindow.h"
#include "bottombar.h"
#include "widget.h"
#include"projectlist.h"
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPalette>
#include <QPushButton>
#include <QSize>
#include <QSizePolicy>
#include <QVBoxLayout>

MainWindow::MainWindow(Widget *parent)
    : Widget(parent),
      bottom_bar(new BottomBar(this, "tima", "эффишио - таск трекер.")),
      main_layout(new QVBoxLayout(this)), content_layout(new QHBoxLayout(this)),
      project_list(new ProjectList(this)) {

  this->resize(800, 600);

  main_layout->addWidget(bottom_bar, Qt::AlignTop);

  main_layout->setAlignment(Qt::AlignCenter);
  main_layout->addStretch();

  content_layout->addStretch();
  content_layout->addWidget(project_list, Qt::AlignRight);
  main_layout->addLayout(content_layout, Qt::AlignVCenter);
  // content_layout->setAlignment(Qt::AlignRight);


  this->setLayout(main_layout);
  this->show();
}
