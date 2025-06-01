#ifndef UPDATE_HANDLER_H
#define UPDATE_HANDLER_H

#include <efficio-rpc-proto/efficio.pb.h>
#include <model-proto/model.pb.h>

using Efficio_proto::CreateProjectRequest;
using Efficio_proto::CreateProjectResponse;
using Efficio_proto::GetProjectRequest;
using Efficio_proto::GetProjectResponse;
using Efficio_proto::Project;
using Efficio_proto::TryJoinProjectRequest;
using Efficio_proto::TryJoinProjectResponse;
using Efficio_proto::TryLeaveProjectRequest;
using Efficio_proto::TryLeaveProjectResponse;
using Efficio_proto::UpdateProjectRequest;
using Efficio_proto::UpdateProjectResponse;

class UpdateHandler {
public:
    static bool create_project(
        const CreateProjectRequest &request,
        CreateProjectResponse &response
    );
    static bool try_join_project(
        const TryJoinProjectRequest &request,
        TryJoinProjectResponse &response
    );
    static bool try_leave_project(
        const TryLeaveProjectRequest &request,
        TryLeaveProjectResponse &response
    );
    static bool
    get_project(const GetProjectRequest &request, GetProjectResponse &response);

private:
    static std::string generate_project_code();
};

#endif