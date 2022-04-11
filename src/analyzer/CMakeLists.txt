# CMAKE VERSION
cmake_minimum_required(VERSION 3.5)

# PROJECT
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(PROJECT_NAME "cnn_analyzer" CACHE STRING "Project name")
project(${PROJECT_NAME} VERSION ${PROJECT_VESRION})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Packages
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
    # TODO: set TensorFlow include path for UNIX
    # TODO: set TensorFlow library path for UNIX
endif(UNIX)

# Sources
include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/src/analyzer)

file(GLOB SOURCES
    main.cpp
    model/*.cpp
    model/idf/*.cpp
    view/*.cpp
    ctrl/*.cpp
    ../simulator/*.cpp
    ../utils/graph/*.cpp
    ../utils/nuclidelibrary/*.cpp
    ../utils/matlab/*.cpp
    ../utils/recv/*.cpp
    ../utils/udp/serverthread.cpp
    ../utils/*.cpp
)
file(GLOB HEADERS
    model/*.h
    model/idf/*.h
    view/*.h
    ctrl/*.h
    ../simulator/*.h
    ../utils/graph/*.h
    ../utils/nuclidelibrary/*.h
    ../utils/matlab/*.h
    ../utils/recv/*.h
    ../utils/udp/serverthread.h
    ../utils/*.h
)
add_executable(analyzer ${SOURCES} ${HEADERS})

# Properties
set_target_properties (
    analyzer
        PROPERTIES
            CMAKE_CXX_STANDARD 17
            CMAKE_CXX_STANDARD_REQUIRED ON
)

# Linking
target_include_directories(
    analyzer
        PRIVATE
            ${QWT_INCLUDE_DIR}
            ${TF_INCLUDE_DIR}
            ${Boost_INCLUDE_DIR}
)

target_link_libraries(
    analyzer
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
    analyzer
        PRIVATE
            -Wall -Wextra -pedantic -Werror
)

# Package
install(TARGETS analyzer RUNTIME DESTINATION bin)
