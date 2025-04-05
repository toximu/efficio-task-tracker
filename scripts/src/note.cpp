#include "note.hpp"
#include <algorithm>
#include <utility>

namespace project_storage_model {

Note::Note(const int id, std::string title, std::string text)
    : id_(id), title_(std::move(title)), text_(std::move(text)) {
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

const std::string &Note::get_date() const {
    return date_;
}

const std::vector<Note::Tag> &Note::get_tags() const {
    return tags_;
}

const std::unordered_set<std::string> &Note::get_members() const {
    return members_;
}

void Note::set_title(const std::string &title) {
    title_ = title;
}

void Note::set_text(const std::string &text) {
    text_ = text;
}

void Note::add_tag(const std::string &tag, const std::string &color) {
    tags_.push_back({tag, color});
}

void Note::set_date(const std::string &date) {
    date_ = date;
}

void Note::add_member(const std::string &member) {
    members_.insert(member);
}

void Note::remove_tag(const std::string &tag) {
    tags_.erase(std::remove_if(tags_.begin(), tags_.end(),
        [&tag](const Tag& t) { return t.name == tag; }), tags_.end());
}

void Note::clear_tags() {
    tags_.clear();
}

void Note::clear_members() {
    members_.clear();
}

}  // namespace project_storage_model