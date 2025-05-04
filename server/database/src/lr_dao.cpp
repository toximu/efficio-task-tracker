#include "lr_dao.hpp"
#include <pqxx/pqxx>
#include "database_manager.hpp"

int LRDao::try_register_user(const std::string &login, const std::string &password) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string check_query = "SELECT * FROM users WHERE login = ?";
    pqxx::params check_params;
    check_params.append(login);

    const pqxx::result check_result = transaction.exec(check_query, check_params);

    if (!check_result.empty()) {
        return -1;
    }

    const std::string insert_query = "INSERT INTO users (login, password) VALUES (?, ?)";
    pqxx::params insert_params;
    insert_params.append(login);
    insert_params.append(password);

    const pqxx::result insert_result = transaction.exec(insert_query, insert_params);

    transaction.commit();
    return insert_result.affected_rows() > 0;
}

bool LRDao::validate_user(const std::string &login, const std::string &password) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query = "SELECT * FROM users WHERE login = ? AND password = ?";
    pqxx::params params;
    params.append(login);
    params.append(password);

    const pqxx::result result = transaction.exec(query, params);

    transaction.commit();
    return result.affected_rows() > 0;
}

bool LRDao::add_project_to_user(
    const std::string &user_login, const int project_id) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query = "UPDATE users SET projects = array_append(projects, ?)"
        "WHERE login = ?";
    pqxx::params params;
    params.append(project_id);
    params.append(user_login);

    const pqxx::result result = transaction.exec(query, params);
    transaction.commit();
    return result.affected_rows() > 0;
}

bool LRDao::get_user_projects(
    const std::string &login,
    std::vector<int> &projects
) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query = "SELECT projects FROM users WHERE login = $1";
    pqxx::params params;
    params.append(login);

    const pqxx::result result = transaction.exec(query, params);

    if (!result.empty()) {
        const auto &row = result[0];
        if (!row["projects"].is_null()) {
            const auto projects_as_string = row["projects"].as<std::string>();

            std::string clean_string = projects_as_string;
            if (!clean_string.empty() && clean_string.front() == '{' &&
                clean_string.back() == '}') {
                clean_string = clean_string.substr(1, clean_string.size() - 2);
            }

            std::istringstream iss(clean_string);
            std::string project_id;
            while (std::getline(iss, project_id, ',')) {
                if (!project_id.empty()) {
                    projects.push_back(std::stoi(project_id));
                }
            }

            transaction.commit();
            return true;
        }
    }

    transaction.commit();
    return false;
}
