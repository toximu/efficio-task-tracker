cmake_minimum_required(VERSION 3.16)

project(LanguageManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Gui  Widgets Core Gui Sql REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


set(SOURCES
    src/language_manager.cpp
)

set(HEADERS
    include/language_manager.h
)

add_library(LanguageManager STATIC ${SOURCES} ${HEADERS})

target_include_directories(LanguageManager
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(LanguageManager PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Sql Database Scripts)

