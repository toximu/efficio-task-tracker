#ifndef USER_HPP
#define USER_HPP

#include <list>
#include <string>
#include "project.hpp"

namespace project_storage_model {

class User {
public:
    User(int id, std::string username);

    [[nodiscard]] int get_id() const;
    [[nodiscard]] const std::string &get_username() const;
    [[nodiscard]] const std::list<Project> &get_projects() const;

    Project &add_project(const Project &project);
    void remove_project(int project_id);

private:
    int id_;
    std::string username_;
    std::list<Project> projects_;
};

}  // namespace project_storage_model

#endif
