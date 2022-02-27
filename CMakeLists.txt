# CMAKE VERSION
cmake_minimum_required(VERSION 3.5)

# PROJECT
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(PROJECT_NAME "analyzer" CACHE STRING "Project name")
project(${PROJECT_NAME} VERSION ${PROJECT_VESRION})

# SOURCES
set(
    SOURCES
        analyzer.cpp
)

# HEADERS
set (
    HEADERS
        types.h
        idao.h
        iview.h
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

