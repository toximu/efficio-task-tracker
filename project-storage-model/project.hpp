#ifndef PROJECT_HPP
#define PROJECT_HPP

#include "note.hpp"
#include <string>
#include <vector>

namespace project_storage_model {

class Project {
public:
  Project(int id, const std::string &name, const std::string &description);

  int get_id() const;
  const std::string &get_name() const;
  const std::string &get_description() const;
  const std::vector<Note> &get_notes() const;

  void add_note(const Note &note);
  void remove_note(int note_id);
  void edit_description(const std::string &description);

private:
  int id_;
  std::string name_;
  std::string description_;
  std::vector<Note> notes_;
};

} // namespace project_storage_model

#endif
