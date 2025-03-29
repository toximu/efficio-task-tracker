#include "note_dao.hpp"
#include <iostream>
#include <ostream>
#include "database_manager.hpp"

bool NoteDao::initialize_note(int &id) {
    QSqlQuery query;
    const auto is_successful = DatabaseManager::get_instance().execute_query(
        query,
        "INSERT INTO notes (title, content) "
        "VALUES ('Пустая заметка', '')"
        "RETURNING id"
    );
    if (is_successful && query.next()) {
        id = query.value(0).toInt();
        return true;
    }
    return false;
}

bool NoteDao::update_note(const Note &note) {
    QSqlQuery query;
    const QString sql_query =
        "UPDATE notes SET "
        "title = :title, "
        "content = :content "
        "WHERE id = :id";
    const QVariantList params = {
        QString::fromStdString(note.get_title()),
        QString::fromStdString(note.get_text()), note.get_id()};

    return DatabaseManager::get_instance().execute_query(
        query, sql_query, params
    );
}

bool NoteDao::delete_note(int id) const {
    QSqlQuery query;
    const QString sql_query = "DELETE FROM notes WHERE id = :id";
    return DatabaseManager::get_instance().execute_query(
        query, sql_query, {id}
    );
}

std::vector<Note> NoteDao::get_all_notes() {
    QSqlQuery query;
    std::vector<Note> notes;
    DatabaseManager::get_instance().execute_query(query, "SELECT * FROM notes");

    while (query.next()) {
        auto id = query.value("id").toUInt();
        auto title = query.value("title").toString().toStdString();
        auto text = query.value("content").toString().toStdString();
        notes.emplace_back(id, title, text);
    }

    return notes;
}

Note NoteDao::get_note_by_id(int id) {
    QSqlQuery query;
    DatabaseManager::get_instance().execute_query(
        query, "SELECT * FROM notes WHERE id = ?", {id}
    );
    query.next();
    auto title = query.value("title").toString().toStdString();
    auto text = query.value("content").toString().toStdString();
    // std::cout << title << ", " << text << std::endl;
    return {id, title, text};
}
