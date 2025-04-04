#include "project_dao.hpp"
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <iostream>
#include <ostream>
#include "database_manager.hpp"

namespace DB {

bool ProjectDAO::create_project(const std::string &name, int &id) {
    // todo thread-safety
    QSqlQuery query;
    QString query_str =
        "INSERT INTO projects (name)"
        " VALUES (:name)"
        "RETURNING id";

    const QVariantList params = {QString::fromStdString(name)};

    bool is_successful =
        DatabaseManager::get_instance().execute_query(query, query_str, params);
    if (is_successful && query.next()) {
        id = query.value(0).toInt();
        return true;
    }
    return false;
}

bool ProjectDAO::get_project(
    int id,
    std::string &name,
    std::vector<int> &notes
) {
    QSqlQuery query;
    QString query_str =
        "SELECT name, array_to_string(notes, ',') FROM projects "
        "WHERE id = ?";
    const QVariantList params = {id};
    bool is_successful =
        DatabaseManager::get_instance().execute_query(query, query_str, params);

    if (is_successful && query.next()) {
        name = query.value("name").toString().toStdString();

        for (auto i : query.value(1).toString().split(",")) {
            notes.push_back(i.toInt());
        }
        return true;
    }
    return false;
}

bool ProjectDAO::add_note_to_project(int project_id, int note_id) {
    QSqlQuery query;
    QString query_str =
        "UPDATE projects "
        "SET notes = array_append(notes, ?)"
        "WHERE id = ?";
    QVariantList params = {note_id, project_id};
    return DatabaseManager::get_instance().execute_query(
        query, query_str, params
    );
}

}  // namespace DB