#include "note_edit_dialog.h"
#include <QDate>
#include <QDialog>
#include <QFile>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <utility>
#include "./ui_note_edit_dialog.h"
#include "language_manager.h"
#include "note_edit_dialog_styles.h"
#include "style_manager.h"
#include "tags_dialog.h"

const std::vector<QString> NoteEditDialog::THEMES = {
    Ui::note_edit_dialog_light_autumn_theme,
    Ui::note_edit_dialog_dark_autumn_theme,
    Ui::note_edit_dialog_dark_purple_theme,
    Ui::note_edit_dialog_light_purple_theme, Ui::note_edit_dialog_blue_theme
};

NoteEditDialog::NoteEditDialog(
    ClientImplementation *client,
    std::string project_name,
    QWidget *parent,
    Note *note
)
    : client_(client),
      QDialog(parent),
      ui_(new Ui::NoteEditDialog),
      note_(note),
      project_name_(std::move(project_name)) {
    ui_->setupUi(this);
    setWindowTitle("EFFICIO");

    init_basic_fields();
    init_additional_fields();
    setup_connections();
    setup_ui();

    handle_theme_changed(StyleManager::instance()->current_theme());
    handle_font_size_changed(StyleManager::instance()->current_font_size());
}

void NoteEditDialog::handle_theme_changed(int theme) {
    this->setStyleSheet(THEMES[theme]);
}

void NoteEditDialog::init_basic_fields() {
    ui_->titleLineEdit->setMaxLength(50);
    ui_->titleLineEdit->setText(QString::fromStdString(note_->title()));
    ui_->descriptionTextEdit->setText(QString::fromStdString(note_->text()));
    ui_->projectNameLabel->setTextFormat(Qt::RichText);
}

NoteEditDialog::~NoteEditDialog() {
    delete ui_;
}

QString NoteEditDialog::create_tag_style_sheet(const int color_code) {
    return QString(
               "background-color: %1; "
               "color: white; "
               "padding: 9px 10px; "
               "border-radius: 5px; "
               "font-family: 'Arial'; "
               "font-size: 12px; "
               "font-weight: bold;"
               "width: 40px;"
               "height: 25px;"
    )
        .arg(TagsDialog::get_color_by_code(color_code));
}

void NoteEditDialog::init_additional_fields() {
    if (!note_->date().empty()) {
        QDate date = QDate::fromString(
            QString::fromStdString(note_->date()), "yyyy-MM-dd"
        );
        if (date.isValid()) {
            ui_->dateEdit->setDate(date);
            ui_->dateLabel->setVisible(true);
            ui_->dateEdit->setVisible(true);
        }
    }

    if (!note_->members().empty()) {
        ui_->membersLabel->setVisible(true);
        for (const auto &member : note_->members()) {
            add_member_avatar(member);
        }
        ui_->joinButton->setText("Покинуть");
    }

    if (!note_->tags().empty()) {
        ui_->tagsLabel->setVisible(true);
        for (const auto &tag : note_->tags()) {
            TagsDialog::Tag tag_info;
            tag_info.is_checked = true;
            tag_info.color = tag.color();
            tag_info.name = QString::fromStdString(tag.text());
            selected_tags_.append(tag_info);

            auto tag_label = std::make_unique<QLabel>(tag_info.name, this);
            tag_label->setStyleSheet(create_tag_style_sheet(tag_info.color));
            ui_->tagsLayout->addWidget(tag_label.get());
            tag_labels_.push_back(std::move(tag_label));
        }
    }
}

void NoteEditDialog::setup_connections() {
    connect(
        ui_->saveButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_save_button_click
    );
    connect(
        ui_->cancelButton, &QPushButton::clicked, this, &NoteEditDialog::reject
    );
    connect(
        ui_->joinButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_join_button_click
    );
    connect(
        ui_->addMembersButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_add_members_button_click
    );
    connect(ui_->addDateButton, &QPushButton::clicked, this, [this]() {
        const bool is_visible = ui_->dateLabel->isVisible();
        ui_->dateLabel->setVisible(!is_visible);
        ui_->dateEdit->setVisible(!is_visible);
    });
    connect(
        StyleManager::instance(), &StyleManager::theme_changed, this,
        &NoteEditDialog::handle_theme_changed
    );
    connect(
        ui_->addTagsButton, &QPushButton::clicked, this,
        &NoteEditDialog::on_add_tags_button_click
    );
    connect(
        StyleManager::instance(), &StyleManager::font_size_changed, this,
        &NoteEditDialog::handle_font_size_changed
    );
    connect(
        LanguageManager::instance(), &LanguageManager::language_changed, this,
        &NoteEditDialog::handle_language_changed
    );
    handle_language_changed(LanguageManager::instance()->current_language());
}

