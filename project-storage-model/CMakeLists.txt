cmake_minimum_required(VERSION 3.10)

project(MyProject)

find_package(Protobuf REQUIRED)

set(PROTO_FILES
    note.proto
    project.proto
    storage.proto
    user.proto
)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

set(SOURCES
    main.cpp
    ${PROTO_SRCS}
)

include_directories(${Protobuf_INCLUDE_DIRS})

add_executable(MyProject ${SOURCES})

target_link_libraries(MyProject ${Protobuf_LIBRARIES})
