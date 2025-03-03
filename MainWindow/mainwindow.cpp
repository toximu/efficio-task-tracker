#include "mainwindow.h"
#include "bottombar.h"
#include "project.hpp"
#include "projectlist.h"
#include"notelist.h"
#include <QFile>
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

namespace Ui {
MainWindow::MainWindow(QWidget *parent, std::string username)
    : QWidget(parent),
      bottom_bar_(new BottomBar(this, username, "эффишио - таск трекер.")),
      main_layout_(new QVBoxLayout(this)),
      content_layout_(new QHBoxLayout(this)),
note_list_(new NoteList(this)),
      project_list_(new ProjectList(this))

{
  this->setObjectName("MainWindow");
this->setAttribute(Qt::WA_StyledBackground);
  this->setStyleSheet(
      R"(
#MainWindow {
    background-color : white;
}
#ProjectList {
    background-color: #FED6BC;
    border: 1px solid #e0e0e0;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
    font-family: -apple-system, BlinkMacSystemFont, sans-serif;
    font-size: 14px;
    color: #000000;
}

#ProjectList::item {
    background-color: transparent;
    border: none;
    padding: 10px;
    margin: 2px;
    border-radius: 6px;
}

#ProjectList::item:hover {
    background-color: #f5f5f5;
}

#ProjectList::item:selected {
    background-color: #007aff;
    color: #ffffff;
}

#ProjectList QScrollBar:vertical {
    border: none;
    background: #f0f0f0;
    width: 10px;
    margin: 0;
}

#ProjectList QScrollBar::handle:vertical {
    background: #c0c0c0;
    border-radius: 5px;
    min-height: 20px;
}

#ProjectList QScrollBar::add-line:vertical,
#ProjectList QScrollBar::sub-line:vertical {
    background: none;
}

#ProjectList QScrollBar::add-page:vertical,
#ProjectList QScrollBar::sub-page:vertical {
    background: none;
}

#BottomBar {
    background-color: black;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
}

#BottomBar QLabel {
    color : white;
    font-family: -apple-system, BlinkMacSystemFont, sans-serif;
    font-size: 14px;
}

#NoteWidget {
    background-color: #C6D8FF;
border-radius: 8px;

}

#NoteList {
    border : 1px solid #A9A9A9;
border-radius : 8px;
}

)");


  main_layout_->addWidget(bottom_bar_, Qt::AlignTop);

  main_layout_->setAlignment(Qt::AlignCenter);

  QWidget * content_widget = new QWidget(this);
  note_list_->setParent(content_widget);
  main_layout_->addWidget(content_widget);
  content_widget->setLayout(content_layout_);
  content_layout_->addWidget(note_list_, Qt::AlignRight);
  content_layout_->addWidget(project_list_, Qt::AlignRight);
  main_layout_->addLayout(content_layout_, Qt::AlignVCenter);

  this->setLayout(main_layout_);

  // connections
   connect(project_list_, &QListWidget::itemClicked,note_list_ ,&NoteList::load_project_notes);

}

void MainWindow::add_project(project_storage_model::Project *project) {
  project_list_->addItem(new ProjectItem(
      project, static_cast<QListWidget *>(this->project_list_)));
}
}


