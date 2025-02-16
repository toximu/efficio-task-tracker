#include "storage.hpp"

void Storage::AddProject(const Project& project) {
    projects.push_back(project);
}

void Storage::RemoveProject(int projectId) {
    projects.erase(std::remove_if(projects.begin(), projects.end(), [projectId](const Project& project) {
        return project.GetId() == projectId;
    }), projects.end());
}

const std::vector<Project>& Storage::GetProjects() const {
    return projects;
}

void Storage::AddUser(const User& user) {
    users.push_back(user);
}

void Storage::RemoveUser(int userId) {
    users.erase(std::remove_if(users.begin(), users.end(), [userId](const User& user) {
        return user.GetId() == userId;
    }), users.end());
}

const std::vector<User>& Storage::GetUsers() const {
    return users;
}
