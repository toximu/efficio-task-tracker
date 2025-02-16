#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <string>
#include <vector>
#include "note.hpp"

class Project {
public:
    Project(int id, const std::string& name, const std::string& description);
    
    int GetId() const;
    const std::string& GetName() const;
    const std::string& GetDescription() const;
    const std::vector<Note>& GetNotes() const;

    void AddNote(const Note& note);
    void RemoveNote(int noteId);
    void EditDescription(const std::string& description);

private:
    int id;
    std::string name;
    std::string description;
    std::vector<Note> notes;
};

#endif
