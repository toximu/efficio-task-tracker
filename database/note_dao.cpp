#include "note_dao.hpp"
#include <QSqlQuery>
#include "database_manager.hpp"

bool NoteDao::create_note(const Note &note) {
    QSqlQuery query;
    QVariantList params = {
        QString::fromStdString(note.get_title()),
        QString::fromStdString(note.get_text())};

    return DatabaseManager::get_instance().execute_query(
        query,
        "INSERT INTO notes (title, content) "
        "VALUES (:title, :content)",
        params
    );
}
