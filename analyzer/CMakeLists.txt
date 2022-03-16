# CMAKE VERSION
cmake_minimum_required(VERSION 3.5)

# PROJECT
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(PROJECT_NAME "analyzer" CACHE STRING "Project name")
project(${PROJECT_NAME} VERSION ${PROJECT_VESRION})
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Qwt
if (WIN32)
    set(QWT_INCLUDE_DIR "C:/qwt-6.1.5_64/src")
    set(QWT_LIBRARY "C:/qwt-6.1.5_64/lib/qwt.dll")
    set(TF_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/tensorflow/include/)
    set(TF_LIBRARY ${CMAKE_SOURCE_DIR}/tensorflow/lib/tensorflow.lib)
endif(WIN32)
if (UNIX)
    set(QWT_INCLUDE_DIR "/usr/local/qwt-6.1.5/include")
    set(QWT_LIBRARY "/usr/local/qwt-6.1.5/lib/libqwt.so")
endif(UNIX)

# SOURCES
set(
    SOURCES
        analyzer.cpp
        model.cpp
        mainwidget.cpp
        simulator.cpp
        nuclidelibrary.cpp
        graph.cpp
        controller.cpp
        graphcanvas.cpp
        tfidentifier.cpp
        mathutils.cpp
        session.cpp
        tcpserverthread.cpp
        tcpaccess.cpp
)

# HEADERS
set (
    HEADERS
        types.h
        detectoraccess.h
        view.h
        identifymethod.h
        mlidentifier.h
        simplemethod.h
        deconvmethod.h
        model.h
        nuclidelibrary.h
        mainwidget.h
        simulator.h
        graph.h
        controller.h
        observer.h
        graphcanvas.h
        tfidentifier.h
        mathutils.h
        session.h
        tcpserverthread.h
        tcpaccess.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# PROPERTIES
set_target_properties (
    ${PROJECT_NAME}
        PROPERTIES
            CMAKE_CXX_STANDARD 17
            CMAKE_CXX_STANDARD_REQUIRED ON
)

# Linking
target_include_directories(
    ${PROJECT_NAME}
        PRIVATE
            ${QWT_INCLUDE_DIR}
            ${TF_INCLUDE_DIR}
            ${Boost_INCLUDE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE
            Qt${QT_VERSION_MAJOR}::Widgets
            ${QWT_LIBRARY}
            ${TF_LIBRARY}
            ${Boost_LIBRARIES}
            wsock32
            ws2_32
)

# Compiler options
target_compile_options(
    ${PROJECT_NAME}
        PRIVATE
            -Wall -Wextra -pedantic -Werror
)

#configure_file(
#    ${CMAKE_SOURCE_DIR}/data/Th228_15_OSGI.spe
#    ${CMAKE_CURRENT_BINARY_DIR}/Th228_15_OSGI.spe
#    COPYONLY
#)
#configure_file(
#    ${CMAKE_SOURCE_DIR}/data/Cs137_15_OSGI.spe
#    ${CMAKE_CURRENT_BINARY_DIR}/Cs137_15_OSGI.spe
#    COPYONLY
#)
configure_file(
    ${CMAKE_SOURCE_DIR}/data/nuclidelibrary.json
    ${CMAKE_CURRENT_BINARY_DIR}/nuclidelibrary.json
    COPYONLY
)

# Package
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
