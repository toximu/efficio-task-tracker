#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

class DatabaseManager {
public:
    static DatabaseManager &get_instance();
    [[nodiscard]] bool check_connection() const;

    bool execute_query(
        QSqlQuery &query,
        const QString &query_str,
        const QVariantList &params
    );

private:
    explicit DatabaseManager();
    ~DatabaseManager();

    QSqlDatabase database_;
};

#endif  // DATABASE_MANAGER_H
