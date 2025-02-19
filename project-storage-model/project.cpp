#include "project.hpp"

namespace project_storage_model {

Project::Project(int id, const std::string &name,
                 const std::string &description)
    : id_(id), name_(name), description_(description) {}

int Project::get_id() const { return id_; }

const std::string &Project::get_name() const { return name_; }

const std::string &Project::get_description() const { return description_; }

const std::vector<Note> &Project::get_notes() const { return notes_; }

void Project::add_note(const Note &note) { notes_.push_back(note); }

void Project::remove_note(int note_id) {
  notes_.erase(std::remove_if(notes_.begin(), notes_.end(),
                              [note_id](const Note &note) {
                                return note.get_id() == note_id;
                              }),
               notes_.end());
}

void Project::edit_description(const std::string &description) {
  this->description_ = description;
}

} // namespace project_storage_model
