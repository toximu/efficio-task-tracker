#ifndef NOTEDAO_HPP
#define NOTEDAO_HPP

#include "note.hpp"

using namespace project_storage_model;

class NoteDao {
public:
    NoteDao() = default;
    static bool create_note(const Note &note);
};

#endif  // NOTEDAO_HPP