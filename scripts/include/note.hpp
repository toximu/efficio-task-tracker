#ifndef NOTE_HPP
#define NOTE_HPP

#include <string>
#include <unordered_set>
#include <vector>

namespace project_storage_model {

class Note {
public:
    struct Tag {
        std::string name;
        std::string color;
    };

    Note(int id, std::string title, std::string text);

    [[nodiscard]] int get_id() const;
    [[nodiscard]] const std::string &get_title() const;
    [[nodiscard]] const std::string &get_text() const;
    [[nodiscard]] const std::string &get_date() const;
    [[nodiscard]] const std::vector<Tag> &get_tags() const;
    [[nodiscard]] const std::unordered_set<std::string> &get_members() const;

    void set_title(const std::string &title);
    void set_text(const std::string &text);
    void add_tag(const std::string &tag, const std::string &color = "#e7624b");
    void set_date(const std::string &date);
    void add_member(const std::string &member);
    void remove_tag(const std::string &tag);
    void clear_tags();
    void clear_members();

private:
    int id_;
    std::string title_;
    std::string text_;
    std::string date_;
    std::vector<Tag> tags_;
    std::unordered_set<std::string> members_;
};

}  // namespace project_storage_model

#endif