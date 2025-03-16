#ifndef TAGS_DIALOG_H
#define TAGS_DIALOG_H

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <memory>

class TagsDialog : public QDialog {
    Q_OBJECT

public:
    struct Tag {
        bool is_checked;
        QString color;
        QString name;
    };

    explicit TagsDialog(
        const QList<Tag> &initial_tags = QList<Tag>(),
        QWidget *parent = nullptr
    );

    QList<Tag> get_selected_tags() const;

private:
    void setup_ui();

    std::unique_ptr<QCheckBox> check_boxes[5];
    std::unique_ptr<QComboBox> color_combo_boxes[5];
    std::unique_ptr<QLineEdit> name_line_edits[5];
    std::unique_ptr<QPushButton> ok_button;
    std::unique_ptr<QPushButton> cancel_button;
};

#endif  // TAGS_DIALOG_H