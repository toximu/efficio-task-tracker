#pragma once

#include <string>
#include <vector>

class LRDao {
public:
    LRDao() = default;
    static bool validate_password(
        const std::string &input_password,
        const std::string &stored_hash
    );
    static int
    try_register_user(const std::string &login, const std::string &password);
    static bool
    validate_user(const std::string &login, const std::string &password);
    static bool add_project_to_user(
        const std::string &user_login,
        const std::string &project_code
    );
    static bool get_user_projects(
        const std::string &login,
        std::vector<std::string> &projects
    );
    static bool delete_project_from_user(
        const std::string &login,
        const std::string &project_code
    );
    static bool try_delete_user(const std::string &login);

private:
    static std::string hash_password(const std::string &password);
};
