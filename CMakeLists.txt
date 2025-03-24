cmake_minimum_required(VERSION 3.21)
project(Efficio VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)
find_package(PostgreSQL REQUIRED)
link_directories(/path/to/postgresql/lib)

add_subdirectory("ui/MainWindow")
add_subdirectory("project-storage-model")
add_subdirectory("ui/login-and-registration-windows")

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/ui/login-and-registration-windows/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/ui/MainWindow/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/database"
)

target_link_libraries(Efficio
    Qt6::Widgets
    Qt6::Core
    Qt6::Sql
    MainWindow
    LoginAndRegistrationWindows
)