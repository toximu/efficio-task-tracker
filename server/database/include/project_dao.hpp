#ifndef PROJECT_DAO_HPP
#define PROJECT_DAO_HPP

#include <string>
#include <model-proto/model.pb.h>

using namespace Efficio_proto;

class ProjectDAO {
public:
    ProjectDAO() = default;
    static bool get_project(const std::string &project_code, Project &project);
    static bool insert_project(Project &project);
    static bool add_member_to_project(const std::string& project_code, const std::string& member);
    static bool add_note_to_project(const std::string& project_code, int note_id);
    static bool change_project_title(const std::string& project_code, const std::string& new_title);
};

template<typename T>
std::vector<T> proto_arr_to_vector(const google::protobuf::RepeatedPtrField<T> &array) {
    std::vector<T> vec;
    for (int i = 0; i < array.size(); ++i) {
        vec.push_back(array[i]);
    }
    return std::move(vec);
}


#endif
