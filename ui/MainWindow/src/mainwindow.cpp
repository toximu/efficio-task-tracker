#include "mainwindow.h"
#include "bottombar.h"
#include "notelist.h"
#include "project.hpp"
#include "projectlist.h"
#include "projectitem.h"
#include <QFile>
#include <QInputDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <string>
#include <QDebug>


namespace Ui {
MainWindow::MainWindow(QWidget *parent, std::string username,
                       project_storage_model::Storage *storage)
    : QWidget(parent),main_layout_(new QVBoxLayout(this)),
    top_bar_(new BottomBar(this, username, "эффишио - таск трекер.")),
    content_layout_(new QHBoxLayout(this)),
    project_list_(new ProjectList(this)),
    note_list_(new NoteList(this)),
    content_widget_(new QWidget(this)),
    new_project_button_(new QPushButton("Новый проект", this)),
      new_note_button_(new QPushButton("Новая заметка", this)),
    storage_(storage)
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

  main_layout_->addWidget(top_bar_, Qt::AlignTop);

  main_layout_->setAlignment(Qt::AlignCenter);
  main_layout_->addWidget(content_widget_);

  content_widget_->setLayout(content_layout_);

  auto right_layout = new QVBoxLayout(content_widget_);
  right_layout->addWidget(project_list_);
  right_layout->addWidget(new_project_button_);
  right_layout->addWidget(new_note_button_);

  content_layout_->addWidget(note_list_, Qt::AlignRight);
  content_layout_->addLayout(right_layout);
  main_layout_->addWidget(content_widget_);

  this->setLayout(main_layout_);

  // connections
  connect(project_list_, &QListWidget::itemClicked, note_list_,
          &NoteList::load_project_notes);
  connect(new_note_button_, &QPushButton::clicked, this, &add_note);
  connect(new_project_button_, &QPushButton::clicked, this, &add_project);
}

void MainWindow::add_project() {

  bool ok;
  QString name_of_project =
      QInputDialog::getText(nullptr, "Название проекта:", "Введите название",
                            QLineEdit::Normal, "", &ok);
  if (ok) {
    auto &project = storage_->add_project(
        project_storage_model::Project(1, name_of_project.toStdString(), ""));
    project_list_->add_project(&project);
  }
}

void MainWindow::add_note() {
  auto project_item = dynamic_cast<ProjectItem *>(project_list_->currentItem());
    // qDebug() << "Note add to " << project_item->project_->get_name() << "its address: " << project_item->project_;
  if (project_item) {
    auto &note = project_item->project_->add_note({1, "empty", ""});
    note_list_->add_note_widget(&note);
  } else {
    QMessageBox msg;
    msg.setText("Проект не выбран!");
    msg.exec();
  }
}

} // namespace Ui
