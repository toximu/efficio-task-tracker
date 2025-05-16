#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <string>
#include "bottombar.h"
#include "notelist.h"
#include "projectlist.h"
#include "storage.hpp"
#include <vector>
#include "profile_window.h"

namespace Ui {
    class MainWindow;
}

namespace Ui {
class MainWindow : public QWidget {
    Q_OBJECT
    std::string username;
    QVBoxLayout *main_layout_;
    BottomBar *top_bar_;
    QHBoxLayout *content_layout_;
    ProjectList *project_list_;
    NoteList *note_list_;
    QWidget *content_widget_;
    QPushButton *new_project_button_;
    QPushButton *new_note_button_;
    project_storage_model::Storage *storage_;

    friend ProjectList;
private slots:
    void add_project();
    void add_note();
    void on_profile_button_click();
signals:
    void logout_requested();
    void delete_account_requested();

public:
    explicit MainWindow(
        QWidget *parent = nullptr,
        std::string username = "none",
        project_storage_model::Storage *storage = nullptr
    );
    static const std::vector<QString> THEMES;
    void on_logout_button_click();
    void on_delete_account_button_click();
    void handle_theme_changed(int theme);
};
}  // namespace Ui
#endif  // MAINWINDOW_H