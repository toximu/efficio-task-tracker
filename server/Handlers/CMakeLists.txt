cmake_minimum_required(VERSION 3.16)

project(Handlers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

add_library(Handlers STATIC ${SOURCES} ${HEADERS})

target_link_libraries(Handlers
        efficio-rpc
        model-proto
        Database
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}
)