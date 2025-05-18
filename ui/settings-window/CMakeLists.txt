cmake_minimum_required(VERSION 3.16)

project(SettingsWindow LANGUAGES CXX)  

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Core Gui Sql REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    src/settings_window.cpp
)

set(HEADERS
    include/settings_window.h
    include/settings_window_style_sheet.h  
)

add_library(SettingsWindow STATIC ${SOURCES} ${HEADERS} ${UI_FILES})

target_include_directories(SettingsWindow
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(SettingsWindow PRIVATE 
    Qt6::Widgets 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Sql
    Database 
    StyleManager
    AuthorizationWindows
)