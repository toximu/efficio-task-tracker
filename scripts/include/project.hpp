#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <list>
#include <string>
#include "note.hpp"

namespace project_storage_model {

class Project {
public:
    Project(int id, const std::string &name, const std::string &description);

    [[nodiscard]] int get_id() const;
    [[nodiscard]] const std::string &get_name() const;
    [[nodiscard]] const std::string &get_description() const;
    const std::list<Note> &get_notes() const;

    Note &add_note(const Note &note);
    void remove_note(int note_id);
    void edit_description(const std::string &description);

private:
    int id_;
    std::string name_;
    std::string description_;
    std::list<Note> notes_;
};

}  // namespace project_storage_model

#endif