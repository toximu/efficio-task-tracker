#include "storage.hpp"

namespace project_storage_model {

Project& Storage::add_project(const Project &project) {
    projects_.push_back(project);  
    return projects_.back();     
}



void Storage::remove_project(int project_id) {
  projects_.erase(std::remove_if(projects_.begin(), projects_.end(),
                                 [project_id](const Project &project) {
                                   return project.get_id() == project_id;
                                 }),
                  projects_.end());
}

const std::list<Project> &Storage::get_projects() const { return projects_; }

User& Storage::add_user(const User &user) { users_.push_back(user); return users_.back(); }

void Storage::remove_user(int user_id) {
  users_.erase(std::remove_if(users_.begin(), users_.end(),
                              [user_id](const User &user) {
                                return user.get_id() == user_id;
                              }),
               users_.end());
}

const std::list<User> &Storage::get_users() const { return users_; }

} // namespace project_storage_model
