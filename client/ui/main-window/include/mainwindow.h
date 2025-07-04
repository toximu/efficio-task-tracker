#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <model-proto/model.pb.h>
#include <QScrollArea>
#include <QWidget>
#include <string>
#include "bottombar.h"
#include "client_implementation.h"
#include "notelist.h"
#include "projectlist.h"

namespace Ui {
class MainWindow;
}

namespace Ui {
class MainWindow : public QWidget {
    Q_OBJECT
    ClientImplementation *client_;
    std::unique_ptr<User> user_;
    std::string font_size_ = "medium";
    QVBoxLayout *main_layout_;
    QTabWidget *tab_widget_;
    BottomBar *top_bar_;
    QHBoxLayout *content_layout_;
    ProjectList *project_list_;
    NoteList *actual_notes_;
    NoteList *completed_notes_;
    NoteList *deleted_notes_;
    QWidget *content_widget_;
    QPushButton *new_project_button_;
    QPushButton *join_project_button_;
    QPushButton *new_note_button_;
    int actual_notes_amount_ = 0;
    int completed_notes_amount_ = 0;
    int deleted_notes_amount_ = 0;

    friend ProjectList;
private slots:
    void create_project();
    void add_project_by_code();
    void leave_project(ProjectItem *project_item);
    void update_notes_amount(int &notes_amount_, int loaded_amount, int type);
    void update_note_lists(
        QListWidgetItem *project,
        Note::Type::States old_type,
        Note::Type::States new_type
    );
    void load_project_notes(QListWidgetItem *project) const;
    void add_note();
    void on_profile_button_click();
signals:
    void logout_requested();
    void delete_account_requested();

public:
    explicit MainWindow(
        QWidget *parent,
        std::unique_ptr<User> user,
        ClientImplementation *client
    );
    static const std::vector<QString> THEMES;
    void on_logout_button_click();
    void on_delete_account_button_click();
    void handle_theme_changed(int theme);
    void handle_language_changed(std::string new_language);
    void handle_font_size_changed(std::string font_size_);
    QScrollArea *create_scroll_area(NoteList *note_list);
};
}  // namespace Ui
#endif  // MAINWINDOW_H