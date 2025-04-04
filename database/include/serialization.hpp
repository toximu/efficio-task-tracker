#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP
#include "storage.hpp"

class Serialization {
public:
    static bool get_storage(
        project_storage_model::Storage &storage,
        const std::string &login
    );
};

#endif