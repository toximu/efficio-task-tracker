cmake_minimum_required(VERSION 3.16)

project(EfficioTaskTracker LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Core Gui Sql REQUIRED)

#add_subdirectory(scripts)
#add_subdirectory(database)
add_subdirectory(ui/main-window)
add_subdirectory(ui/note-widget)
add_subdirectory(ui/authorization-windows)
add_subdirectory(ui/theme-manager)
add_subdirectory(client)
add_executable(EfficioTaskTracker main.cpp)

target_link_libraries(EfficioTaskTracker PRIVATE
        model-proto
        Qt6::Widgets
        Qt6::Core
        Qt6::Gui
        Qt6::Sql
        Database
        Scripts
        NoteWidget
        MainWindow
        AuthorizationWindows
        ThemeManager
        model-proto
        Client
)
