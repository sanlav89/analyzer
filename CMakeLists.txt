# CMAKE VERSION
cmake_minimum_required(VERSION 3.5)

## PROJECT
set(PROJECT_NAME "analyzer" CACHE STRING "Project name")
project(${PROJECT_NAME})

# SUBDIRECTORIES
add_subdirectory(${PROJECT_NAME})
add_subdirectory(tests)
