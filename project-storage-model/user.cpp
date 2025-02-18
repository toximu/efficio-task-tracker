#include "user.hpp"

namespace project_storage_model {

User::User(int id, const std::string &username)
    : id_(id), username_(username) {}

int User::get_id() const { return id_; }

const std::string &User::get_username() const { return username_; }

const std::vector<Project> &User::get_projects() const { return projects_; }

void User::add_project(const Project &project) { projects_.push_back(project); }

void User::remove_project(int project_id) {
  projects_.erase(std::remove_if(projects_.begin(), projects_.end(),
                                 [project_id](const Project &project) {
                                   return project.get_id() == project_id;
                                 }),
                  projects_.end());
}

} // namespace project_storage_model
