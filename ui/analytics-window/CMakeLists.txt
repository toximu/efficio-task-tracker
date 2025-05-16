cmake_minimum_required(VERSION 3.16)

project(AnalyticsWindow LANGUAGES CXX)  

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Core Gui Sql Charts REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    src/analytics_window.cpp
)

set(HEADERS
    include/analytics_window.h
    include/analytics_window_style_sheet.h  
)

add_library(AnalyticsWindow STATIC ${SOURCES} ${HEADERS})

target_include_directories(AnalyticsWindow
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(AnalyticsWindow
    PRIVATE 
        Qt6::Core 
        Qt6::Gui 
        Qt6::Sql
        Database 
        ThemeManager
    PUBLIC 
        Qt6::Widgets 
        Qt6::Charts   
)