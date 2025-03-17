#include "user.hpp"
#include <algorithm>
#include <utility>

namespace project_storage_model {

User::User(const int id, std::string username)
    : id_(id), username_(std::move(username)) {
}

int User::get_id() const {
    return id_;
}

const std::string &User::get_username() const {
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
