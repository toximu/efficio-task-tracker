#include "tags_dialog.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "tags_dialog_styles.h"
#include "style_manager.h"
#include "language_manager.h"


const std::vector<QString> TagsDialog::THEMES = {
    Ui::tags_dialog_light_autumn_theme,
    Ui::tags_dialog_dark_autumn_theme,
    Ui::tags_dialog_dark_purple_theme,
    Ui::tags_dialog_light_purple_theme,
    Ui::tags_dialog_blue_theme
};

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
    handle_theme_changed(StyleManager::instance()->current_theme());
    connect(LanguageManager::instance(), &LanguageManager::language_changed,
            this, &TagsDialog::handle_language_changed
    );
    handle_language_changed(LanguageManager::instance()->current_language());
}


void TagsDialog::handle_language_changed(std::string new_language) {
    if (new_language == "RU") {
        setWindowTitle("Добавить теги");
        ok_button_->setText(tr("OK"));
        cancel_button_->setText(tr("Отмена"));

        const QStringList colors = {"Красный", "Синий", "Розовый", "Зеленый", "Желтый"};
        for (int i = 0; i < MAX_TAGS_COUNT; ++i) {
            if (color_combo_boxes_[i]) {
                color_combo_boxes_[i]->setItemText(0, colors[0]);
                color_combo_boxes_[i]->setItemText(1, colors[1]);
                color_combo_boxes_[i]->setItemText(2, colors[2]);
                color_combo_boxes_[i]->setItemText(3, colors[3]);
                color_combo_boxes_[i]->setItemText(4, colors[4]);
            }
            if (name_line_edits_[i]) {
                name_line_edits_[i]->setPlaceholderText("Имя тега " + QString::number(i + 1));
            }
        }
    } else if (new_language == "EN") {
        setWindowTitle("Add tags");
        ok_button_->setText(tr("OK"));
        cancel_button_->setText(tr("Cancel"));

        const QStringList colors = {"Red", "Blue", "Pink", "Green", "Yellow"};
        for (int i = 0; i < MAX_TAGS_COUNT; ++i) {
            if (color_combo_boxes_[i]) {
                color_combo_boxes_[i]->setItemText(0, colors[0]);
                color_combo_boxes_[i]->setItemText(1, colors[1]);
                color_combo_boxes_[i]->setItemText(2, colors[2]);
                color_combo_boxes_[i]->setItemText(3, colors[3]);
                color_combo_boxes_[i]->setItemText(4, colors[4]);
            }
            if (name_line_edits_[i]) {
                name_line_edits_[i]->setPlaceholderText("Tag name " + QString::number(i + 1));
            }
        }
    }
}


void TagsDialog::setup_ui() {
    auto *main_layout = new QVBoxLayout(this);

    for (int i = 0; i < MAX_TAGS_COUNT; ++i) {
        auto *tag_layout = new QHBoxLayout();

        check_boxes_[i] = std::make_unique<QCheckBox>(this);
        check_boxes_[i]->setChecked(false);
        tag_layout->addWidget(check_boxes_[i].get());

        color_combo_boxes_[i] = std::make_unique<QComboBox>(this);
        color_combo_boxes_[i]->addItem("Красный", "#e7624b");
        color_combo_boxes_[i]->addItem("Синий", "#165d7b");
        color_combo_boxes_[i]->addItem("Розовый", "#bd6dab");
        color_combo_boxes_[i]->addItem("Зеленый", "#00b16b");
        color_combo_boxes_[i]->addItem("Желтый", "#e69f00");
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
    connect(StyleManager::instance(), &StyleManager::theme_changed,
            this, &TagsDialog::handle_theme_changed);
}

void TagsDialog::handle_theme_changed(int theme) {
    this->setStyleSheet(THEMES[theme]);
}

QList<TagsDialog::Tag> TagsDialog::get_selected_tags() const {
    QList<Tag> tags;
    for (int i = 0; i < MAX_TAGS_COUNT; ++i) {
        if (check_boxes_[i]->isChecked() &&
            !name_line_edits_[i]->text().isEmpty()) {
            Tag tag;
            tag.is_checked = true;
            tag.color = color_combo_boxes_[i]->currentData().toString();
            tag.name = name_line_edits_[i]->text();
            tags.append(tag);
        }
    }
    return tags;
}