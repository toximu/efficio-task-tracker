#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <QSqlError>
#include <QSqlQuery>

class DatabaseManager final : public QObject {
    Q_OBJECT

public:
    static DatabaseManager &get_instance();
    [[nodiscard]] bool check_connection() const;
    bool execute_query(
        QSqlQuery &query,
        const QString &query_str,
        const QVariantList &params = {}
    );

private:
    explicit DatabaseManager();
    ~DatabaseManager() override;

    QSqlDatabase database_;
};

#endif  // DATABASE_MANAGER_HPP
