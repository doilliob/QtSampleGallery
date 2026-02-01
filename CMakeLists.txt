cmake_minimum_required(VERSION 3.19)
project(QtSampleGallery LANGUAGES CXX)

# Compilation settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(UNIX)
   set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -O0")
   set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3")
else(UNIX)
   SET(CMAKE_CXX_FLAGS_DEBUG_INIT "/MDd /Wall /O0")
   SET(CMAKE_CXX_FLAGS_RELEASE_INIT "/MD /Wall /O2 /GL")
endif(UNIX)

# Qt library settings
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

# OpenCV library settings
find_package(OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Project
qt_standard_project_setup()

qt_add_executable(QtSampleGallery
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    imagefileiterator.h imagefileiterator.cpp
    imagefilemanipulator.h imagefilemanipulator.cpp
    brightlesspickerdialog.h brightlesspickerdialog.cpp brightlesspickerdialog.ui
    README.md
)

target_link_libraries(QtSampleGallery
    PRIVATE
        Qt::Core
        Qt::Widgets
        ${OpenCV_LIBS}
)

include(GNUInstallDirs)

install(TARGETS QtSampleGallery
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET QtSampleGallery
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
