#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <vector>
#include "project.hpp"
#include "user.hpp"

class Storage {
public:
    void AddProject(const Project& project);
    void RemoveProject(int projectId);
    const std::vector<Project>& GetProjects() const;

    void AddUser(const User& user);
    void RemoveUser(int userId);
    const std::vector<User>& GetUsers() const;

private:
    std::vector<Project> projects;
    std::vector<User> users;
};

#endif
