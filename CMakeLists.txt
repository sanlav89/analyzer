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
#find_package(Boost COMPONENTS filesystem REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})

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
)

# HEADERS
set (
    HEADERS
        types.h
        detector.h
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
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
add_executable(test_tfidentifier test_tfidentifier.cpp tfidentifier.cpp)

# PROPERTIES
set_target_properties (
    ${PROJECT_NAME}
    test_tfidentifier
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
)

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE
            Qt${QT_VERSION_MAJOR}::Widgets
            ${QWT_LIBRARY}
            ${TF_LIBRARY}
)

# Compiler options
target_compile_options(
    ${PROJECT_NAME}
        PRIVATE
            -Wall -Wextra -pedantic -Werror
)
target_compile_options(
    test_tfidentifier
        PRIVATE
            -Wall -Wextra -pedantic -Werror
)

configure_file(
    ${CMAKE_SOURCE_DIR}/data/Th228_15_OSGI.spe
    ${CMAKE_CURRENT_BINARY_DIR}/Th228_15_OSGI.spe
    COPYONLY
)
configure_file(
    ${CMAKE_SOURCE_DIR}/data/Cs137_15_OSGI.spe
    ${CMAKE_CURRENT_BINARY_DIR}/Cs137_15_OSGI.spe
    COPYONLY
)
configure_file(
    ${CMAKE_SOURCE_DIR}/data/nuclidelibrary.json
    ${CMAKE_CURRENT_BINARY_DIR}/nuclidelibrary.json
    COPYONLY
)

# Package
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

### UNIT-tests
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

# Testing
enable_testing()
add_test(test_tfidentifier test_tfidentifier)
