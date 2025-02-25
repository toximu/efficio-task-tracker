#include "tags_dialog.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "tags_dialog_styles.h"

TagsDialog::TagsDialog(const QList<Tag> &initial_tags, QWidget *parent)
    : QDialog(parent) {
    setup_ui();

    for (int i = 0; i < qMin(5, initial_tags.size()); ++i) {
        const Tag &tag = initial_tags[i];
        check_boxes[i]->setChecked(tag.is_checked);
        int color_index = color_combo_boxes[i]->findData(tag.color);
        if (color_index != -1) {
            color_combo_boxes[i]->setCurrentIndex(color_index);
        }
        name_line_edits[i]->setText(tag.name);
    }

    setWindowTitle("Добавить теги");
    setModal(true);
    setFixedSize(300, 250);
    setStyleSheet(Ui::tags_dialog_light_theme);
}

TagsDialog::~TagsDialog() {
}

void TagsDialog::setup_ui() {
    QVBoxLayout *main_layout = new QVBoxLayout(this);

    for (int i = 0; i < 5; ++i) {
        QHBoxLayout *tag_layout = new QHBoxLayout;

        check_boxes[i] = new QCheckBox(this);
        check_boxes[i]->setChecked(false);
        tag_layout->addWidget(check_boxes[i]);

        color_combo_boxes[i] = new QComboBox(this);
        color_combo_boxes[i]->addItem("Красный", "#e7624b");
        color_combo_boxes[i]->addItem("Синий", "#165d7b");
        color_combo_boxes[i]->addItem("Розовый", "#bd6dab");
        color_combo_boxes[i]->addItem("Зеленый", "#00b16b");
        color_combo_boxes[i]->addItem("Желтый", "#e69f00");
        tag_layout->addWidget(color_combo_boxes[i]);

        name_line_edits[i] = new QLineEdit(this);
        name_line_edits[i]->setPlaceholderText(
            "Имя тега " + QString::number(i + 1)
        );
        tag_layout->addWidget(name_line_edits[i]);

        main_layout->addLayout(tag_layout);
    }

    QHBoxLayout *button_layout = new QHBoxLayout;

    ok_button = new QPushButton("OK", this);
    ok_button->setObjectName("ok_button");
    button_layout->addWidget(ok_button);

    cancel_button = new QPushButton("Отмена", this);
    cancel_button->setObjectName("cancel_button");
    button_layout->addWidget(cancel_button);

    main_layout->addLayout(button_layout);

    connect(ok_button, &QPushButton::clicked, this, &TagsDialog::accept);
    connect(cancel_button, &QPushButton::clicked, this, &TagsDialog::reject);
}

QList<TagsDialog::Tag> TagsDialog::get_selected_tags() const {
    QList<Tag> tags;
    for (int i = 0; i < 5; ++i) {
        if (check_boxes[i]->isChecked() &&
            !name_line_edits[i]->text().isEmpty()) {
            Tag tag;
            tag.is_checked = true;
            tag.color = color_combo_boxes[i]->currentData().toString();
            tag.name = name_line_edits[i]->text();
            tags.append(tag);
        }
    }
    return tags;
}
