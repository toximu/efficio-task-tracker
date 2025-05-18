#include "note_edit_dialog.h"
#include <QDialog>
#include <QFile>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QDate>
#include "./ui_note_edit_dialog.h"
#include "note_edit_dialog_styles.h"
#include "tags_dialog.h"
#include "style_manager.h"


const std::vector<QString> NoteEditDialog::THEMES = {
    Ui::note_edit_dialog_light_autumn_theme,
    Ui::note_edit_dialog_dark_autumn_theme,
    Ui::note_edit_dialog_dark_purple_theme,
    Ui::note_edit_dialog_light_purple_theme,
    Ui::note_edit_dialog_blue_theme
};

NoteEditDialog::NoteEditDialog(QWidget* parent, Note* note)
    : QDialog(parent),
      ui_(new Ui::NoteEditDialog),
      note_(note)  {
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
    ui_->titleLineEdit->setText(QString::fromStdString(note_->get_title()));
    ui_->descriptionTextEdit->setText(QString::fromStdString(note_->get_text()));
}


void NoteEditDialog::on_switch_theme_button_click() {
    int next_theme = (StyleManager::instance()->current_theme() + 1) % 5;
    StyleManager::instance()->apply_theme(next_theme);
}


NoteEditDialog::~NoteEditDialog() {
    delete ui_;
}

void NoteEditDialog::init_additional_fields() {
    if (!note_->get_date().empty()) {
        QDate date = QDate::fromString(QString::fromStdString(note_->get_date()), "yyyy-MM-dd");
        if (date.isValid()) {
            ui_->dateEdit->setDate(date);
            ui_->dateLabel->setVisible(true);
            ui_->dateEdit->setVisible(true);
        }
    }

    if (!note_->get_members().empty()) {
        ui_->membersLabel->setVisible(true);
        for (const auto& member : note_->get_members()) {
            add_member_avatar(member);
        }
        ui_->joinButton->setText("Покинуть");
    }

    if (!note_->get_tags().empty()) {
        ui_->tagsLabel->setVisible(true);
        for (const auto& tag : note_->get_tags()) {
            TagsDialog::Tag tag_info;
            tag_info.is_checked = true;
            tag_info.color = QString::fromStdString(tag.color);
            tag_info.name = QString::fromStdString(tag.name);
            selected_tags_.append(tag_info);

            auto tag_label = std::make_unique<QLabel>(tag_info.name, this);
            tag_label->setStyleSheet(create_tag_style_sheet(tag_info.color));
            ui_->tagsLayout->addWidget(tag_label.get());
            tag_labels_.push_back(std::move(tag_label));
        }
    }
}

void NoteEditDialog::setup_connections() {
    connect(ui_->saveButton, &QPushButton::clicked, this, &NoteEditDialog::on_save_button_click);
    connect(ui_->cancelButton, &QPushButton::clicked, this, &NoteEditDialog::reject);
    connect(ui_->joinButton, &QPushButton::clicked, this, &NoteEditDialog::on_join_button_click);
    connect(ui_->addMembersButton, &QPushButton::clicked, this, &NoteEditDialog::on_add_members_button_click);
    connect(ui_->addDateButton, &QPushButton::clicked, this, [this]() {
        const bool is_visible = ui_->dateLabel->isVisible();
        ui_->dateLabel->setVisible(!is_visible);
        ui_->dateEdit->setVisible(!is_visible);
    });
    connect(ui_->switch_theme, &QPushButton::clicked, this,
        &NoteEditDialog::on_switch_theme_button_click
    );
    connect(StyleManager::instance(), &StyleManager::theme_changed,
            this, &NoteEditDialog::handle_theme_changed);
    connect(ui_->addTagsButton, &QPushButton::clicked, this, &NoteEditDialog::on_add_tags_button_click);
    connect(StyleManager::instance(), &StyleManager::font_size_changed,
            this, &NoteEditDialog::handle_font_size_changed
    );
}

