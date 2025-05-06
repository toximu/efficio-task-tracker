#ifndef UPDATE_HANDLER_H
#define UPDATE_HANDLER_H

#include <model-proto/model.pb.h>

using Efficio_proto::Project;

class UpdateHandler {
public:
    static Project create_project(const std::string& title);
private:
    static std::string generate_project_code();
};



#endif