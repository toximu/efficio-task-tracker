cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(PROJECT_STORAGE_MODEL_DIR ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Protobuf REQUIRED)

set(PROTO_FILES
    ${PROJECT_STORAGE_MODEL_DIR}/note.proto
    ${PROJECT_STORAGE_MODEL_DIR}/project.proto
    ${PROJECT_STORAGE_MODEL_DIR}/storage.proto
    ${PROJECT_STORAGE_MODEL_DIR}/user.proto
)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

set(SOURCES
    ${PROJECT_STORAGE_MODEL_DIR}/main.cpp
    ${PROTO_SRCS}
)

include_directories(${Protobuf_INCLUDE_DIRS} ${PROJECT_STORAGE_MODEL_DIR})

add_executable(MyProject ${SOURCES})

target_link_libraries(MyProject ${Protobuf_LIBRARIES})
