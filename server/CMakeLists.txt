cmake_minimum_required(VERSION 3.16)
project(Server)

add_subdirectory(Service)


add_executable(Server main.cpp)

target_link_libraries(Server Service)