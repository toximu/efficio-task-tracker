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


Project UpdateHandler::create_project(const std::string& title) {
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