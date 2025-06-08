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
#include <string>
#include <QScreen>
#include <QString>
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
#include "style_manager.h"
#include "language_manager.h"
#include "registration_window.h"
#include "login_window.h"
#include <string>
#include <vector>

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
      top_bar_(new BottomBar(this, username, "EFFICIO :: Task-Tracker")),
      content_layout_(new QHBoxLayout(this)),
      project_list_(new ProjectList(this)),
      actual_notes_(new NoteList(this, "actual")),
      overdue_notes_(new NoteList(this, "overdue")),
      completed_notes_(new NoteList(this, "completed")),
      deleted_notes_(new NoteList(this, "deleted")),
      content_widget_(new QWidget(this)),
      new_project_button_(new QPushButton("Новый проект", this)),
      new_note_button_(new QPushButton("Новая заметка", this)),
      storage_(storage),
      tab_widget_(new QTabWidget(this)) {
    this->setObjectName("main-window");
    this->setAttribute(Qt::WA_StyledBackground);

    tab_widget_->addTab(create_scroll_area(actual_notes_), "Актуальные");
    tab_widget_->addTab(create_scroll_area(overdue_notes_), "Просроченные");
    tab_widget_->addTab(create_scroll_area(completed_notes_), "Выполненные");
    tab_widget_->addTab(create_scroll_area(deleted_notes_), "Удаленные");
    
    tab_widget_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    actual_notes_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    overdue_notes_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    completed_notes_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    deleted_notes_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    main_layout_->addWidget(top_bar_, Qt::AlignTop);
    main_layout_->setAlignment(Qt::AlignCenter);


    QWidget* right_panel = new QWidget(this);
    QVBoxLayout* right_layout = new QVBoxLayout(right_panel);
    //right_layout->setContentsMargins(0, 34, 0, 0); // Верхний отступ 10px
    right_layout->addWidget(project_list_);
    right_layout->addWidget(new_project_button_);
    right_layout->addWidget(new_note_button_);
    right_panel->setFixedWidth(210);
    tab_widget_->tabBar()->setExpanding(true);
    
    content_layout_->addWidget(tab_widget_);
    content_layout_->addWidget(right_panel);

    main_layout_->addWidget(top_bar_);
    main_layout_->addLayout(content_layout_);

    project_list_->load_projects(storage);

    connect(
        project_list_, &QListWidget::itemClicked, actual_notes_,
        &NoteList::load_project_notes
    );
    connect(
        project_list_, &QListWidget::itemClicked, overdue_notes_,
        &NoteList::load_project_notes
    );
    connect(
        project_list_, &QListWidget::itemClicked, completed_notes_,
        &NoteList::load_project_notes
    );
    connect(
        project_list_, &QListWidget::itemClicked, deleted_notes_,
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
        StyleManager::instance(), &StyleManager::theme_changed,
        this, &MainWindow::handle_theme_changed
    );
    connect(
        StyleManager::instance(), &StyleManager::font_size_changed,
        this, &MainWindow::handle_font_size_changed
    );
    connect(LanguageManager::instance(), &LanguageManager::language_changed,
            this, &MainWindow::handle_language_changed
    );
    handle_theme_changed(StyleManager::instance()->current_theme());
    handle_font_size_changed(StyleManager::instance()->current_font_size());
    handle_language_changed(LanguageManager::instance()->current_language());
}

QScrollArea* MainWindow::create_scroll_area(NoteList* note_list) {
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(note_list);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setFrameShape(QFrame::NoFrame);
    return scrollArea;
}

void MainWindow::handle_language_changed(std::string new_language) {
    if (new_language == "RU") {
        new_project_button_->setText("Новый проект");
        new_note_button_->setText("Новая заметка");
    } 
    else if(new_language == "EN") {
        new_project_button_->setText("New project");
        new_note_button_->setText("New note");
    }
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

void MainWindow::handle_font_size_changed(std::string font_size_) {

    QString font_rule;
    if (font_size_ == "small") {
        font_rule = "#ProjectList, #BottomBar QLabel, #BottomBar QPushButton, #NoteWidget QPushButton, QPushButton { font-size: 11px; }";
    }
    else if (font_size_ == "medium") {
        font_rule = "#ProjectList, #BottomBar QLabel, #BottomBar QPushButton, #NoteWidget QPushButton, QPushButton { font-size: 13px; }";
    }
    else if (font_size_ == "big") {
        font_rule = "#ProjectList, #BottomBar QLabel, #BottomBar QPushButton, #NoteWidget QPushButton, QPushButton { font-size: 15px; }";
    }

    this->setStyleSheet(THEMES[StyleManager::instance()->current_theme()] + font_rule);
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
    QString name_of_project;
    if (LanguageManager::instance()->current_language() == "RU") {
        name_of_project = QInputDialog::getText(
            nullptr, "Название проекта:", "Введите название", QLineEdit::Normal, "",
            &ok
        );
    } else if (LanguageManager::instance()->current_language() == "EN") {
        name_of_project = QInputDialog::getText(
            nullptr, "Name of project:", "Create a name", QLineEdit::Normal, "",
            &ok
        );
    }
    if (ok && name_of_project.trimmed()== ""){
        if (LanguageManager::instance()->current_language() == "RU") {
            QMessageBox::warning(this, "Ошибка", "Введите название!");
        } else {
            QMessageBox::warning(this, "Error", "Please enter a name!");
        }
    } else if (ok){
        int id = 0; 

        if (DB::ProjectDAO::create_project(name_of_project.trimmed().toStdString(), id)) {
            LRDao::add_project_to_user(username, id);
            auto &project = storage_->add_project(
                Project(id, name_of_project.trimmed().toStdString(), "")
            );
            project_list_->add_project(&project);
        }
    }
    handle_font_size_changed(StyleManager::instance()->current_font_size());
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
            actual_notes_->add_note_widget(&note, project_list_->currentItem());
        }
    } else {
        QMessageBox msg;
        if (LanguageManager::instance()->current_language() == "RU") {
            msg.setText("Сперва выберите проект!");
        } else if (LanguageManager::instance()->current_language() == "EN") {
            msg.setText("Choose a project first!");
        }
        msg.exec();
    }
}

}  // namespace Ui