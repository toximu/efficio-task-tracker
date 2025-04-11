cmake_minimum_required(VERSION 3.16)
project(NoteWidgetEfficio VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

file(GLOB NOTE_WIDGET_SRC "src/*.cpp")
file(GLOB NOTE_WIDGET_INCLUDE "include/*.h")
file(GLOB NOTE_WIDGET_UI "ui/*.ui")

set(TS_FILES NoteWidgetEfficio_ru_RU.ts)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

add_library(${PROJECT_NAME} STATIC
        ${NOTE_WIDGET_SRC}
        ${NOTE_WIDGET_UI}
        ${TS_FILES}
)

target_include_directories(NoteWidgetEfficio PUBLIC
        ${CMAKE_SOURCE_DIR}/../../scripts
        ${CMAKE_SOURCE_DIR}/../../database
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(NoteWidgetEfficio PUBLIC
        Qt6::Core
        Qt6::Widgets
        Qt6::Sql
)

set_target_properties(NoteWidgetEfficio PROPERTIES
        ARCHIVE_OUTPUT_NAME NoteWidgetEfficio
        POSITION_INDEPENDENT_CODE ON
)

include(GNUInstallDirs)
install(TARGETS NoteWidgetEfficio
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h*"
)