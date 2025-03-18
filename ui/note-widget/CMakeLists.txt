cmake_minimum_required(VERSION 3.16)
set(QT_NO_VULKAN_DETECTION TRUE)

project(NoteWidgetEfficio VERSION 0.1 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "D:/Programs/Qt/6.8.2/mingw_64/lib/cmake")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

include_directories(
        ${CMAKE_SOURCE_DIR}/../../scripts
        ${CMAKE_SOURCE_DIR}/../../database
)

set(TS_FILES NoteWidgetEfficio_ru_RU.ts)

set(PROJECT_SOURCES
        main.cpp
        note_edit_dialog.cpp
        note_edit_dialog.h
        note_edit_dialog.ui
        ../../database/database_manager.cpp
        ../../database/database_manager.hpp
        ../../database/note_dao.cpp
        ../../database/note_dao.hpp
        ../../scripts/note.cpp
        tags_dialog.h
        tags_dialog.cpp
        ../../scripts/user.hpp
        ../../scripts/user.cpp
        ../../scripts/project.cpp
        ../../scripts/storage.cpp
)

qt_add_executable(NoteWidgetEfficio
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        .clang-format
        note_edit_dialog_styles.h
        tags_dialog_styles.h
)

target_link_libraries(NoteWidgetEfficio PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Sql
)

set_target_properties(NoteWidgetEfficio PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS NoteWidgetEfficio
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(NoteWidgetEfficio)