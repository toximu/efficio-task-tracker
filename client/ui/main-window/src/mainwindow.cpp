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
      completed_notes_(new NoteList(client_, this, Note::Type::completed)),
      deleted_notes_(new NoteList(client_, this, Note::Type::deleted)),
      content_widget_(new QWidget(this)),
      new_project_button_(new QPushButton("Создать", this)),
      new_note_button_(new QPushButton("Новая заметка", this)),
      join_project_button_(new QPushButton("Добавить", this)),
      tab_widget_(new QTabWidget(this)) {
    this->setObjectName("main-window");
    this->setAttribute(Qt::WA_StyledBackground);

    tab_widget_->addTab(create_scroll_area(actual_notes_), "Актуальные");
    tab_widget_->addTab(create_scroll_area(completed_notes_), "Выполненные");
    tab_widget_->addTab(create_scroll_area(deleted_notes_), "Удаленные");

    main_layout_->addWidget(top_bar_, Qt::AlignTop);
    main_layout_->setAlignment(Qt::AlignCenter);

    QWidget *right_panel = new QWidget(this);
    QVBoxLayout *right_layout = new QVBoxLayout(right_panel);
    QHBoxLayout *project_buttons_layout = new QHBoxLayout(right_panel);
    right_layout->addWidget(project_list_);
    project_buttons_layout->addWidget(new_project_button_);
    project_buttons_layout->addWidget(join_project_button_);
    right_layout->addLayout(project_buttons_layout);
    right_layout->addWidget(new_note_button_);

    tab_widget_->tabBar()->setExpanding(true);

    content_layout_->addWidget(tab_widget_, Qt::AlignRight);
    content_layout_->addWidget(right_panel);

    main_layout_->addWidget(top_bar_);
    main_layout_->addLayout(content_layout_);

    project_list_->load_projects(user_->mutable_storage());

    connect(
        project_list_, &QListWidget::itemClicked, this,
        &MainWindow::load_project_notes
    );

    connect(
        actual_notes_, &NoteList::change_note_type_requested, this,
        &Ui::MainWindow::update_note_lists
    );
    connect(
        completed_notes_, &NoteList::change_note_type_requested, this,
        &Ui::MainWindow::update_note_lists
    );
    connect(
        deleted_notes_, &NoteList::change_note_type_requested, this,
        &Ui::MainWindow::update_note_lists
    );

    connect(
        project_list_, &ProjectList::leave_project, this,
        &MainWindow::leave_project
    );

    connect(
        new_note_button_, &QPushButton::clicked, this, &Ui::MainWindow::add_note
    );
    connect(
        new_project_button_, &QPushButton::clicked, this,
        &Ui::MainWindow::create_project
    );
    connect(
        join_project_button_, &QPushButton::clicked, this,
        &Ui::MainWindow::add_project_by_code
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
        join_project_button_->setText("Присоединиться");
        new_project_button_->setText("Создать");
        new_note_button_->setText("Новая заметка");
        tab_widget_->setTabText(0, "Актуальные");
        tab_widget_->setTabText(1, "Выполненные");
        tab_widget_->setTabText(2, "Удаленные");
    } else if (new_language == "EN") {
        join_project_button_->setText("Join");
        new_project_button_->setText("New project");
        new_note_button_->setText("New note");
        tab_widget_->setTabText(0, "Actual");
        tab_widget_->setTabText(1, "Completed");
        tab_widget_->setTabText(2, "Deleted");
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
    ProfileWindow *new_profile_window = new ProfileWindow(
        client_, user_.get(), this->parentWidget(), actual_notes_amount_,
        completed_notes_amount_
    );
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
        Project *try_project = new Project();
        if (client_->try_join_project(
                try_project, code.toStdString(), *user_
            )) {
            Project *project = user_->mutable_storage()->add_projects();
            *project = std::move(*try_project);
            project_list_->add_project(project);
        }
    }
}

void MainWindow::leave_project(ProjectItem *project_item) {
    client_->try_leave_project(project_item->project_->code(), *user_);
    actual_notes_->clear_note_list();
    completed_notes_->clear_note_list();
    deleted_notes_->clear_note_list();
    delete project_item;
}

void MainWindow::update_notes_amount(
    int &notes_amount_,
    int loaded_amount,
    int type
) {
    if (notes_amount_ == 0) {
        notes_amount_ = loaded_amount;
    } else {
        notes_amount_ += type;
    }
    std::cout << notes_amount_ << std::endl;
}

void MainWindow::update_note_lists(
    QListWidgetItem *project,
    Note::Type::States old_type,
    Note::Type::States new_type
) {
    if (old_type == Note::Type::actual) {
        update_notes_amount(
            actual_notes_amount_,
            this->actual_notes_->load_project_notes(project), -1
        );
    }
    if (old_type == Note::Type::completed) {
        update_notes_amount(
            completed_notes_amount_,
            this->completed_notes_->load_project_notes(project), -1
        );
    }
    if (old_type == Note::Type::deleted) {
        update_notes_amount(
            deleted_notes_amount_,
            this->deleted_notes_->load_project_notes(project), -1
        );
    }

    if (new_type == Note::Type::actual) {
        update_notes_amount(
            actual_notes_amount_,
            this->actual_notes_->load_project_notes(project), 1
        );
    }
    if (new_type == Note::Type::completed) {
        update_notes_amount(
            completed_notes_amount_,
            this->completed_notes_->load_project_notes(project), 1
        );
    }
    if (new_type == Note::Type::deleted) {
        update_notes_amount(
            deleted_notes_amount_,
            this->deleted_notes_->load_project_notes(project), 1
        );
    }
}

void MainWindow::load_project_notes(QListWidgetItem *project) const {
    auto *p = dynamic_cast<ProjectItem *>(project);
    client_->get_project(p->project_, p->project_->code());
    actual_notes_->load_project_notes(project);
    completed_notes_->load_project_notes(project);
    deleted_notes_->load_project_notes(project);
}

void MainWindow::add_note() {
    auto project_item =
        dynamic_cast<ProjectItem *>(project_list_->currentItem());
    if (project_item) {
        Note *note = project_item->project_->add_notes();
        auto status =
            client_->try_create_note(note, project_item->project_->code());
        std::cout << "[CLIENT]: NOTE CREATED - "
                  << (status == 1 ? "TRUE" : "FALSE") << std::endl;
        actual_notes_->load_project_notes(project_list_->currentItem());
        actual_notes_amount_++;
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