cmake_minimum_required(VERSION 3.16)

project(Database LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(Qt6 COMPONENTS Widgets Core Sql REQUIRED)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

add_library(Database STATIC ${SOURCES} ${HEADERS})

target_include_directories(Database
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Database PRIVATE OpenSSL::Crypto Qt6::Widgets Qt6::Core Qt6::Sql model-proto pqxx NoteWidget)
add_executable(test_database main.cpp)
target_link_libraries(test_database Database model-proto)
