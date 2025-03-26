#ifndef LRDAO_H
#define LRDAO_H

#include <QByteArray>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include "database_manager.hpp"

class LRDao {
public:
    LRDao() = default;
    static bool try_register_user(const QString &login, const QString &password);
    static bool validate_user(const QString &login, const QString &password);

private:
    static QString hash_password(const QString &password);
};

#endif  // LRDAO_H
