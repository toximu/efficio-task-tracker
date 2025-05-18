cmake_minimum_required(VERSION 3.16)

project(EfficioTaskTracker LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets LinguistTools Core Gui Sql REQUIRED)

set(TS_FILES
    translations/app_ru.ts
    translations/app_en.ts
)

qt_add_translation(QM_FILES ${TS_FILES})

qt_add_resources(PROJECT_RESOURCES
    PREFIX "/translations"
    FILES ${QM_FILES}
)

add_subdirectory(scripts)
add_subdirectory(database)
add_subdirectory(ui/profile-window)
add_subdirectory(ui/main-window)
add_subdirectory(ui/authorization-windows)
add_subdirectory(ui/note-widget)
add_subdirectory(ui/style-manager)
add_subdirectory(ui/settings-window)
add_subdirectory(ui/analytics-window)
add_subdirectory(proto)
add_executable(EfficioTaskTracker main.cpp)

target_link_libraries(EfficioTaskTracker PRIVATE
        Qt6::Widgets
        Qt6::Core
        Qt6::Gui
        Qt6::Sql
        model-proto
        efficio-rpc
        Database
        Scripts
        StyleManager
        AuthorizationWindows
        ProfileWindow
        MainWindow
        NoteWidget
        SettingsWindow
        AnalyticsWindow
)
