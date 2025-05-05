#include "tags_dialog.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "tags_dialog_styles.h"

TagsDialog::TagsDialog(const QList<Tag> &initial_tags, QWidget *parent)
    : QDialog(parent) {
    setup_ui();

    for (int i = 0; i < qMin(MAX_TAGS_COUNT, initial_tags.size()); ++i) {
        const auto &[is_checked, color, name] = initial_tags[i];
        check_boxes_[i]->setChecked(is_checked);

        const int color_index = color_combo_boxes_[i]->findData(color);
        if (color_index != -1) {
            color_combo_boxes_[i]->setCurrentIndex(color_index);
        }

        name_line_edits_[i]->setText(name);
    }

    setWindowTitle("Добавить теги");
    setModal(true);
    setFixedSize(DIALOG_SIZE.first, DIALOG_SIZE.second);
    setStyleSheet(Ui::tags_dialog_light_theme);
}

void TagsDialog::setup_ui() {
    auto *main_layout = new QVBoxLayout(this);

    for (int i = 0; i < MAX_TAGS_COUNT; ++i) {
        auto *tag_layout = new QHBoxLayout();

        check_boxes_[i] = std::make_unique<QCheckBox>(this);
        check_boxes_[i]->setChecked(false);
        tag_layout->addWidget(check_boxes_[i].get());

        color_combo_boxes_[i] = std::make_unique<QComboBox>(this);
        color_combo_boxes_[i]->addItem("Красный", get_color_by_code(0));
        color_combo_boxes_[i]->addItem("Синий", get_color_by_code(1));
        color_combo_boxes_[i]->addItem("Розовый", get_color_by_code(2));
        color_combo_boxes_[i]->addItem("Зеленый", get_color_by_code(3));
        color_combo_boxes_[i]->addItem("Желтый", get_color_by_code(4));
        tag_layout->addWidget(color_combo_boxes_[i].get());

        name_line_edits_[i] = std::make_unique<QLineEdit>(this);
        name_line_edits_[i]->setPlaceholderText(
            "Имя тега " + QString::number(i + 1)
        );
        tag_layout->addWidget(name_line_edits_[i].get());

        main_layout->addLayout(tag_layout);
    }

    auto *button_layout = new QHBoxLayout;

    ok_button_ = std::make_unique<QPushButton>("OK", this);
    ok_button_->setObjectName("ok_button");
    button_layout->addWidget(ok_button_.get());

    cancel_button_ = std::make_unique<QPushButton>("Отмена", this);
    cancel_button_->setObjectName("cancel_button");
    button_layout->addWidget(cancel_button_.get());

    main_layout->addLayout(button_layout);

    connect(ok_button_.get(), &QPushButton::clicked, this, &TagsDialog::accept);
    connect(
        cancel_button_.get(), &QPushButton::clicked, this, &TagsDialog::reject
    );
}

QList<TagsDialog::Tag> TagsDialog::get_selected_tags() const {
    QList<Tag> tags;
    for (int i = 0; i < MAX_TAGS_COUNT; ++i) {
        if (check_boxes_[i]->isChecked() &&
            !name_line_edits_[i]->text().isEmpty()) {
            Tag tag;
            tag.is_checked = true;
            tag.color = color_combo_boxes_[i]->currentData().toInt();
            tag.name = name_line_edits_[i]->text();
            tags.append(tag);
        }
    }
    return tags;
}

QString TagsDialog::get_color_by_code(const int code) {
    switch (code) {
        case 0: return "#e7624b";
        case 1: return "#165d7b";
        case 2: return "#bd6dab";
        case 3: return "#00b16b";
        case 4: return "#e69f00";
        default: return "ffffff";
    }
}