#include "note_dao.hpp"
#include <QDateTime>
#include "database_manager.hpp"

bool NoteDao::create_note(const Note &note) {
    const QSqlQuery query = DatabaseManager::get_instance().execute_query(
        "INSERT INTO notes (title, content, created_at, updated_at) "
        "VALUES (:title, :content, :created, :updated)",
        {QString::fromStdString(note.get_title()),
         QString::fromStdString(note.get_text()), QDateTime::currentDateTime(),
         QDateTime::currentDateTime()}
    );

    return query.lastError().type() == QSqlError::NoError;
}

bool NoteDao::update_note(const Note &note) {
    const QSqlQuery query = DatabaseManager::get_instance().execute_query(
        "UPDATE notes SET "
        "title = :title, "
        "content = :content, "
        "updated_at = :updated "
        "WHERE id = :id",
        {QString::fromStdString(note.get_title()),
         QString::fromStdString(note.get_text()), QDateTime::currentDateTime(),
         note.get_id()}
    );

    return query.lastError().type() == QSqlError::NoError;
}

bool NoteDao::delete_note(const int id) {
    const QSqlQuery query = DatabaseManager::get_instance().execute_query(
        "DELETE FROM notes WHERE id = :id", {id}
    );

    return query.lastError().type() == QSqlError::NoError;
}

std::vector<Note> NoteDao::get_all_notes() {
    std::vector<Note> notes;
    QSqlQuery query =
        DatabaseManager::get_instance().execute_query("SELECT * FROM notes");

    while (query.next()) {
        notes.emplace_back(get_next_note_from_query(query));
    }

    return notes;
}

Note NoteDao::get_note_by_id(const int id) {
    QSqlQuery query = DatabaseManager::get_instance().execute_query(
        "SELECT * FROM notes WHERE id = :id", {id}
    );

    return query.next() ? get_next_note_from_query(query) : Note();
}

Note NoteDao::get_next_note_from_query(const QSqlQuery &query) {
    const int id = query.value("id").toInt();
    const std::string title = query.value("title").toString().toStdString();
    const std::string text = query.value("content").toString().toStdString();
    return {id, title, text};
}
