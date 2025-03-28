#ifndef NOTEDAO_HPP
#define NOTEDAO_HPP

#include <vector>
#include "note.hpp"

using namespace project_storage_model;

class NoteDao {
public:
    NoteDao() = default;
    static bool initialize_note(int &id);
    static bool update_note(const Note &note);
    bool delete_note(int id) const;
    [[nodiscard]] std::vector<Note> get_all_notes() const;
    [[nodiscard]] Note get_note_by_id(int id) const;
};

#endif  // NOTEDAO_HPP