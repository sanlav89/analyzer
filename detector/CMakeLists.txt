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
set(ANALYZER_DIR ${CMAKE_SOURCE_DIR}/analyzer)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
#find_package(Boost COMPONENTS filesystem REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/analyzer)

# Qwt
if (WIN32)
    set(QWT_INCLUDE_DIR "C:/qwt-6.1.5_64/src")
    set(QWT_LIBRARY "C:/qwt-6.1.5_64/lib/qwt.dll")
endif(WIN32)
if (UNIX)
    set(QWT_INCLUDE_DIR "/usr/local/qwt-6.1.5/include")
    set(QWT_LIBRARY "/usr/local/qwt-6.1.5/lib/libqwt.so")
endif(UNIX)

# SOURCES
set(
    SOURCES
        detector.cpp
        detectorwidget.cpp
        detectorgraph.cpp
        sliderwithlabel.cpp
        mathutils.cpp
        ${ANALYZER_DIR}/nuclidelibrary.cpp
        ${ANALYZER_DIR}/graph.cpp
        ${ANALYZER_DIR}/graphcanvas.cpp
)

# HEADERS
set (
    HEADERS
        detectorwidget.h
        detectorgraph.h
        sliderwithlabel.h
        mathutils.h
        ${ANALYZER_DIR}/view.h
        ${ANALYZER_DIR}/types.h
        ${ANALYZER_DIR}/nuclidelibrary.h
        ${ANALYZER_DIR}/graph.h
        ${ANALYZER_DIR}/graphcanvas.h
)

add_executable(detector ${SOURCES} ${HEADERS})

# PROPERTIES
set_target_properties (
    detector
        PROPERTIES
            CMAKE_CXX_STANDARD 17
            CMAKE_CXX_STANDARD_REQUIRED ON
)

# Linking
target_include_directories(
    detector
        PRIVATE
            ${QWT_INCLUDE_DIR}
)

target_link_libraries(
    detector
        PRIVATE
            Qt${QT_VERSION_MAJOR}::Widgets
            ${QWT_LIBRARY}
)

# Compiler options
target_compile_options(
    detector
        PRIVATE
            -Wall -Wextra -pedantic -Werror
)

configure_file(
    ${CMAKE_SOURCE_DIR}/data/nuclidelibrary.json
    ${CMAKE_CURRENT_BINARY_DIR}/nuclidelibrary.json
    COPYONLY
)

# Package
install(TARGETS detector RUNTIME DESTINATION bin)
