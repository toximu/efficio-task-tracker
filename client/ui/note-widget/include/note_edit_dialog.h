#ifndef NOTE_EDIT_DIALOG_H
#define NOTE_EDIT_DIALOG_H

#include <QLabel>
#include <memory>
#include <vector>
#include "client_implementation.h"
#include "model-proto/model.pb.h"
#include "tags_dialog.h"

using Efficio_proto::Note;

QT_BEGIN_NAMESPACE

namespace Ui {
class NoteEditDialog;
}

QT_END_NAMESPACE

class NoteEditDialog final : public QDialog {
    Q_OBJECT

public:
    static const std::vector<QString> THEMES;

    explicit NoteEditDialog(
        ClientImplementation *client,
        std::string project_name = "TODO",
        QWidget *parent = nullptr,
        Note *note = nullptr
    );
    ~NoteEditDialog() override;

    static QString create_tag_style_sheet(int color_code);
    void handle_theme_changed(int theme);
    void handle_font_size_changed(std::string font_size);
    void handle_language_changed(std::string new_language);

private slots:
    void on_save_button_click();
    void on_join_button_click();
    void on_add_members_button_click();
    void on_add_tags_button_click();

private:
    void init_basic_fields();
    void init_additional_fields();
    void setup_connections();
    void setup_ui();

    void add_member_avatar(const std::string &member);

    void clear_member_avatars();
    void update_tags_display();

    [[nodiscard]] bool try_save_note() const;

    Ui::NoteEditDialog *ui_{};
    std::vector<std::unique_ptr<QLabel>> member_avatars_;
    std::vector<std::unique_ptr<QLabel>> tag_labels_;
    QList<TagsDialog::Tag> selected_tags_;
    Note *note_;
    std::string project_name_;
    ClientImplementation *client_;
};

#endif  // NOTE_EDIT_DIALOG_H