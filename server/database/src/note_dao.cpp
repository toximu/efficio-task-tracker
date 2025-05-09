#include "note_dao.hpp"
#include <pqxx/pqxx>
#include "database_manager.hpp"

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

    const std::string query =
        "UPDATE notes SET "
        "title = :title, "
        "content = :content, "
        "members = :members, "
        "date = :date, "
        "tags = :tags "
        "WHERE id = :id";

    // TODO: I'm not sure, it will work correctly because note.members() and
    // note.tags() return strange type const pqxx::result result =
    // transaction.exec_params(
    //     query, note.title(), note.text(), note.members(), note.date(),
    //     note.tags(), note.id()
    // );
    //
    // if (result.empty()) {
    //     return false;
    // }

    transaction.commit();
    return true;
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
