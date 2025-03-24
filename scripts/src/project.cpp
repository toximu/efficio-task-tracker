#include "../include/project.hpp"
#include <algorithm>

namespace project_storage_model {

Project::Project(
    int id,
    const std::string &name,
    const std::string &description
)
    : id_(std::move(id)), name_(std::move(name)), description_(std::move(description)) {
}

[[nodiscard]] int Project::get_id() const {
    return id_;
}

[[nodiscard]] const std::string &Project::get_name() const {
    return name_;
}

[[nodiscard]] const std::string &Project::get_description() const {
    return description_;
}

const std::list<Note> &Project::get_notes() const {
    return notes_;
}

Note &Project::add_note(const Note &note) {
    notes_.push_back(note);
    return notes_.back();
}

void Project::remove_note(int note_id) {
    notes_.erase(
        std::remove_if(
            notes_.begin(), notes_.end(),
            [note_id](const Note &note) { return note.get_id() == note_id; }
        ),
        notes_.end()
    );
}

void Project::edit_description(const std::string &description) {
    this->description_ = description;
}

}  // namespace project_storage_model
