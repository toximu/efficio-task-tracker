#include "../include/user.hpp"
#include <algorithm>

namespace project_storage_model {

User::User(int id, const std::string &username)
    : id_(std::move(id)), username_(std::move(username)) {
}

[[nodiscard]] int User::get_id() const {
    return id_;
}

[[nodiscard]] const std::string &User::get_username() const {
    return username_;
}

const std::list<Project> &User::get_projects() const {
    return projects_;
}

Project &User::add_project(const Project &project) {
    projects_.push_back(project);
    return projects_.back();
}

void User::remove_project(int project_id) {
    projects_.erase(
        std::remove_if(
            projects_.begin(), projects_.end(),
            [project_id](const Project &project) {
                return project.get_id() == project_id;
            }
        ),
        projects_.end()
    );
}

}  // namespace project_storage_model
