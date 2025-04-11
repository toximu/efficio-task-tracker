#include "note_dao.hpp"
#include <iostream>
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
        "content = :content, "
        "members = :members, "
        "date = :date, "
        "tags = :tags "
        "WHERE id = :id";
    const QVariantList params = {
        QString::fromStdString(note.get_title()),
        QString::fromStdString(note.get_text()),
        convert_string_set_to_postgres_array(note.get_members()),
        QString::fromStdString(note.get_date()),
        convert_tags_to_postgres_array(note.get_tags()),
        note.get_id()
    };

    return DatabaseManager::get_instance().execute_query(
        query, sql_query, params
    );
}

bool NoteDao::delete_note(int id) {
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
        query, "SELECT title, content, array_to_string(tags, ','), date, array_to_string(members, ',') FROM notes WHERE id = ?", {id}
    );
    query.next();
    auto title = query.value(0).toString().toStdString();
    auto text = query.value(1).toString().toStdString();
    auto date = query.value(3).toString().toStdString();
    Note result{id, title, text};
    auto tags_list = query.value(2).toString().split(",");

    if (!tags_list.empty() && tags_list[0] != "") {
        for (const auto& tag_str : tags_list) {

            result.add_tag(tag_str.split(':')[0].toStdString(), tag_str.split(':')[1].toStdString());
        }
    }
    auto member_list = query.value(4).toString().split(",");
    if (!member_list.empty() && member_list[0] != "") {
        for (const auto& member : member_list) {
            result.add_member(member.toStdString());
        }
    }

    return result;
}

QString NoteDao::convert_string_set_to_postgres_array(const std::unordered_set<std::string>& string_set) {
    if (string_set.empty()) {
        return "{}";
    }

    QStringList buffer;
    for (const auto& item : string_set) {
        buffer << QString::fromStdString(item).replace(",", "\\,");
    }
    return "{" + buffer.join(",") + "}";
}

QString NoteDao::convert_tags_to_postgres_array(const std::vector<Note::Tag>& tags) {
    if (tags.empty()) {
        return "{}";
    }

    QStringList buffer;
    for (const auto &[name, color] : tags) {
        buffer << QString("\"%1:%2\"")
                      .arg(QString::fromStdString(name).replace("\"", "\\\""),
                          QString::fromStdString(color).replace("\"", "\\\""));
    }
    return "{" + buffer.join(",") + "}";
}
