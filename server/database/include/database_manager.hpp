#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <pqxx/pqxx>
#include "note_dao.hpp"

class DatabaseManager final {
public:
    static DatabaseManager &get_instance();
    pqxx::connection& get_connection();
    [[nodiscard]] static std::string get_connection_string();

private:
    explicit DatabaseManager();
    ~DatabaseManager() = default;
    std::unique_ptr<pqxx::connection> connection_;
};

#endif  // DATABASE_MANAGER_HPP