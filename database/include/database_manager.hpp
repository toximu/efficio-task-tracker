#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <QSqlQuery>

class DatabaseManager final {
public:
    static DatabaseManager &get_instance();
    [[nodiscard]] bool check_connection() const;
    bool execute_query(
        QSqlQuery &query,
        const QString &query_str,
        const QVariantList &params = {}
    ) const;
    [[nodiscard]] QSqlDatabase get_database() const;

private:
    explicit DatabaseManager();
    ~DatabaseManager();
    QSqlDatabase database_;
};

#endif  // DATABASE_MANAGER_HPP
