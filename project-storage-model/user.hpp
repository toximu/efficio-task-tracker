#ifndef USER_HPP
#define USER_HPP

#include "project.hpp"
#include <string>
#include <vector>

namespace project_storage_model {

class User {
public:
  User(int id, const std::string &username);

  int get_id() const;
  const std::string &get_username() const;
  const std::vector<Project> &get_projects() const;

  void add_project(const Project &project);
  void remove_project(int project_id);

private:
  int id_;
  std::string username_;
  std::vector<Project> projects_;
};

} // namespace project_storage_model

#endif
