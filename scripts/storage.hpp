#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <list>
#include "project.hpp"
#include "user.hpp"

namespace project_storage_model {

class Storage {
public:
    Project &add_project(const Project &project);
    void remove_project(int project_id);
    [[nodiscard]] const std::list<Project> &get_projects() const;

    User &add_user(const User &user);
    void remove_user(int user_id);
    [[nodiscard]] const std::list<User> &get_users() const;

private:
    std::list<Project> projects_;
    std::list<User> users_;
};

}  // namespace project_storage_model

#endif
