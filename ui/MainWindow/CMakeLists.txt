cmake_minimum_required(VERSION 3.14)
project(MainWindow)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets Core LinguistTools)

file(GLOB MAIN_WINDOW_SRC "src/*")
file(GLOB MAIN_WINDOW_INCLUDE "include/*")


add_library(${PROJECT_NAME}
    ${MAIN_WINDOW_SRC}
        ${MAIN_WINDOW_INCLUDE}
        MainWindow_en_US.ts
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core)
target_link_libraries(${PROJECT_NAME} PUBLIC project-storage-model)

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)