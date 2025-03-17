cmake_minimum_required(VERSION 3.16)

project(Efficio VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(MainWindow_dir ${CMAKE_SOURCE_DIR}/MainWindow/)
set(project-storage-model_dir ${CMAKE_SOURCE_DIR}/project-storage-model/)

set(TS_FILES ${MainWindow_dir}MainWindow_en_US.ts)

include_directories(MainWindow/include project-storage-model/include)

set(PROJECT_SOURCES
        main.cpp
        MainWindow/include/mainwindow.h
        MainWindow/src/mainwindow.cpp
        MainWindow/include/bottombar.h
        MainWindow/src/bottombar.cpp
        MainWindow/include/projectlist.h
        MainWindow/src/projectlist.cpp
        MainWindow/include/applicationwindow.h
        MainWindow/src/applicationwindow.cpp
        MainWindow/include/projectitem.h
        MainWindow/src/projectitem.cpp
        MainWindow/include/notelist.h
        MainWindow/src/notelist.cpp
        MainWindow/include/notewidget.h
        MainWindow/src/notewidget.cpp
        project-storage-model/src/note.cpp
        project-storage-model/src/project.cpp
        project-storage-model/src/storage.cpp
        project-storage-model/src/user.cpp
        project-storage-model/include/note.hpp
        project-storage-model/include/project.hpp
        project-storage-model/include/storage.hpp
        project-storage-model/include/user.hpp
        ${TS_FILES}
)





if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Efficio
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )


    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET MainWindow APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Efficio SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Efficio
                ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Efficio PRIVATE Qt${QT_VERSION_MAJOR}::Widgets )

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MainWindow)
endif()
set_target_properties(Efficio PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Efficio
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Efficio)
endif()
