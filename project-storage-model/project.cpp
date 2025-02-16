#include "project.hpp"

Project::Project(int id, const std::string& name, const std::string& description)
    : id(id), name(name), description(description) {}

int Project::GetId() const {
    return id;
}

const std::string& Project::GetName() const {
    return name;
}

const std::string& Project::GetDescription() const {
    return description;
}

const std::vector<Note>& Project::GetNotes() const {
    return notes;
}

void Project::AddNote(const Note& note) {
    notes.push_back(note);
}

void Project::RemoveNote(int noteId) {
    notes.erase(std::remove_if(notes.begin(), notes.end(), [noteId](const Note& note) {
        return note.GetId() == noteId;
    }), notes.end());
}

void Project::EditDescription(const std::string& description) {
    this->description = description;
}
