#include "../include/note.hpp"
#include <algorithm>

namespace project_storage_model {

Note::Note(int id, const std::string &title, const std::string &text)
    : id_(std::move(id)), title_(std::move(title)), text_(std::move(text)) {
}

[[nodiscard]] int Note::get_id() const {
    return id_;
}

[[nodiscard]] const std::string &Note::get_title() const {
    return title_;
}

[[nodiscard]] const std::string &Note::get_text() const {
    return text_;
}

const std::list<std::string> &Note::get_tags() const {
    return tags_;
}

void Note::set_title(const std::string &title) {
    this->title_ = title;
}

void Note::set_text(const std::string &text) {
    this->text_ = text;
}

void Note::add_tag(const std::string &tag) {
    tags_.push_back(tag);
}

void Note::remove_tag(const std::string &tag) {
    tags_.erase(std::remove(tags_.begin(), tags_.end(), tag), tags_.end());
}

}  // namespace project_storage_model
