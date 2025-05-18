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
#include <grpcpp/grpcpp.h>
#include "efficio-rpc-proto/efficio.grpc.pb.h"
#include "update_requests.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using Efficio_proto::Update;
using Efficio_proto::GetNoteRequest;
using Efficio_proto::GetNoteResponse;

NoteEditDialog::NoteEditDialog(QWidget* parent, Note* note)
    : QDialog(parent),
      ui_(new Ui::NoteEditDialog),
      note_(note) {
    if (note_ == nullptr) {
        std::cerr << "Not a valid note!\n";
    }
    ui_->setupUi(this);
    setWindowTitle("EFFICIO");

    init_basic_fields();
    init_additional_fields();
    setup_connections();
    setup_ui();
}

NoteEditDialog::~NoteEditDialog() {
    delete ui_;
}

void NoteEditDialog::init_basic_fields() {
    ui_->titleLineEdit->setText(QString::fromStdString(note_->title()));
    ui_->descriptionTextEdit->setText(QString::fromStdString(note_->text()));
}

void NoteEditDialog::init_additional_fields() {
    if (!note_->date().empty()) {
        QDate date = QDate::fromString(QString::fromStdString(note_->date()), "yyyy-MM-dd");
        if (date.isValid()) {
            ui_->dateEdit->setDate(date);
            ui_->dateLabel->setVisible(true);
            ui_->dateEdit->setVisible(true);
        }
    }

    if (!note_->members().empty()) {
        ui_->membersLabel->setVisible(true);
        for (const auto& member : note_->members()) {
            add_member_avatar(member);
        }
        ui_->joinButton->setText("Покинуть");
    }

    if (!note_->tags().empty()) {
        ui_->tagsLabel->setVisible(true);
        for (const auto& tag : note_->tags()) {
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
    connect(ui_->saveButton, &QPushButton::clicked, this, &NoteEditDialog::on_save_button_click);
    connect(ui_->cancelButton, &QPushButton::clicked, this, &NoteEditDialog::reject);
    connect(ui_->joinButton, &QPushButton::clicked, this, &NoteEditDialog::on_join_button_click);
    connect(ui_->addMembersButton, &QPushButton::clicked, this, &NoteEditDialog::on_add_members_button_click);
    connect(ui_->addDateButton, &QPushButton::clicked, this, [this]() {
        const bool is_visible = ui_->dateLabel->isVisible();
        ui_->dateLabel->setVisible(!is_visible);
        ui_->dateEdit->setVisible(!is_visible);
    });
    connect(ui_->addTagsButton, &QPushButton::clicked, this, &NoteEditDialog::on_add_tags_button_click);
}

void NoteEditDialog::setup_ui() {
    setFixedSize(700, 480);
    setStyleSheet(Ui::light_theme);
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
    for (const auto &[is_checked, color_code, name] : selected_tags_) {
        if (is_checked) {
            auto tag_label = std::make_unique<QLabel>(name, this);
            tag_label->setStyleSheet(create_tag_style_sheet(color_code));
            ui_->tagsLayout->addWidget(tag_label.get());
            tag_labels_.push_back(std::move(tag_label));
        }
    }
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
    ).arg(TagsDialog::get_color_by_code(color_code));
}

bool NoteEditDialog::try_save_note() const {
    // TODO: add saving members and tags
    note_->set_title(ui_->titleLineEdit->text().toStdString());
    note_->set_text(ui_->descriptionTextEdit->toPlainText().toStdString());
    note_->set_date(ui_->dateEdit->date().toString("yyyy-MM-dd").toStdString());

    return true;
}