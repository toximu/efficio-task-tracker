cmake_minimum_required(VERSION 3.16)

project(MainWindow LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Core Gui Sql REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.h")
file(GLOB UI_FILES CONFIGURE_DEPENDS "ui/*.ui")

add_library(MainWindow STATIC
        ${SOURCES}
        ${HEADERS}
        ${UI_FILES}
)

target_include_directories(MainWindow PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(MainWindow PRIVATE
        Qt6::Widgets
        Qt6::Core
        Qt6::Gui
        Qt6::Sql
)