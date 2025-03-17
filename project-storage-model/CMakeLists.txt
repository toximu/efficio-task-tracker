cmake_minimum_required(VERSION 3.10)

project(project-storage-model)


add_library(${PROJECT_NAME} STATIC src/note.cpp src/project.cpp src/storage.cpp src/user.cpp)
add_executable(test main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)