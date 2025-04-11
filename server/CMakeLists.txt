cmake_minimum_required(VERSION 3.16)
project(server)
add_subdirectory(Service)


add_executable(main main.cpp)

target_link_libraries(main Service)