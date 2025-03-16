cmake_minimum_required(VERSION 3.10)

project(project-storage-model)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    note.cpp
    project.cpp
    storage.cpp
    user.cpp
)

set(HEADERS
    note.hpp
    project.hpp
    storage.hpp
    user.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})