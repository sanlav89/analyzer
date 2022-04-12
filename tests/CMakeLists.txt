# CMAKE VERSION
cmake_minimum_required(VERSION 3.5)

# PROJECT
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(PROJECT_NAME "cnn_analyzer" CACHE STRING "Project name")
project(${PROJECT_NAME} VERSION ${PROJECT_VESRION})

# TensorFlow
if (WIN32)
    set(TF_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/tensorflow/include/)
    set(TF_LIBRARY ${CMAKE_SOURCE_DIR}/tensorflow/lib/tensorflow.lib)
endif(WIN32)
if (UNIX)
    # TODO: set TensorFlow include path for UNIX
    # TODO: set TensorFlow library path for UNIX
endif(UNIX)

# Testing

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

# Executables

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/analyzer)

add_executable(
    test_convneuralnet
        test_convneuralnet.cpp
        ../src/analyzer/model/idf/convneuralnet.cpp
        )
add_executable(
    test_utilsmath
        test_utilsmath.cpp
        ../src/utils/matlab/matlab.cpp
        )

set_target_properties (
    test_convneuralnet
    test_utilsmath
        PROPERTIES
            CMAKE_CXX_STANDARD 17
            CMAKE_CXX_STANDARD_REQUIRED ON
)

target_compile_options(
    test_convneuralnet
        PRIVATE
            -Wall -Wextra -pedantic -Werror
)
target_compile_options(
    test_utilsmath
        PRIVATE
            -Wall -Wextra -pedantic -Werror
)

gtest_discover_tests(test_convneuralnet)
target_include_directories(test_convneuralnet PRIVATE ${TF_INCLUDE_DIR})
target_link_libraries(
    test_convneuralnet
    ${TF_LIBRARY}
    gtest_main
)
target_link_libraries(
    test_utilsmath
    gtest_main
)

# Testing
enable_testing()
add_test(test_convneuralnet test_convneuralnet)
add_test(test_utilsmath test_utilsmath)
