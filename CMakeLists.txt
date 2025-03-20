cmake_minimum_required(VERSION 3.21)

project(Efficio VERSION 1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools)

add_subdirectory(ui/MainWindow)
add_subdirectory(project-storage-model)



add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        Qt6::Widgets
        MainWindow
)
