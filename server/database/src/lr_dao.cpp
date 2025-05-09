#include "lr_dao.hpp"
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <array>
#include <iomanip>
#include <pqxx/pqxx>
#include <sstream>
#include "database_manager.hpp"

std::string LRDao::hash_password(const std::string &password) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        throw std::runtime_error("Failed to create EVP_MD_CTX");
    }

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr) != 1) {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Failed to initialize digest");
    }

    if (EVP_DigestUpdate(mdctx, password.c_str(), password.size()) != 1) {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Failed to update digest");
    }

    std::array<unsigned char, SHA256_DIGEST_LENGTH> hash{};
    unsigned int length = 0;
    if (EVP_DigestFinal_ex(mdctx, hash.data(), &length) != 1) {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("Failed to finalize digest");
    }

    EVP_MD_CTX_free(mdctx);

    std::stringstream ss;
    for (const auto &byte : hash) {
        ss << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(byte);
    }

    return ss.str();
}

bool LRDao::validate_password(
    const std::string &input_password,
    const std::string &stored_hash
) {
    const std::string input_hash = hash_password(input_password);
    return input_hash == stored_hash;
}

int LRDao::try_register_user(
    const std::string &login,
    const std::string &password
) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string check_query = "SELECT * FROM users WHERE login = $1";
    pqxx::params check_params;
    check_params.append(login);

    const pqxx::result check_result =
        transaction.exec(check_query, check_params);

    if (!check_result.empty()) {
        return -1;
    }

    const std::string hashed_password = hash_password(password);

    const std::string insert_query =
        "INSERT INTO users (login, password) VALUES ($1, $2)";
    pqxx::params insert_params;
    insert_params.append(login);
    insert_params.append(hashed_password);

    const pqxx::result insert_result =
        transaction.exec(insert_query, insert_params);

    transaction.commit();
    return insert_result.affected_rows() > 0 ? 1 : 0;
}

bool LRDao::validate_user(
    const std::string &login,
    const std::string &password
) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query = "SELECT password FROM users WHERE login = $1";
    pqxx::params params;
    params.append(login);

    const pqxx::result result = transaction.exec(query, params);

    if (result.empty()) {
        transaction.commit();
        return false;
    }

    const auto stored_hash = result[0]["password"].as<std::string>();
    const bool is_valid = validate_password(password, stored_hash);

    transaction.commit();
    return is_valid;
}

bool LRDao::add_project_to_user(
    const std::string &user_login,
    const int project_id
) {
    auto &connection = DatabaseManager::get_instance().get_connection();
    pqxx::work transaction(connection);

    const std::string query =
        "UPDATE users SET projects = array_append(projects, ?)"
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