void NoteEditDialog::handle_language_changed(std::string new_language) {
    if (new_language == "RU") {
        setWindowTitle("EFFICIO");
        ui_->saveButton->setText("Сохранить");
        ui_->dateLabel->setText("Срок");
        ui_->cancelButton->setText("Отмена");
        ui_->joinButton->setText(
            ui_->membersLabel->isVisible() ? "Покинуть" : "Присоединиться"
        );
        ui_->addMembersButton->setText("Участники");
        ui_->addDateButton->setText("Дата");
        ui_->addTagsButton->setText("Теги");
        ui_->projectNameLabel->setText(
            QString("в проекте: <u>%1</u>")
                .arg(QString::fromStdString(project_name_))
        );
        ui_->descriptionLabel->setText("Описание:");
        if (note_->title() == "" or note_->title() == "Empty note") {
            ui_->titleLineEdit->setText("Пустая заметка");
        }
        if (note_->text() == "" or
            note_->text() == "Add a detailed description of your note") {
            ui_->descriptionTextEdit->setPlaceholderText(
                "Добавьте подробное описание вашей заметки"
            );
        }
        ui_->sidePanelLabel->setText("Добавить к заметке");
        ui_->sidePanelLabel_2->setText("Предложения");
    } else if (new_language == "EN") {
        setWindowTitle("EFFICIO");
        ui_->saveButton->setText("Save");
        ui_->dateLabel->setText("Deadline");
        ui_->cancelButton->setText("Cancel");
        ui_->joinButton->setText(
            ui_->membersLabel->isVisible() ? "Leave" : "Join"
        );
        ui_->addMembersButton->setText("Members");
        ui_->addDateButton->setText("Date");
        ui_->addTagsButton->setText("Tags");
        ui_->projectNameLabel->setText(
            QString("in project: <u>%1</u>")
                .arg(QString::fromStdString(project_name_))
        );
        ui_->descriptionLabel->setText("Description:");
        if (note_->title() == "" || note_->title() == "Пустая заметка") {
            ui_->titleLineEdit->setText("Empty note");
        }

        if (note_->text() == "" ||
            note_->text() == "Добавьте подробное описание вашей заметки") {
            ui_->descriptionTextEdit->setPlaceholderText(
                "Add a detailed description of your note"
            );
        }
        ui_->sidePanelLabel->setText("Add to note");
        ui_->sidePanelLabel_2->setText("Suggestions");
    }
}

void NoteEditDialog::handle_font_size_changed(std::string font_size_) {
    QString current_style = this->styleSheet();

    QString font_rules;
    if (font_size_ == "small") {
        font_rules =
            "QLineEdit#titleLineEdit { font-size: 20px; }"
            "QLabel#projectNameLabel { font-size: 11px; }"
            "QLabel#descriptionLabel { font-size: 14px; }"
            "QLabel#sidePanelLabel, QLabel#sidePanelLabel_2 { font-size: 12px; "
            "}"
            "QMessageBox QLabel { font-size: 12px; }"
            "QMessageBox QPushButton { font-size: 11px; }";
    } else if (font_size_ == "big") {
        font_rules =
            "QLineEdit#titleLineEdit { font-size: 30px; }"
            "QLabel#projectNameLabel { font-size: 16px; }"
            "QLabel#descriptionLabel { font-size: 21px; }"
            "QLabel#sidePanelLabel, QLabel#sidePanelLabel_2 { font-size: 17px; "
            "}"
            "QMessageBox QLabel { font-size: 17px; }"
            "QMessageBox QPushButton { font-size: 16px; }";
    }

    this->setStyleSheet(
        THEMES[StyleManager::instance()->current_theme()] + font_rules
    );
}

