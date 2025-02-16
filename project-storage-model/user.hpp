#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include "project.hpp"

class User {
public:
    User(int id, const std::string& username);
    
    int GetId() const;
    const std::string& GetUsername() const;
    const std::vector<Project>& GetProjects() const;
    
    void AddProject(const Project& project);
    void RemoveProject(int projectId);

private:
    int id;
    std::string username;
    std::vector<Project> projects;
};

#endif
