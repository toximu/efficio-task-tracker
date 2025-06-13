cmake_minimum_required(VERSION 3.16)

project(NoteWidget LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Core Gui Sql REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

set(UI_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/note_edit_dialog.ui
)

set(SOURCES
        src/note_edit_dialog.cpp
        src/tags_dialog.cpp
)

set(HEADERS
        include/note_edit_dialog.h
        include/tags_dialog.h
)

file(GLOB TS_FILES "*.ts")

add_library(NoteWidget STATIC ${SOURCES} ${HEADERS} ${UI_FILES})

target_include_directories(NoteWidget
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(NoteWidget Client Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Sql Database LanguageManager model-proto StyleManager)