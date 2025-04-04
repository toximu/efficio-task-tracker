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
    static int try_register_user(const QString &login, const QString &password);
    static bool validate_user(const QString &login, const QString &password);
    static bool add_project_to_user(std::string user_login, int project_id);
    static bool
    get_user_projects(const std::string &login, std::vector<int> &projects);

private:
    static QString hash_password(const QString &password);
};

#endif  // LRDAO_H