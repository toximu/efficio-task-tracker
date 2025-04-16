cmake_minimum_required(VERSION 3.16)
project(server)
add_subdirectory(Service)


add_executable(start_server main.cpp)

target_link_libraries(start_server Service Database)