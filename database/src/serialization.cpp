#include "serialization.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include "lr_dao.hpp"
#include "note.hpp"
#include "note_dao.hpp"
#include "project.hpp"
#include "project_dao.hpp"
#include "storage.hpp"

bool Serialization::get_storage(project_storage_model::Storage &storage, const std::string& login) {

    std::vector<int> projects;
    if (LRDao::get_user_projects(login, projects)) {
        for (auto p : projects) {
            // std::cout << p << std::endl;
            std::string project_name;
            std::vector<int> notes;
            if (DB::ProjectDAO::get_project(p, project_name, notes)) {
                Project project{p, project_name, ""};
                for (auto n : notes) {
                    auto note = NoteDao::get_note_by_id(n);
                    project.add_note(note);
                }
                storage.add_project(project);
            } else {
                std::cout << "get project";

                return false;
            }
        }
    } else {

        std::cout << "get projects";

        return false;
    }
    return true;
}