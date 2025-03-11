#include "mainwindow.h"
#include "bottombar.h"
#include "notelist.h"
#include "project.hpp"
#include "projectlist.h"
#include <QFile>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <string>

namespace Ui {
MainWindow::MainWindow(QWidget *parent, std::string username,
                       project_storage_model::Storage *storage)
    : QWidget(parent), content_widget_(new QWidget(this)),
      bottom_bar_(new BottomBar(this, username, " -  .")),
      main_layout_(new QVBoxLayout(this)),
      content_layout_(new QHBoxLayout(this)), note_list_(new NoteList(this)),
      project_list_(new ProjectList(this)),
      new_note_button_(new QPushButton("", this)), storage_(storage),
      new_project_button_(new QPushButton(" ", this))

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
  main_layout_->addWidget(content_widget_);

  content_widget_->setLayout(content_layout_);

  auto right_layout = new QVBoxLayout(content_widget_);
  right_layout->addWidget(project_list_);
  right_layout->addWidget(new_project_button_);

  content_layout_->addWidget(note_list_, Qt::AlignRight);
  content_layout_->addLayout(right_layout);
  main_layout_->addWidget(content_widget_);

  this->setLayout(main_layout_);

  // connections
  connect(project_list_, &QListWidget::itemClicked, note_list_,
          &NoteList::load_project_notes);
  connect(new_note_button_, &QPushButton::clicked, this,
          &MainWindow::add_empty_note);
}

void MainWindow::add_project(project_storage_model::Project *project) {
  project_list_->addItem(new ProjectItem(
      project, static_cast<QListWidget *>(this->project_list_)));
}

void MainWindow::add_empty_note() {
  project_storage_model::Note &note =
      dynamic_cast<ProjectItem *>(project_list_->currentItem())
          ->project_->add_note({1, "new note", ""});
  note_list_->add_note_widget(&note);
}

} // namespace Ui
