#include "user.hpp"

User::User(int id, const std::string& username)
    : id(id), username(username) {}

int User::GetId() const {
    return id;
}

const std::string& User::GetUsername() const {
    return username;
}

const std::vector<Project>& User::GetProjects() const {
    return projects;
}

void User::AddProject(const Project& project) {
    projects.push_back(project);
}

void User::RemoveProject(int projectId) {
    projects.erase(std::remove_if(projects.begin(), projects.end(), [projectId](const Project& project) {
        return project.GetId() == projectId;
    }), projects.end());
}
