#include "note.hpp"

Note::Note(int id, const std::string& title, const std::string& text)
    : id(id), title(title), text(text) {}

int Note::GetId() const {
    return id;
}

const std::string& Note::GetTitle() const {
    return title;
}

const std::string& Note::GetText() const {
    return text;
}

const std::vector<std::string>& Note::GetTags() const {
    return tags;
}

void Note::SetTitle(const std::string& title) {
    this->title = title;
}

void Note::SetText(const std::string& text) {
    this->text = text;
}

void Note::AddTag(const std::string& tag) {
    tags.push_back(tag);
}

void Note::RemoveTag(const std::string& tag) {
    tags.erase(std::remove(tags.begin(), tags.end(), tag), tags.end());
}
