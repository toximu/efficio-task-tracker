#ifndef NOTEDAO_HPP
#define NOTEDAO_HPP

#include <QString>
#include <vector>
#include "note.hpp"

using namespace project_storage_model;

class NoteDao {
public:
    NoteDao() = default;
    static bool initialize_note(int &id);
    static bool update_note(const Note &note);
    static bool delete_note(int id);
    [[nodiscard]] static std::vector<Note> get_all_notes();
    [[nodiscard]] static Note get_note_by_id(int id);

private:
    static QString convert_string_set_to_postgres_array(const std::unordered_set<std::string>& string_set);
    static QString convert_tags_to_postgres_array(const std::vector<Note::Tag>& tags);
};

#endif  // NOTEDAO_HPP