#ifndef TAGS_DIALOG_H
#define TAGS_DIALOG_H

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <memory>
#include <vector>
#include <QString>


class TagsDialog final : public QDialog {
    Q_OBJECT

public:
    const static std::vector<QString> THEMES;
    void handle_theme_changed(int theme);
    const int MAX_TAGS_COUNT = 5;
    const std::pair<int, int> DIALOG_SIZE = std::make_pair(300, 250);

    struct Tag {
        bool is_checked;
        QString color;
        QString name;
    };

    explicit TagsDialog(
        const QList<Tag> &initial_tags = QList<Tag>(),
        QWidget *parent = nullptr
    );

    [[nodiscard]] QList<Tag> get_selected_tags() const;

private:
    void setup_ui();

    std::unique_ptr<QCheckBox> check_boxes_[5];
    std::unique_ptr<QComboBox> color_combo_boxes_[5];
    std::unique_ptr<QLineEdit> name_line_edits_[5];
    std::unique_ptr<QPushButton> ok_button_;
    std::unique_ptr<QPushButton> cancel_button_;
};

#endif  // TAGS_DIALOG_H