void NoteEditDialog::setup_ui() {
    setFixedSize(700, 480);
    setStyleSheet(THEMES[StyleManager::instance()->current_theme()]);
    ui_->buttonsLayout->setAlignment(Qt::AlignLeft);
}

void NoteEditDialog::on_save_button_click() {
    if (!try_save_note()) {
        if (LanguageManager::instance()->current_language() == "RU") {
            QMessageBox::information(
                this, "Ошибка", "Не удалось сохранить заметку"
            );
        } else {
            QMessageBox::information(this, "Error", "Failed to save the note");
        }
    }
    close();
}

void NoteEditDialog::on_join_button_click() {
    const bool is_joined = ui_->membersLabel->isVisible();
    ui_->membersLabel->setVisible(!is_joined);

    if (!is_joined) {
        const std::string current_user = "TODO";
        add_member_avatar(current_user);
        note_->add_members(current_user);
        ui_->joinButton->setText("Покинуть");
    } else {
        std::string current_user = "TODO";
        clear_member_avatars();
        ui_->joinButton->setText("Присоединиться");
    }
}

void NoteEditDialog::add_member_avatar(const std::string &member) {
    QPixmap pixmap(32, 32);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(0, 0, 32, 32);

    auto member_label = std::make_unique<QLabel>(this);
    member_label->setPixmap(pixmap);
    member_label->setFixedSize(32, 32);
    ui_->avatarsLayout->addWidget(member_label.get());
    member_avatars_.push_back(std::move(member_label));
}

void NoteEditDialog::clear_member_avatars() {
    for (auto &avatar : member_avatars_) {
        ui_->avatarsLayout->removeWidget(avatar.get());
    }
    member_avatars_.clear();
}

void NoteEditDialog::on_add_members_button_click() {
    if (LanguageManager::instance()->current_language() == "RU") {
        QMessageBox::information(
            this, "Ошибка", "Другие участники не найдены."
        );
    } else {
        QMessageBox::information(
            this, "Error", "No other participants were found."
        );
    }
}

void NoteEditDialog::on_add_tags_button_click() {
    TagsDialog tags_dialog(selected_tags_, this);
    if (tags_dialog.exec() == Accepted) {
        selected_tags_ = tags_dialog.get_selected_tags();
        update_tags_display();
    }
}

void NoteEditDialog::update_tags_display() {
    for (auto &tag_label : tag_labels_) {
        ui_->tagsLayout->removeWidget(tag_label.get());
    }
    tag_labels_.clear();

    ui_->tagsLabel->setVisible(!selected_tags_.empty());
    for (const auto &[is_checked, color, name] : selected_tags_) {
        if (is_checked) {
            auto tag_label = std::make_unique<QLabel>(name, this);
            tag_label->setStyleSheet(create_tag_style_sheet(color));
            ui_->tagsLayout->addWidget(tag_label.get());
            tag_labels_.push_back(std::move(tag_label));
        }
    }
}

Efficio_proto::Note_tag_colors color_code_to_note_tag_colors(
    const int color_code
) {
    switch (color_code) {
        case 0:
            return Efficio_proto::Note_tag_colors_Red;
        case 1:
            return Efficio_proto::Note_tag_colors_Blue;
        case 2:
            return Efficio_proto::Note_tag_colors_Pink;
        case 3:
            return Efficio_proto::Note_tag_colors_Green;
        case 4:
            return Efficio_proto::Note_tag_colors_Yellow;
    }
}

bool NoteEditDialog::try_save_note() const {
    note_->set_title(ui_->titleLineEdit->text().toStdString());
    note_->set_text(ui_->descriptionTextEdit->toPlainText().toStdString());
    note_->set_date(ui_->dateEdit->date().toString("yyyy-MM-dd").toStdString());

    note_->clear_members();
    if (!member_avatars_.empty()) {
        note_->add_members("TODO");
    }

    note_->clear_tags();
    for (const auto &tag : selected_tags_) {
        auto *new_tag = note_->add_tags();
        new_tag->set_text(tag.name.toStdString());
        new_tag->set_color(color_code_to_note_tag_colors(tag.color));
    }

    return client_->try_update_note(note_);
}