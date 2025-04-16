cmake_minimum_required(VERSION 3.16)

project(Service LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(libpqxx REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Threads)


file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(Service STATIC ${SOURCES} ${HEADERS})

target_link_libraries(Service
        Database
        model-proto
        efficio-rpc
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
        pqxx
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}
)