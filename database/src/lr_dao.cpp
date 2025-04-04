#include "lr_dao.hpp"
#include <QCryptographicHash>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVariantList>
#include <iostream>

QString LRDao::hash_password(const QString &password) {
    const QByteArray hash =
        QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return hash.toHex();
}

int LRDao::try_register_user(const QString &login, const QString &password) {
    QSqlQuery query;

    const bool is_login_free = DatabaseManager::get_instance().execute_query(
        query, "SELECT * FROM users WHERE login = ?", {login}
    );

    if (!is_login_free) {
        return -1;
    }

    QSqlQuery insert_query;
    return static_cast<int>(DatabaseManager::get_instance().execute_query(
        insert_query, "INSERT INTO users (login, password) VALUES (?, ?)",
        {login, password}
    ));
}

bool LRDao::validate_user(const QString &login, const QString &password) {
    QSqlQuery query;

    const QString query_str =
        "SELECT * FROM users WHERE login = ? AND password = ?";
    const QVariantList params = {login, password};

    const auto success =
        DatabaseManager::get_instance().execute_query(query, query_str, params);

    return query.next() && success;
}

bool LRDao::add_project_to_user(std::string user_login, int project_id) {
    QSqlQuery query;
    const QString query_str =
        "UPDATE users SET projects = array_append(projects, ?)"
        "WHERE login = ?";

    const QVariantList params = {
        QString::fromStdString(std::to_string(project_id)),
        QString::fromStdString(user_login)};

    return DatabaseManager::get_instance().execute_query(
        query, query_str, params
    );
}

bool LRDao::get_user_projects(
    const std::string &login,
    std::vector<int> &projects
) {
    QSqlQuery query;
    const QString query_str =
        "SELECT array_to_string(projects, ',') FROM users WHERE login = ?";

    const QVariantList params = {QString::fromStdString(login)};
    bool is_success =
        DatabaseManager::get_instance().execute_query(query, query_str, params);

    if (is_success && query.next() && query.value(0).isValid()) {
        QStringList ps = query.value(0).toString().split(",");
        for (auto i : ps) {
            projects.push_back(i.toInt());
        }

        return true;
    }
    return false;
}