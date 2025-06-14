#pragma once

#include <QDialog>
#include <QListWidget>
#include <string>
#include <vector>

class MemberSelectionDialog : public QDialog {
    Q_OBJECT
public:
    explicit MemberSelectionDialog(
        const std::vector<std::string> &available_members,
        QWidget *parent = nullptr
    );

    std::vector<std::string> get_selected_members() const;

private:
    QListWidget *members_list;
    QColor generate_random_color(const std::string &seed) const;
    QPixmap create_circle_icon(const QColor &color, int size = 32) const;
};