void NoteEditDialog::handle_font_size_changed(std::string font_size_) {
    QString current_style = this->styleSheet();
   
    QString font_rules;
    if(font_size_ == "small") {
        font_rules = 
            "QLineEdit#titleLineEdit { font-size: 20px; }"
            "QLabel#projectNameLabel { font-size: 11px; }"
            "QLabel#descriptionLabel { font-size: 14px; }"
            "QLabel#sidePanelLabel, QLabel#sidePanelLabel_2 { font-size: 12px; }"
            "QMessageBox QLabel { font-size: 12px; }"
            "QMessageBox QPushButton { font-size: 11px; }";
    }
    else if(font_size_ == "big") {
        font_rules = 
            "QLineEdit#titleLineEdit { font-size: 30px; }"
            "QLabel#projectNameLabel { font-size: 16px; }"
            "QLabel#descriptionLabel { font-size: 21px; }"
            "QLabel#sidePanelLabel, QLabel#sidePanelLabel_2 { font-size: 17px; }"
            "QMessageBox QLabel { font-size: 17px; }"
            "QMessageBox QPushButton { font-size: 16px; }";
    }

    this->setStyleSheet(THEMES[StyleManager::instance()->current_theme()] + font_rules);
}

void NoteEditDialog::setup_ui() {
    setFixedSize(700, 480);
    setStyleSheet(THEMES[StyleManager::instance()->current_theme()]);
    ui_->buttonsLayout->setAlignment(Qt::AlignLeft);
}

void NoteEditDialog::on_save_button_click() {
    if (try_save_note()) {
        QMessageBox::information(this, "Заметка сохранена",
            QString("Заголовок: %1\nСодержимое: %2")
                .arg(ui_->titleLineEdit->text(), ui_->descriptionTextEdit->toPlainText()));
    } else {
        QMessageBox::information(this, "Ошибка", "Не удалось сохранить заметку");
    }
    close();
}

void NoteEditDialog::on_join_button_click() {
    const bool is_joined = ui_->membersLabel->isVisible();
    ui_->membersLabel->setVisible(!is_joined);

    if (!is_joined) {
        const std::string current_user = "TODO";
        add_member_avatar(current_user);
        note_->add_member(current_user);
        ui_->joinButton->setText("Покинуть");
    } else {
        std::string current_user = "TODO";
        clear_member_avatars();
        ui_->joinButton->setText("Присоединиться");
    }
}

void NoteEditDialog::add_member_avatar(const std::string& member) {
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
    for (auto& avatar : member_avatars_) {
        ui_->avatarsLayout->removeWidget(avatar.get());
    }
    member_avatars_.clear();
}

void NoteEditDialog::on_add_members_button_click() {
    QMessageBox::information(this, "Ошибка", "Другие участники не найдены :(");
}

void NoteEditDialog::on_add_tags_button_click() {
    TagsDialog tags_dialog(selected_tags_, this);
    if (tags_dialog.exec() == Accepted) {
        selected_tags_ = tags_dialog.get_selected_tags();
        update_tags_display();
    }
}

void NoteEditDialog::update_tags_display() {
    for (auto& tag_label : tag_labels_) {
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

QString NoteEditDialog::create_tag_style_sheet(const QString& color) {
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
    ).arg(color);
}

bool NoteEditDialog::try_save_note() const {
    note_->set_title(ui_->titleLineEdit->text().toStdString());
    note_->set_text(ui_->descriptionTextEdit->toPlainText().toStdString());
    note_->set_date(ui_->dateEdit->date().toString("yyyy-MM-dd").toStdString());

    note_->clear_tags();
    for (const auto &[is_checked, color, name] : selected_tags_) {
        if (is_checked) {
            note_->add_tag(name.toStdString(), color.toStdString());
        }
    }

    return NoteDao::update_note(*note_);
}