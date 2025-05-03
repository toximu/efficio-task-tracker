#ifndef PROJECT_DAO_HPP
#define PROJECT_DAO_HPP

#include <string>
#include <model-proto/model.pb.h>

using namespace Efficio_proto;

class ProjectDAO {
    public:
        ProjectDAO() = default;
        static bool get_project(const std::string &code, Project &project);
};



#endif
