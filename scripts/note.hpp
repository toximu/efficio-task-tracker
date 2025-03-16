#ifndef NOTE_HPP
#define NOTE_HPP

#include <list>
#include <string>

namespace project_storage_model {

class Note {
public:
    Note() = default;
    Note(int id, std::string title, std::string text);

    [[nodiscard]] int get_id() const;
    [[nodiscard]] const std::string &get_title() const;
    [[nodiscard]] const std::string &get_text() const;
    [[nodiscard]] const std::list<std::string> &get_tags() const;

    void set_title(const std::string &title);
    void set_text(const std::string &text);
    void add_tag(const std::string &tag);
    void remove_tag(const std::string &tag);

private:
    int id_;
    std::string title_;
    std::string text_;
    std::list<std::string> tags_;
};

}  // namespace project_storage_model

#endif
