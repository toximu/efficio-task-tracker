cmake_minimum_required(VERSION 3.16)
set(QT_NO_VULKAN_DETECTION TRUE)

project(login_window VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core Widgets Gui REQUIRED)

set(CMAKE_PREFIX_PATH "C:/Qt/6.8.2/mingw_64")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)
find_package(PostgreSQL REQUIRED)
link_directories(/path/to/postgresql/lib)


include_directories(
        ${CMAKE_SOURCE_DIR}/../database-for-lr
)

set(TS_FILES login_window_ru_RU.ts)

set(PROJECT_SOURCES
        main.cpp
        login_window.cpp
        login_window.h
        login_window.ui
        registration_window.cpp
        registration_window.h
        registration_window.ui
        ../database-for-lr/database_manager.cpp
        ../database-for-lr/database_manager.hpp
        ../database-for-lr/lr_dao.cpp
        ../database-for-lr/lr_dao.hpp     
)

qt_add_executable(login_window
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ../.clang-format
    registration_window_style_sheet.h
    login_window_style_sheet.h

)

target_link_libraries(login_window PRIVATE 
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
)

set_target_properties(login_window PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS login_window
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(login_window)