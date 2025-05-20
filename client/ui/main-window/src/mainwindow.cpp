#include "mainwindow.h"
#include <model-proto/model.pb.h>
#include <QDebug>
#include <QFile>
#include <QInputDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <string>
#include "bottombar.h"
#include "main_window_style.hpp"
#include "notelist.h"
#include "projectitem.h"
#include "projectlist.h"

using namespace Efficio_proto;

namespace Ui {
MainWindow::MainWindow(QWidget *parent, std::string username, Storage *storage)
    : QWidget(parent),
      username(username),
      main_layout_(new QVBoxLayout(this)),
      top_bar_(new BottomBar(this, username, "EFFICIO :: Таск-Трекер")),
      content_layout_(new QHBoxLayout(this)),
      project_list_(new ProjectList(this)),
      note_list_(new NoteList(this)),
      content_widget_(new QWidget(this)),
      new_project_button_(new QPushButton("Новый проект", this)),
      new_note_button_(new QPushButton("Новая заметка", this)),
      storage_(storage) {
    this->setObjectName("main-window");
    this->setAttribute(Qt::WA_StyledBackground);
    this->setMinimumSize(QSize(800, 600));
    this->setStyleSheet(main_window_style);

    main_layout_->addWidget(top_bar_, Qt::AlignTop);
    main_layout_->setAlignment(Qt::AlignCenter);
    main_layout_->addWidget(content_widget_);
    content_widget_->setLayout(content_layout_);
    auto right_layout = new QVBoxLayout(content_widget_);
    right_layout->addWidget(project_list_);
    right_layout->addWidget(new_project_button_);
    right_layout->addWidget(new_note_button_);
    QScrollArea *scrollArea = new QScrollArea(content_widget_);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(note_list_);
    content_layout_->addWidget(scrollArea, Qt::AlignRight);
    content_layout_->addLayout(right_layout);
    main_layout_->addWidget(content_widget_);
    this->setLayout(main_layout_);

    this->project_list_->load_projects(storage);

    connect(
        project_list_, &QListWidget::itemClicked, note_list_,
        &NoteList::load_project_notes
    );
    connect(
        new_note_button_, &QPushButton::clicked, this, &Ui::MainWindow::add_note
    );
    connect(
        new_project_button_, &QPushButton::clicked, this,
        &Ui::MainWindow::create_project
    );
}

void MainWindow::create_project() {
    bool ok;
    QString name_of_project = QInputDialog::getText(
        nullptr, "Название проекта:", "Введите название", QLineEdit::Normal, "",
        &ok
    );
    // TODO: notificate server
    // TODO: send request to server, get code
    if (ok) {
        Project *project = storage_->add_projects();
        project->set_title(name_of_project.toStdString());
        project_list_->add_project(project);
    }
}

void MainWindow::add_note() {
    auto project_item =
        dynamic_cast<ProjectItem *>(project_list_->currentItem());
    // TODO: notificate server
    if (project_item) {
        Note *note = project_item->project_->add_notes();
        note->set_title("Пустая заметка");
        note->set_allocated_text(new std::string(""));
        note_list_->add_note_widget(note);
    } else {
        QMessageBox msg;
        msg.setText("Проект не выбран!");
        msg.exec();
    }
}

}  // namespace Ui