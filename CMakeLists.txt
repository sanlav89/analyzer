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

# SOURCES
set(
    SOURCES
        analyzer.cpp
        model.cpp
        view.cpp
)

# HEADERS
set (
    HEADERS
        types.h
        idao.h
        iview.h
        identifymethod.h
        mlidentifier.h
        simplemethod.h
        deconvmethod.h
        model.h
        nuclidelibrary.h
        view.h
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
target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE
            Qt${QT_VERSION_MAJOR}::Widgets
)

# Compiler options
target_compile_options(
    ${PROJECT_NAME} 
        PRIVATE
            -Wall -Wextra -pedantic -Werror
)

# Package
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# Testing
# enable_testing()

