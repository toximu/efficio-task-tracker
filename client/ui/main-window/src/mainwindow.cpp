#include "mainwindow.h"
#include <model-proto/model.pb.h>
#include <QApplication>
#include <QFile>
#include <QInputDialog>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QScreen>
#include <QScrollArea>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include <string>
#include <vector>
#include "bottombar.h"
#include "language_manager.h"
#include "login_window.h"
#include "lr_dao.hpp"
#include "main_window_style.hpp"
#include "note_dao.hpp"
#include "notelist.h"
#include "profile_window.h"
#include "project_dao.hpp"
#include "projectitem.h"
#include "projectlist.h"
#include "style_manager.h"

namespace Ui {

const std::vector<QString> MainWindow::THEMES = {
    Ui::main_window_light_autumn_theme, Ui::main_window_dark_autumn_theme,
    Ui::main_window_dark_purple_theme, Ui::main_window_light_purple_theme,
    Ui::main_window_blue_theme
};

MainWindow::MainWindow(
    QWidget *parent,
    std::unique_ptr<User> user,
    ClientImplementation *client
)
    : QWidget(parent),
      client_(client),
      user_(std::move(user)),
      main_layout_(new QVBoxLayout(this)),
      top_bar_(new BottomBar(this, user_->login(), "EFFICIO :: Таск-Трекер")),
      content_layout_(new QHBoxLayout(this)),
      project_list_(new ProjectList(this)),
      actual_notes_(new NoteList(client_, this, Note::Type::actual)),
      overdue_notes_(new NoteList(client_, this, Note::Type::overdue)),
      completed_notes_(new NoteList(client_, this, Note::Type::completed)),
      deleted_notes_(new NoteList(client_, this, Note::Type::deleted)),
      content_widget_(new QWidget(this)),
      new_project_button_(new QPushButton("Новый проект", this)),
      new_note_button_(new QPushButton("Новая заметка", this)),
      join_project_button_(new QPushButton("Добавить", this)),
      tab_widget_(new QTabWidget(this)) {
    this->setObjectName("main-window");
    this->setAttribute(Qt::WA_StyledBackground);

    tab_widget_->addTab(create_scroll_area(actual_notes_), "Актуальные");
    tab_widget_->addTab(create_scroll_area(overdue_notes_), "Просроченные");
    tab_widget_->addTab(create_scroll_area(completed_notes_), "Выполненные");
    tab_widget_->addTab(create_scroll_area(deleted_notes_), "Удаленные");

    tab_widget_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    actual_notes_->setSizePolicy(
        QSizePolicy::Expanding, QSizePolicy::Expanding
    );
    overdue_notes_->setSizePolicy(
        QSizePolicy::Expanding, QSizePolicy::Expanding
    );
    completed_notes_->setSizePolicy(
        QSizePolicy::Expanding, QSizePolicy::Expanding
    );
    deleted_notes_->setSizePolicy(
        QSizePolicy::Expanding, QSizePolicy::Expanding
    );

    main_layout_->addWidget(top_bar_, Qt::AlignTop);
    main_layout_->setAlignment(Qt::AlignCenter);

    QWidget *right_panel = new QWidget(this);
    QVBoxLayout *right_layout = new QVBoxLayout(right_panel);
    right_layout->addWidget(project_list_);
    right_layout->addWidget(new_project_button_);
    right_layout->addWidget(new_note_button_);
    right_panel->setFixedWidth(210);
    tab_widget_->tabBar()->setExpanding(true);

    content_layout_->addWidget(tab_widget_);
    content_layout_->addWidget(right_panel);

    main_layout_->addWidget(top_bar_);
    main_layout_->addLayout(content_layout_);

    project_list_->load_projects(user_->mutable_storage());

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
        &Ui::MainWindow::create_project
    );
    connect(
        top_bar_, &Ui::BottomBar::profile_button_clicked, this,
        &MainWindow::on_profile_button_click
    );
    connect(
        StyleManager::instance(), &StyleManager::theme_changed, this,
        &MainWindow::handle_theme_changed
    );
    connect(
        StyleManager::instance(), &StyleManager::font_size_changed, this,
        &MainWindow::handle_font_size_changed
    );
    connect(
        LanguageManager::instance(), &LanguageManager::language_changed, this,
        &MainWindow::handle_language_changed
    );
    handle_theme_changed(StyleManager::instance()->current_theme());
    handle_font_size_changed(StyleManager::instance()->current_font_size());
    handle_language_changed(LanguageManager::instance()->current_language());
}

QScrollArea *MainWindow::create_scroll_area(NoteList *note_list) {
    QScrollArea *scrollArea = new QScrollArea();
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
    } else if (new_language == "EN") {
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
        font_rule =
            "#ProjectList, #BottomBar QLabel, #BottomBar QPushButton, "
            "#NoteWidget QPushButton, QPushButton { font-size: 11px; }";
    } else if (font_size_ == "medium") {
        font_rule =
            "#ProjectList, #BottomBar QLabel, #BottomBar QPushButton, "
            "#NoteWidget QPushButton, QPushButton { font-size: 13px; }";
    } else if (font_size_ == "big") {
        font_rule =
            "#ProjectList, #BottomBar QLabel, #BottomBar QPushButton, "
            "#NoteWidget QPushButton, QPushButton { font-size: 15px; }";
    }

    this->setStyleSheet(
        THEMES[StyleManager::instance()->current_theme()] + font_rule
    );
}

void MainWindow::on_profile_button_click() {
    this->setEnabled(false);
    ProfileWindow *new_profile_window =
        new ProfileWindow(client_, user_.get(), this->parentWidget());
    new_profile_window->setAttribute(Qt::WA_DeleteOnClose);
    connect(
        new_profile_window, &ProfileWindow::logout_requested, this,
        &MainWindow::on_logout_button_click
    );
    connect(
        new_profile_window, &ProfileWindow::delete_account_requested, this,
        &MainWindow::on_delete_account_button_click
    );
    connect(new_profile_window, &ProfileWindow::destroyed, this, [this]() {
        this->setEnabled(true);
    });
    new_profile_window->show();
    new_profile_window->raise();
    new_profile_window->activateWindow();
}

void MainWindow::create_project() {
    bool ok;
    QString name_of_project = QInputDialog::getText(
        nullptr, "Название проекта:", "Введите название", QLineEdit::Normal, "",
        &ok
    );

    if (ok) {
        Project *project = user_->mutable_storage()->add_projects();
        client_->create_project(project, name_of_project.toStdString(), *user_);
        project_list_->add_project(project);
    }
}

void MainWindow::add_project_by_code() {
    bool ok;
    QString code = QInputDialog::getText(
        nullptr, "Код", "Введите код:", QLineEdit::Normal, "", &ok
    );

    if (ok) {
        Project *project = user_->mutable_storage()->add_projects();
        client_->try_join_project(project, code.toStdString(), *user_);
        project_list_->add_project(project);
    }
}

void MainWindow::add_note() {
    auto project_item =
        dynamic_cast<ProjectItem *>(project_list_->currentItem());
    if (project_item) {
        Note *note = project_item->project_->add_notes();
        client_->try_create_note(note, project_item->project_->code());
        actual_notes_->add_note_widget(note, project_list_->currentItem());
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