#include "lr_dao.hpp"
#include <QCryptographicHash>
#include <QDebug>
#include <QSqlQuery>
#include <QVariantList>

QString LRDao::hash_password(const QString &password) {
    QByteArray hash =
        QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return hash.toHex();
}

bool LRDao::register_user(const QString &login, const QString &password) {
    // maybe in future make it thread-safe?
    QSqlQuery query;

    QString check_query_str = "SELECT * FROM users WHERE login = ?";
    QVariantList check_params = {login};
    bool check_query = DatabaseManager::get_instance().execute_query(
        query, check_query_str, check_params
    );

    if (check_query) {
        return false;
    }
    QString hashed_password = LRDao::hash_password(password);
    QString insert_query_str =
        "INSERT INTO users (login, password) VALUES (?, ?)";
    QVariantList insert_params = {login, hashed_password};

    return DatabaseManager::get_instance().execute_query(
        query, insert_query_str, insert_params
    );
}

bool LRDao::validate_user(const QString &login, const QString &password) {
    QSqlQuery query;

    QString hashed_password = LRDao::hash_password(password);
    QString query_str = "SELECT * FROM users WHERE login = ? AND password = ?";
    QVariantList params = {login, hashed_password};

    return DatabaseManager::get_instance().execute_query(
        query, query_str, params
    );
    return query.next();
}
