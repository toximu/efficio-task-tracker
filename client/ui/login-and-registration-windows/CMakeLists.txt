cmake_minimum_required(VERSION 3.16)
project(LoginRegistrationWindows VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)
find_package(PostgreSQL REQUIRED)
link_directories(/path/to/postgresql/lib)

find_package(Qt6 COMPONENTS Core Widgets Gui REQUIRED)

set(TS_FILES login_window_ru_RU.ts)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

file(GLOB LOGIN_REGISTRATION_WINDOWS_SRC "src/*")
file(GLOB LOGIN_REGISTRATION_WINDOWS_INCLUDE "include/*")
file(GLOB LOGIN_REGISTRATION_WINDOWS_UI "ui/*")


add_library(${PROJECT_NAME}
    ${LOGIN_REGISTRATION_WINDOWS_SRC}
        ${LOGIN_REGISTRATION_WINDOWS_INCLUDE}
        login_window_ru_RU.ts
)

target_include_directories(LoginRegistrationWindows PUBLIC
        ${CMAKE_SOURCE_DIR}/../../scripts
        ${CMAKE_SOURCE_DIR}/../../database
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(LoginRegistrationWindows PRIVATE 
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
)

set_target_properties(LoginRegistrationWindows PROPERTIES
    ARCHIVE_OUTPUT_NAME LoginRegistrationWindows
    POSITION_INDEPENDENT_CODE ON
)

include(GNUInstallDirs)
install(TARGETS LoginRegistrationWindows
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h*"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core)

qt_finalize_executable(LoginRegistrationWindows)