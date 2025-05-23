cmake_minimum_required(VERSION 3.16)

project(Database LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Sql REQUIRED)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

add_library(Database STATIC ${SOURCES} ${HEADERS})

target_include_directories(Database
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Database PRIVATE Qt6::Core Qt6::Sql Qt6::Widgets Scripts)