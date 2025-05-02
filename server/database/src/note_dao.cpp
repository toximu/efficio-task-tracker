#include "note_dao.hpp"
#include <pqxx/pqxx>
#include "database_manager.hpp"

std::string color_code_to_hex(const int code) {
    static const std::unordered_map<int, std::string> color_map = {
        {0, "#e7624b"}, {1, "#165d7b"}, {2, "#bd6dab"},
        {3, "#00b16b"}, {4, "#e69f00"},
    };

    const auto it = color_map.find(code);
    return it != color_map.end() ? it->second : "ffffff";
}

Note NoteDao::initialize_note_for_user(const std::string &login) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query =
        "INSERT INTO notes (title, content) "
        "VALUES ($1, $2) "
        "RETURNING id, title, content";

    const pqxx::result result =
        transaction.exec_params(query, "Пустая заметка", "");

    if (result.empty()) {
        return {};
    }

    const pqxx::row row = result[0];
    const auto note = new Note();
    note->set_id(row["id"].as<int>());
    note->set_title(row["title"].as<std::string>());

    transaction.commit();
    return *note;
}

bool NoteDao::update_note(const Note &note) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    std::string members_array = "{";
    for (int i = 0; i < note.members().size(); ++i) {
        if (i > 0) {
            members_array += ",";
        }
        members_array += "\"" + note.members(i) + "\"";
    }
    members_array += "}";

    std::string tags_array = "{";
    for (int i = 0; i < note.tags().size(); ++i) {
        if (i > 0) {
            tags_array += ",";
        }
        const auto &tag = note.tags(i);
        std::string color_code = color_code_to_hex(tag.color());
        tags_array += "\"{" + tag.text() + ":" + color_code + "}\"";
    }
    tags_array += "}";

    const std::string query =
        "UPDATE notes SET "
        "title = $1, "
        "content = $2, "
        "members = $3::varchar(50)[], "
        "date = $4, "
        "tags = $5::varchar(50)[] "
        "WHERE id = $6";

    const pqxx::result result = transaction.exec_params(
        query, note.title(), note.text(), members_array, note.date(),
        tags_array, note.id()
    );

    transaction.commit();
    return result.affected_rows() > 0;
}

Note NoteDao::get_note(const int note_id) {
    pqxx::connection connection(DatabaseManager::get_connection_string());
    pqxx::work transaction(connection);

    const std::string query =
        "SELECT * FROM notes WHERE id = " + transaction.quote(note_id);

    const pqxx::result result = transaction.exec(query);

    if (result.empty()) {
        return {};
    }

    const pqxx::row row = result[0];

    const auto note = new Note();

    note->set_id(row["id"].as<int>());
    note->set_title(row["title"].as<std::string>());
    note->set_text(row["content"].as<std::string>());

    if (!row["date"].is_null()) {
        note->set_date(row["date"].as<std::string>());
    }

    if (!row["members"].is_null()) {
        note->add_members(row["members"].as<std::string>());
    }

    const pqxx::result tags = transaction.exec(
        "SELECT * FROM notes WHERE id = " + transaction.quote(note->id())
    );

    // for (const auto &tag_row : tags) {
    //     auto *tag = note->add_tags();
    //     tag->set_text(tag_row["text"].as<std::string>());
    //     tag->set_color(
    //         static_cast<Note::tag::colors>(tag_row["color"].as<int>())
    //     );
    // }

    transaction.commit();
    return *note;
}
