#ifndef NOTEDAO_HPP
#define NOTEDAO_HPP

#include "model-proto/model.pb.h"

using Efficio_proto::Note;

class NoteDao {
public:
    NoteDao() = default;
    static Note initialize_note_for_user(const std::string& login);
    static bool update_note(const Note &note);
    [[nodiscard]] static Note get_note(int note_id);
};

#endif  // NOTEDAO_HPP