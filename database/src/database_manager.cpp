#include "database_manager.hpp"
#include <QApplication>
#include <QMessageBox>
#include <QSqlError>

DatabaseManager::DatabaseManager() {
    database_ = QSqlDatabase::addDatabase("QPSQL");
    database_.setHostName("localhost");
    database_.setPort(5432);
    database_.setDatabaseName("efficio");
    database_.setUserName("efficio");
    database_.setPassword("admin");
    database_.open();

    QSqlQuery query(database_);
    query.exec(
        "CREATE TABLE IF NOT EXISTS notes ("
        "id SERIAL PRIMARY KEY, "
        "title TEXT NOT NULL, "
        "content TEXT, "
        "members VARCHAR(50)[], "
        "date VARCHAR(50), "
        "tags VARCHAR(50)[]"
        ")"
    );

    query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "login VARCHAR(50) PRIMARY KEY, "
        "password VARCHAR(50) NOT NULL, "
        "projects INT[]"
        ")"
    );

    query.exec(
        "CREATE TABLE IF NOT EXISTS projects("
        "id SERIAL PRIMARY KEY, "
        "name VARCHAR(50) NOT NULL, "
        "notes INT[]"
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
    if (!instance.database_.isOpen() && !instance.database_.open()) {
        throw std::runtime_error("Lost connection with database");
    }
    return instance;
}

bool DatabaseManager::execute_query(
    QSqlQuery &query,
    const QString &query_str,
    const QVariantList &params
) const {
    QSqlQuery temp(database_);
    query = std::move(temp);

    if (!query.prepare(query_str)) {
        qDebug() << "Prepare error:" << query.lastError();
        return false;
    }

    for (int i = 0; i < params.size(); i++) {
        query.bindValue(i, params[i]);
    }

    return query.exec();
}

QSqlDatabase DatabaseManager::get_database() const {
    return database_;
}