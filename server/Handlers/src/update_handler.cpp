#include "update_handler.hpp"
#include <model-proto/model.pb.h>
#include <random>
#include "lr_dao.hpp"
#include "project_dao.hpp"

using Efficio_proto::Project;

std::string UpdateHandler::generate_project_code() {
    static const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<std::size_t> dis(0, chars.size() - 1);
    std::string result;
    for (size_t i = 0; i < 6; ++i) {
        result += chars[dis(gen)];
    }
    return result;
}

bool UpdateHandler::create_project(
    const CreateProjectRequest &request,
    CreateProjectResponse &response
) {
    if (!LRDao::validate_user(
            request.user().login(), request.user().hashed_password()
        )) {
        response.set_allocated_error_text(new std::string("Incorrect user"));
        return false;
    }
    Project *project = new Project();
    project->set_title(request.project_title());
    std::string project_code;
    while (true) {
        project_code = generate_project_code();
        if (ProjectDAO::code_available(project_code)) {
            break;
        }
    }
    project->set_code(project_code);
    *project->add_members() = request.user().login();
    ProjectDAO::insert_project(*project);
    LRDao::add_project_to_user(request.user().login(), project_code);
    response.set_allocated_project(project);
    return true;
}

bool UpdateHandler::try_join_project(
    const TryJoinProjectRequest &request,
    TryJoinProjectResponse &response
) {
    if (!LRDao::validate_user(
            request.user().login(), request.user().hashed_password()
        )) {
        response.set_allocated_error_text(new std::string("Incorrect user"));
        return false;
    }

    {
        std::vector<std::string> project_codes;
        LRDao::get_user_projects(request.user().login(), project_codes);
        for (const auto &project_code : project_codes) {
            if (project_code == request.code()) {
                response.set_allocated_error_text(
                    new std::string("Already have this project")
                );
                return false;
            }
        }
    }

    if (!ProjectDAO::add_member_to_project(
            request.code(), request.user().login()
        )) {
        response.set_allocated_error_text(
            new std::string("Can't add member to project")
        );
        return false;
    }
    if (!LRDao::add_project_to_user(request.user().login(), request.code())) {
        response.set_allocated_error_text(
            new std::string("Can't add project to user")
        );
        return false;
    }

    Project *project = new Project();
    ProjectDAO::get_project(request.code(), *project);
    response.set_allocated_project(project);

    return true;
}

bool UpdateHandler::try_leave_project(
    const TryLeaveProjectRequest &request,
    TryLeaveProjectResponse &response
) {
    if (!LRDao::validate_user(
            request.user().login(), request.user().hashed_password()
        )) {
        return false;
    }

    ProjectDAO::delete_member_from_project(
        request.code(), request.user().login()
    );

    LRDao::delete_project_from_user(request.user().login(), request.code());

    return true;
}

bool UpdateHandler::get_project(
    const GetProjectRequest &request,
    GetProjectResponse &response
) {

    Project *project = new Project();
    bool ok = ProjectDAO::get_project(request.code(), *project);
    if (!ok) {
        response.set_allocated_error_text(new std::string("Can't get project"));
        return false;
    }
    response.set_allocated_project(project);
    return true;
}
