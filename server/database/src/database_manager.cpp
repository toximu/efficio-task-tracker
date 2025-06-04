#include "database_manager.hpp"
#include <pqxx/pqxx>

DatabaseManager::DatabaseManager() {
    connection_ = std::make_unique<pqxx::connection>(get_connection_string());
    pqxx::work transaction(*connection_);

    transaction.exec(
        "CREATE TABLE IF NOT EXISTS notes ("
        "id SERIAL PRIMARY KEY, "
        "title TEXT NOT NULL, "
        "content TEXT, "
        "user_id VARCHAR(50) REFERENCES users(login), "
        "members VARCHAR(50)[], "
        "date VARCHAR(50), "
        "tags VARCHAR(50)[]"
        ")"
    );

    transaction.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "login VARCHAR(50) PRIMARY KEY, "
        "password VARCHAR(50) NOT NULL, "
        "token VARCHAR(100), "
        "projects VARCHAR(6)[]"
        ")"
    );

    transaction.exec(
        "CREATE TABLE IF NOT EXISTS projects ("
        "code VARCHAR(6) PRIMARY KEY, "
        "title VARCHAR(50) NOT NULL, "
        "notes INT[], "
        "members VARCHAR(50)[]"
        ")"
    );

    transaction.commit();
}

DatabaseManager &DatabaseManager::get_instance() {
    static DatabaseManager instance;
    if (!instance.connection_->is_open()) {
        throw std::runtime_error("Lost connection with database");
    }
    return instance;
}

pqxx::connection &DatabaseManager::get_connection() {
    if (!connection_->is_open()) {
        connection_ =
            std::make_unique<pqxx::connection>(get_connection_string());
    }
    return *connection_;
}

std::string DatabaseManager::get_connection_string() {
    return "postgresql://efficio:admin@localhost/efficio";
}