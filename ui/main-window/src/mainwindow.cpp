#include "mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QInputDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QApplication>  
#include <QMainWindow>   
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QScrollArea>
#include <string>
#include <QScreen>
#include "applicationwindow.h"
#include "bottombar.h"
#include "lr_dao.hpp"
#include "main_window_style.hpp"
#include "note_dao.hpp"
#include "notelist.h"
#include "project.hpp"
#include "project_dao.hpp"
#include "projectitem.h"
#include "projectlist.h"
#include "theme_manager.h"
#include "registration_window.h"
#include "login_window.h"

namespace Ui {

const std::vector<QString> MainWindow::THEMES = {
    Ui::main_window_light_autumn_theme,
    Ui::main_window_dark_autumn_theme,
    Ui::main_window_dark_purple_theme,
    Ui::main_window_light_purple_theme,
    Ui::main_window_blue_theme
};

MainWindow::MainWindow(
    QWidget *parent,
    std::string username,
    project_storage_model::Storage *storage
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
      new_note_button_(new QPushButton("Новая заметка", this)),
      storage_(storage) {
    this->setObjectName("main-window");
    this->setAttribute(Qt::WA_StyledBackground);
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
        &Ui::MainWindow::add_project
    );
    connect(
        top_bar_, &Ui::BottomBar::profile_button_clicked, 
        this, &MainWindow::on_profile_button_click
    );
    connect(
        ThemeManager::instance(), &ThemeManager::theme_changed,
        this, &MainWindow::handle_theme_changed
    );
    handle_theme_changed(ThemeManager::instance()->current_theme());
}

void MainWindow::on_delete_account_button_click() {
    this->deleteLater();
    emit delete_account_requested();
}

void MainWindow::on_logout_button_click() {
    this->deleteLater();
    emit logout_requested();
}

void MainWindow::handle_theme_changed(int theme) {
    this->setStyleSheet(THEMES[theme]);
}

void MainWindow::on_profile_button_click() {
    this->setEnabled(false);
    ProfileWindow *new_profile_window = new ProfileWindow(QString::fromStdString(this->username), this->parentWidget());
    new_profile_window->setAttribute(Qt::WA_DeleteOnClose);
    connect(
        new_profile_window, &ProfileWindow::logout_requested,
        this, &MainWindow::on_logout_button_click
    );
    connect(
        new_profile_window, &ProfileWindow::delete_account_requested,
        this, &MainWindow::on_delete_account_button_click
    ); 
    connect(new_profile_window, &ProfileWindow::destroyed, 
        this, [this]() { this->setEnabled(true); });   
    new_profile_window->show();
    new_profile_window->raise();  
    new_profile_window->activateWindow();
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

}  // namespace Ui