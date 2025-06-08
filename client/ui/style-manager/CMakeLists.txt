cmake_minimum_required(VERSION 3.16)

project(StyleManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Gui  Widgets Core Gui Sql REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


set(SOURCES
    src/style_manager.cpp
)

set(HEADERS
    include/style_manager.h
)

add_library(StyleManager STATIC ${SOURCES} ${HEADERS})

target_include_directories(StyleManager
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(StyleManager PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Sql Database)

