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
endif(WIN32)
if (UNIX)
    set(QWT_INCLUDE_DIR "/usr/local/qwt-6.1.5/include")
    set(QWT_LIBRARY "/usr/local/qwt-6.1.5/lib/libqwt.so")
endif(UNIX)

# Sources
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/detector)
file(GLOB SOURCES
    main.cpp
    model/*.cpp
    view/*.cpp
    ctrl/*.cpp
    ../simulator/*.cpp
    ../utils/graph/*.cpp
    ../utils/nuclidelibrary/*.cpp
    ../utils/matlab/*.cpp
    ../utils/udp/client.cpp
    ../utils/*.cpp
)
file(GLOB HEADERS
    model/*.h
    view/*.h
    ctrl/*.h
    ../simulator/*.h
    ../utils/graph/*.h
    ../utils/nuclidelibrary/*.h
    ../utils/matlab/*.h
    ../utils/udp/client.h
    ../utils/*.h
)
add_executable(detector ${SOURCES} ${HEADERS})

# Properties
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
            ${Boost_INCLUDE_DIR}
)

target_link_libraries(
    detector
        PRIVATE
            Qt${QT_VERSION_MAJOR}::Widgets
            ${QWT_LIBRARY}
            ${Boost_LIBRARIES}
            wsock32
            ws2_32
)

# Compiler options
target_compile_options(
    detector
        PRIVATE
            -Wall -Wextra -pedantic -Werror
)

# Package
install(TARGETS detector RUNTIME DESTINATION bin)


