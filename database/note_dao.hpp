#ifndef NOTEDAO_HPP
#define NOTEDAO_HPP

#include <QSqlQuery>
#include <vector>
#include "note.hpp"

using namespace project_storage_model;

class NoteDao {
public:
    NoteDao() = default;
    static bool create_note(const Note &note);
    static bool update_note(const Note &note);
    static bool delete_note(int id);
    static std::vector<Note> get_all_notes();
    static Note get_note_by_id(int id);

private:
    static Note get_next_note_from_query(const QSqlQuery &query);
};

#endif  // NOTEDAO_HPP