cmake_minimum_required(VERSION 3.16)

project(AuthorizationWindows LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Core Gui Sql REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

set(UI_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/login_window.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/registration_window.ui
)

set(SOURCES
        src/login_window.cpp
        src/registration_window.cpp
)

set(HEADERS
        include/login_window.h
        include/login_window_style_sheet.h
        include/registration_window_style_sheet.h
        include/registration_window.h
)

file(GLOB TS_FILES "*.ts")

add_library(AuthorizationWindows STATIC ${SOURCES} ${HEADERS} ${UI_FILES})

target_include_directories(AuthorizationWindows
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(AuthorizationWindows PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Sql Database Scripts MainWindow)