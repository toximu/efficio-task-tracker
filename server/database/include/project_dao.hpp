#pragma once

#include <model-proto/model.pb.h>
#include <pqxx/pqxx>
#include <string>
#include "database_manager.hpp"

using namespace Efficio_proto;

class ProjectDAO {
    template <typename T>
    static bool change_project_array(
        const std::string &project_code,
        const T &parameter,
        const std::string &field,
        const std::string &operation
    ) {
        auto &connection = DatabaseManager::get_instance().get_connection();
        pqxx::work transaction(connection);

        const std::string query =
            "UPDATE projects "
            "SET " +
            field + " = array_" + operation + "(" + field +
            ", $1) "
            "WHERE code = $2 "
            "RETURNING 1;";

        const pqxx::result result =
            transaction.exec_params(query, parameter, project_code);
        if (result.empty()) {
            return false;
        }
        transaction.commit();
        return true;
    }

public:
    ProjectDAO() = default;
    static bool
    get_all_user_projects(const std::string &login, Storage &storage);
    static bool get_project(const std::string &project_code, Project &project);
    static bool insert_project(const Project &project);
    static bool add_member_to_project(
        const std::string &project_code,
        const std::string &member
    );
    static bool delete_member_from_project(
        const std::string &project_code,
        const std::string &member
    );
    static bool
    add_note_to_project(const std::string &project_code, int note_id);
    static bool
    delete_note_from_project(const std::string &project_code, int note_id);
    static bool change_project_title(
        const std::string &project_code,
        const std::string &new_title
    );
    static bool code_available(const std::string &project_code);
    static std::vector<std::string> get_members(
        const std::string &project_code
    );
};

template <typename T>
std::vector<T> proto_arr_to_vector(
    const google::protobuf::RepeatedPtrField<T> &array
) {
    std::vector<T> vec;
    for (int i = 0; i < array.size(); ++i) {
        vec.push_back(array[i]);
    }
    return std::move(vec);
}
