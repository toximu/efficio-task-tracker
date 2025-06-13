cmake_minimum_required(VERSION 3.16)

project(Client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Threads)


file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(Client STATIC ${SOURCES} ${HEADERS} src/client_implementation.cpp)

target_link_libraries(Client
        model-proto
        efficio-rpc
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)

target_include_directories(Client
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}
)

#add_executable(test-server test_server.cpp)
#target_link_libraries(test-server Client)