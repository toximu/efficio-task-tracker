#ifndef TAGS_DIALOG_H
#define TAGS_DIALOG_H

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QLineEdit>

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
    ~TagsDialog();

    QList<Tag> get_selected_tags() const;

private:
    void setup_ui();

    QCheckBox *check_boxes[5];
    QComboBox *color_combo_boxes[5];
    QLineEdit *name_line_edits[5];
    QPushButton *ok_button;
    QPushButton *cancel_button;
};

#endif  // TAGS_DIALOG_H
