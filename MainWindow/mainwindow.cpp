#include "mainwindow.h"
#include "bottombar.h"
#include "projectlist.h"
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
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget *parent, std::string username)
    : QWidget(parent),
      bottom_bar(new BottomBar(this, username, "эффишио - таск трекер.")),
      main_layout(new QVBoxLayout(this)), content_layout(new QHBoxLayout(this)),
      project_list(new ProjectList(this)) {
  this->setObjectName("MainWindow");

  this->setStyleSheet(
      R"(#ProjectList {
    background-color: #ffffff;
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
    background-color: #000000;
    border-radius: 8px;
    padding: 8px;
    outline: 0;
}

#BottomBar QLabel {
    color : white;
    font-family: -apple-system, BlinkMacSystemFont, sans-serif;
    font-size: 14px;
}
)");

  main_layout->addWidget(bottom_bar, Qt::AlignTop);

  main_layout->setAlignment(Qt::AlignCenter);

  content_layout->addStretch();
  content_layout->addWidget(project_list, Qt::AlignRight);
  main_layout->addLayout(content_layout, Qt::AlignVCenter);

  this->setLayout(main_layout);
  this->show();
}

void MainWindow::add_project(std::string text) {

  project_list->addItem(
      new ProjectItem(text, static_cast<QListWidget *>(this->project_list)));
}
