#ifndef PROJECT_DAO_HPP
#define PROJECT_DAO_HPP

#include <QByteArray>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include "database_manager.hpp"
#include "project.hpp"

namespace DB {

class ProjectDAO {
public:
    ProjectDAO() = default;
    static bool create_project(const std::string &name, int &id);
    static bool get_project(int id, std::string &name, std::vector<int> &notes);
    static bool add_note_to_project(int project_id, int note_id);
};
}  // namespace DB

#endif