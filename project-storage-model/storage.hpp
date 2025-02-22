#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "project.hpp"
#include "user.hpp"
#include <vector>

namespace project_storage_model {

class Storage {
public:
  void add_project(const Project &project);
  void remove_project(int project_id);
  const std::vector<Project> &get_projects() const;

  void add_user(const User &user);
  void remove_user(int user_id);
  const std::vector<User> &get_users() const;

private:
  std::vector<Project> projects_;
  std::vector<User> users_;
};

} // namespace project_storage_model

#endif
