#include "mainwindow.h"
#include "bottombar.h"
#include "projectlist.h"
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QPalette>
#include <QPushButton>
#include <QSize>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QWidget>
#include <string>

MainWindow::MainWindow(QWidget *parent, std::string username)
    : QWidget(parent),
      bottom_bar(new BottomBar(this, username, "эффишио - таск трекер.")),
      main_layout(new QVBoxLayout(this)), content_layout(new QHBoxLayout(this)),
      project_list(new ProjectList(this)) {

  // this->resize(parent->size().width(), parent->size().height());

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

void MainWindow::add_project(std::string text) {

  project_list->addItem(
      new ProjectItem(text, static_cast<QListWidget *>(this->project_list)));
}
