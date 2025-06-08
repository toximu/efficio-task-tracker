#include "project_dao.hpp"
#include <pqxx/pqxx>
#include "database_manager.hpp"
#include "note_dao.hpp"

bool ProjectDAO::get_all_user_projects(
    const std::string &login,
    Storage &storage
) {
    pqxx::connection &connection =
        DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string projects_query =
        "SELECT p.code, p.title, p.members "
        "FROM projects p "
        "JOIN users u ON p.code::text = ANY(u.projects::text[]) "
        "WHERE u.login = " +
        transaction.quote(login);

    const pqxx::result projects_result = transaction.exec(projects_query);

    if (projects_result.empty()) {
        transaction.commit();
        return false;
    }

    for (const auto &project_row : projects_result) {
        Project project;
        project.set_code(project_row["code"].as<std::string>());
        project.set_title(project_row["title"].as<std::string>());

        // if (!project_row["members"].is_null()) {
        //     auto members_str = project_row["members"].as<std::string>();
        //
        //     if (!members_str.empty() && members_str.front() == '{' &&
        //         members_str.back() == '}') {
        //         members_str = members_str.substr(1, members_str.size() - 2);
        //         std::istringstream iss(members_str);
        //         std::string member;
        //         while (std::getline(iss, member, ',')) {
        //             if (member.size() >= 2 && member.front() == '"' &&
        //                 member.back() == '"') {
        //                 member = member.substr(1, member.size() - 2);
        //             }
        //
        //             std::erase_if(member, ::isspace);
        //             if (!member.empty()) {
        //                 project.add_members(member);
        //             }
        //         }
        //     }
        // }

        storage.mutable_projects()->Add(std::move(project));
    }

    transaction.commit();
    return true;
}

bool ProjectDAO::get_project(const std::string &code, Project &project) {
    pqxx::connection &connection =
        DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query = "SELECT * FROM projects WHERE code = $1";

    const pqxx::result result = transaction.exec_params(query, code);

    if (result.empty()) {
        transaction.commit();
        return false;
    }
    transaction.commit();
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
                    Note *note = project.add_notes();
                    *note = NoteDao::get_note(std::stoi(note_id_string));
                }
            }
        }
    }

    return true;
}

bool ProjectDAO::insert_project(Project &project) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query =
        "INSERT INTO projects (code, title, notes, members) "
        "VALUES ($1, $2, $3, $4) ";

    std::vector<int> note_ids;
    for (auto note : project.notes()) {
        note_ids.push_back(note.id());
    }

    const pqxx::result result = transaction.exec_params(
        query, project.code(), project.title(), note_ids,
        proto_arr_to_vector(project.members())
    );

    transaction.commit();
    return true;
}

bool ProjectDAO::add_member_to_project(
    const std::string &project_code,
    const std::string &member
) {
    return change_project_array(project_code, member, "members", "append");
}

bool ProjectDAO::delete_member_from_project(
    const std::string &project_code,
    const std::string &member
) {
    return change_project_array(project_code, member, "members", "remove");
}

bool ProjectDAO::add_note_to_project(
    const std::string &project_code,
    int note_id
) {
    return change_project_array(project_code, note_id, "notes", "append");
}

bool ProjectDAO::change_project_title(
    const std::string &project_code,
    const std::string &new_title
) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query =
        "UPDATE projects "
        "SET title = $1 "
        "WHERE code = $2 "
        "RETURNING 1;";

    const pqxx::result result =
        transaction.exec_params(query, new_title, project_code);
    if (result.empty()) {
        return false;
    }

    transaction.commit();
    return true;
}

bool ProjectDAO::delete_note_from_project(
    const std::string &project_code,
    int note_id
) {
    return change_project_array(project_code, note_id, "notes", "remove");
}

bool ProjectDAO::code_available(const std::string &project_code) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query =
        "SELECT code "
        "FROM projects "
        "WHERE code = $1 ";
    const pqxx::result result = transaction.exec_params(query, project_code);
    transaction.commit();
    if (result.empty()) {
        return true;
    }
    return false;
}
