#include "update_handler.hpp"
#include <model-proto/model.pb.h>
#include <random>
#include "project_dao.hpp"

using Efficio_proto::Project;

std::string UpdateHandler::generate_project_code() {
    static const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, chars.size() - 1);
    std::string result;
    for (size_t i = 0; i < 6; ++i) {
        result += chars[dis(gen)];
    }
    return result;
}

Project UpdateHandler::create_project(const std::string &title) {
    Project project;
    project.set_title(title);
    std::string project_code;
    while (true) {
        project_code = generate_project_code();
        if (ProjectDAO::code_available(project_code)) {
            break;
        }
    }
    project.set_code(project_code);
    ProjectDAO::insert_project(project);
    return std::move(project);
}

bool UpdateHandler::try_join_project(
    const std::string &project_code,
    const std::string &login
) {
    // todo: check if login exists

    // todo: check if users has not this project already

    if (!ProjectDAO::add_member_to_project(project_code, login)) {
        return false;
    }

    // todo: add project to user(UserDAO not exists yet)

    return true;
}

bool UpdateHandler::try_leave_project(
    const std::string &project_code,
    const std::string &login
) {
    // todo : check if login exists

    if (!ProjectDAO::delete_member_from_project(project_code, login)) {
        return false;
    }

    // todo : delete project from user

    return true;
}

std::optional<Project> UpdateHandler::get_project(const std::string &project_code) {
    Project project;
    bool ok = ProjectDAO::get_project(project_code, project);
    if (!ok) {
        return std::nullopt;
    }
    return project;
}
