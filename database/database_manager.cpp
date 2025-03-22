#include "database_manager.hpp"
#include <QApplication>
#include <QMessageBox>
#include <QSqlError>

DatabaseManager::DatabaseManager() {
    QSqlQuery query;

    database_ = QSqlDatabase::addDatabase("QPSQL");
    database_.setHostName("localhost");
    database_.setPort(5432);
    database_.setDatabaseName("efficio");
    database_.setUserName("efficio");
    database_.setPassword("admin");
    database_.open();

    query.exec(
        "CREATE TABLE IF NOT EXISTS notes ("
        "id SERIAL PRIMARY KEY, "
        "title TEXT NOT NULL, "
        "content TEXT NOT NULL"
        ")"
    );

    query.exec(
        "CREATE TABLE IF NOT EXISTS logins ("
        "login VARCHAR(50) PRIMARY KEY, "
        "password VARCHAR(50) NOT NULL "
        ")"
    );
}

DatabaseManager::~DatabaseManager() {
    if (database_.isOpen()) {
        database_.close();
    }
}

DatabaseManager &DatabaseManager::get_instance() {
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::check_connection() const {
    return database_.isOpen();
}

bool DatabaseManager::execute_query(
    QSqlQuery &query,
    const QString &query_str,
    const QVariantList &params
) {
    query.prepare(query_str);
    for (int i = 0; i < params.size(); i++) {
        query.bindValue(i, params[i]);
    }

    if (!query.exec()) {
        qDebug() << "Query execution error:" << query.lastError().text();
        return false;
    }
    return true;
}