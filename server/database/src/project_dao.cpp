#include "project_dao.hpp"
#include "note_dao.hpp"
#include "database_manager.hpp"
#include <pqxx/pqxx>


bool ProjectDAO::get_project(const std::string &code, Project &project) {
    pqxx::connection &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);


    const std::string query =
        "SELECT * FROM projects WHERE code = " + transaction.quote(code);

    const pqxx::result result = transaction.exec(query);

    if (result.empty()) {
        return false;
    }

    const pqxx::row row = result[0];

    project.set_title(row["title"].as<std::string>());
    project.set_code(row["code"].as<std::string>());


    if (!row["members"].is_null()) {
        const auto members_as_string = row["members"].as<std::string>();

        if (members_as_string.size() > 2) {
            std::stringstream ss(
                members_as_string.substr(1, members_as_string.size() - 2)
            );
            std::string member;

            while (std::getline(ss, member, ',')) {
                std::erase(member, '"');
                if (!member.empty()) {
                    project.add_members(member);
                }
            }
        }
    }

    if (!row["notes"].is_null()) {
        const auto notes_as_string = row["notes"].as<std::string>();

        if (notes_as_string.size() > 2) {
            std::stringstream ss(
                notes_as_string.substr(1, notes_as_string.size() - 2)
            );
            std::string note_id_string;

            while (std::getline(ss, note_id_string, ',')) {
                std::erase(note_id_string, '"');
                if (!note_id_string.empty()) {
                    Note* note = project.add_notes();
                    *note = NoteDao::get_note(std::stoi(note_id_string));
                }
            }
        }
    }

    return true;

}


bool ProjectDAO::insert_project(Project &project) {
    auto& connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query =
        "INSERT INTO projects (code, title, notes, members) "
        "VALUES ($1, $2, $3, $4) ";

    std::vector<int> note_ids;
    for (auto note : project.notes()) {
        note_ids.push_back(note.id());
    }

    const pqxx::result result = transaction.exec_params(
        query,
        project.code(),
        project.title(),
        note_ids,
        proto_arr_to_vector(project.members())
        );

    transaction.commit();
    return true;
}

bool ProjectDAO::add_member_to_project(
    const std::string &project_code,
    const std::string &member
) {
    auto& connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query =
        "UPDATE projects "
        "SET members = array_append(members, $1) "
        "WHERE code = $2 "
        "RETURNING 1;";


    const pqxx::result result = transaction.exec_params(query, member, project_code);
    if (result.empty()) {
        return false;
    }
    transaction.commit();
    return true;
}


bool ProjectDAO::add_note_to_project(
    const std::string &project_code,
    int note_id
) {
    auto& connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query =
        "UPDATE projects "
        "SET notes = array_append(notes, $1) "
        "WHERE code = $2 "
        "RETURNING 1;";

    const pqxx::result result = transaction.exec_params(query,note_id, project_code);
    if (result.empty()) {
        return false;
    }
    transaction.commit();
    return true;
}

bool ProjectDAO::change_project_title(
    const std::string &project_code,
    const std::string &new_title
) {
    auto& connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query =
        "UPDATE projects "
        "SET title = $1 "
        "WHERE code = $2 "
        "RETURNING 1;";

    const pqxx::result result = transaction.exec_params(query, new_title, project_code);
    if (result.empty()) {
        return false;
    }

    transaction.commit();
    return true;
}


