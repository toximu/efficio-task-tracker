#ifndef UPDATE_HANDLER_H
#define UPDATE_HANDLER_H

#include <model-proto/model.pb.h>

using Efficio_proto::Project;

class UpdateHandler {
public:
    static Project create_project(const std::string &title);
    static bool
    try_join_project(const std::string &project_code, const std::string &login);
    static bool try_leave_project(
        const std::string &project_code,
        const std::string &login
    );
    static std::optional<Project> get_project(const std::string &project_code);

private:
    static std::string generate_project_code();
};

#endif