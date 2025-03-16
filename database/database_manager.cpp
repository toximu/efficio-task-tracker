#include "database_manager.hpp"
#include <QApplication>
#include <QMessageBox>

DatabaseManager::DatabaseManager() {
    QCoreApplication::addLibraryPath("/usr/lib/x86_64-linux-gnu/qt6/plugins");
    database_ = QSqlDatabase::addDatabase("QPSQL");
    database_.setHostName("localhost");
    database_.setPort(5433);
    database_.setDatabaseName("efficio");
    database_.setUserName("efficio");
    database_.setPassword("admin");

    if (!database_.open()) {
        const QString error = database_.lastError().text();

        QMessageBox::critical(
            nullptr, "Database Error", "Cannot connect to database:\n" + error
        );
    } else {
        qDebug() << "OK";
    }
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

QSqlQuery DatabaseManager::execute_query(
    const QString &query,
    const QVariantList &params
) {
    QSqlQuery q;
    q.prepare(query);
    for (const auto &param : params) {
        q.addBindValue(param);
    }

    if (!q.exec()) {
        qDebug() << "Query execution error:" << q.lastError().text();
    }

    return q;
}