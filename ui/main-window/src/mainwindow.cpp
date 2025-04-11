#include "mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QInputDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QScrollArea>
#include <string>
#include "bottombar.h"
#include "lr_dao.hpp"
#include "main_window_style.hpp"
#include "note_dao.hpp"
#include "notelist.h"
#include "project.hpp"
#include "project_dao.hpp"
#include "projectitem.h"
#include "projectlist.h"

namespace Ui {

const std::vector<QString> MainWindow::THEMES = {
    Ui::main_window_light_autumn_theme,
    Ui::main_window_dark_autumn_theme,
    Ui::main_window_dark_purple_theme,
    Ui::main_window_light_purple_theme,
    Ui::main_window_nature_flat_theme
};

MainWindow::MainWindow(
    QWidget *parent,
    std::string username,
    project_storage_model::Storage *storage,
    int number_of_theme_
)
    : QWidget(parent),
      username(username),
      main_layout_(new QVBoxLayout(this)),
      top_bar_(new BottomBar(this, username, "EFFICIO :: Таск-Трекер")),
      content_layout_(new QHBoxLayout(this)),
      project_list_(new ProjectList(this)),
      note_list_(new NoteList(this)),
      content_widget_(new QWidget(this)),
      new_project_button_(new QPushButton("Новый проект", this)),
      switch_theme_button_(new QPushButton(this)),
      new_note_button_(new QPushButton("Новая заметка", this)),
      storage_(storage), 
      number_of_theme(number_of_theme_) {
    this->setObjectName("main-window");
    this->setAttribute(Qt::WA_StyledBackground);
    this->setMinimumSize(QSize(800, 600));

    main_layout_->addWidget(top_bar_, Qt::AlignTop);
    main_layout_->setAlignment(Qt::AlignCenter);
    main_layout_->addWidget(content_widget_);
    content_widget_->setLayout(content_layout_);
    auto right_layout = new QVBoxLayout(content_widget_);
    right_layout->addWidget(project_list_);
    right_layout->addWidget(new_project_button_);
    right_layout->addWidget(new_note_button_);
    QScrollArea* scrollArea = new QScrollArea(content_widget_);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(note_list_);
    content_layout_->addWidget(scrollArea, Qt::AlignRight);
    content_layout_->addLayout(right_layout);
    main_layout_->addWidget(content_widget_);
    this->setLayout(main_layout_);

    switch_theme_button_->setObjectName("switch_theme_button_");
    right_layout->addWidget(switch_theme_button_, 0, Qt::AlignRight | Qt::AlignBottom);
    
    this->setStyleSheet(THEMES[number_of_theme_]);
    this->project_list_->load_projects(storage);

    connect(
        project_list_, &QListWidget::itemClicked, note_list_,
        &NoteList::load_project_notes
    );
    connect(
        new_note_button_, &QPushButton::clicked, this, &Ui::MainWindow::add_note
    );
    connect(
        switch_theme_button_, &QPushButton::clicked, this, 
        &Ui::MainWindow::on_switch_theme_clicked
    );
    connect(
        new_project_button_, &QPushButton::clicked, this,
        &Ui::MainWindow::add_project
    );
    connect(
        new_project_button_, &QPushButton::clicked, this,
        &Ui::MainWindow::add_project
    );
}

void MainWindow::add_project() {
    bool ok;
    QString name_of_project = QInputDialog::getText(
        nullptr, "Название проекта:", "Введите название", QLineEdit::Normal, "",
        &ok
    );
    if (ok) {
        int id = 0;

        if (DB::ProjectDAO::create_project(name_of_project.toStdString(), id)) {
            LRDao::add_project_to_user(username, id);
            auto &project = storage_->add_project(
                Project(id, name_of_project.toStdString(), "")
            );
            project_list_->add_project(&project);
        }
    }
}

void MainWindow::add_note() {
    auto project_item =
        dynamic_cast<ProjectItem *>(project_list_->currentItem());
    if (project_item) {
        if (int id = 0; NoteDao::initialize_note(id)) {
            DB::ProjectDAO::add_note_to_project(
                project_item->project_->get_id(), id
            );
            auto &note =
                project_item->project_->add_note({id, "Пустая заметка", ""});
            note_list_->add_note_widget(&note);
        }
    } else {
        QMessageBox msg;
        msg.setText("Проект не выбран!");
        msg.exec();
    }
}


void MainWindow::on_switch_theme_clicked() {
        this->number_of_theme = (this->number_of_theme+1)%THEMES.size();
        setStyleSheet(THEMES[this->number_of_theme]);
}

}  // namespace Ui