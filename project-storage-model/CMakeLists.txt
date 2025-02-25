cmake_minimum_required(VERSION 3.10)

project(ProjectStorageModel)

find_package(Protobuf REQUIRED)

set(PROTO_FILES
    note.proto
    project.proto
    user.proto
    storage.proto
)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

set(SOURCES
    main.cpp
    ${PROTO_SRCS}
)

add_executable(my_program ${SOURCES})

target_link_libraries(my_program ${PROTOBUF_LIBRARIES})

include_directories(${PROTOBUF_INCLUDE_DIRS})

target_compile_options(my_program PRIVATE -std=c++11)
