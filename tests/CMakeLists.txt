# CMAKE VERSION
cmake_minimum_required(VERSION 3.5)

# PROJECT
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(PROJECT_NAME "analyzer" CACHE STRING "Project name")
project(${PROJECT_NAME} VERSION ${PROJECT_VESRION})
set(ANALYZER_PATH ${CMAKE_SOURCE_DIR}/analyzer)
set(TF_LIBRARY_DLL "tensorflow.dll")
set(TF_LIBRARY_LIB "tensorflow.lib")

if (WIN32)
    set(TF_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/tensorflow/include/)
    set(TF_LIBRARY ${CMAKE_SOURCE_DIR}/tensorflow/lib/${TF_LIBRARY_LIB})
endif(WIN32)

# SOURCES
set(
    SOURCES
        ${ANALYZER_PATH}/tfidentifier.h
)

# HEADERS
set (
    HEADERS
        test_tfidentifier.cpp
        ${ANALYZER_PATH}/tfidentifier.cpp
)

add_executable(test_tfidentifier ${SOURCES} ${HEADERS})
include_directories(${ANALYZER_PATH})

# PROPERTIES
set_target_properties (
    test_tfidentifier
        PROPERTIES
            CMAKE_CXX_STANDARD 17
            CMAKE_CXX_STANDARD_REQUIRED ON
)

# Compiler options
target_compile_options(
    test_tfidentifier
        PRIVATE
            -Wall -Wextra -pedantic -Werror
)

# GoogleTest package
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Tests linking
gtest_discover_tests(test_tfidentifier)
target_include_directories(test_tfidentifier PRIVATE ${TF_INCLUDE_DIR})
target_link_libraries(
    test_tfidentifier
    ${TF_LIBRARY}
    gtest_main
)

configure_file(
    ${TF_LIBRARY}
    ${CMAKE_CURRENT_BINARY_DIR}/${TF_LIBRARY_LIB}
    COPYONLY
)
configure_file(
    ${CMAKE_SOURCE_DIR}/tensorflow/lib/${TF_LIBRARY_DLL}
    ${CMAKE_CURRENT_BINARY_DIR}/${TF_LIBRARY_DLL}
    COPYONLY
)

# Testing
enable_testing()
add_test(test_tfidentifier test_tfidentifier)
