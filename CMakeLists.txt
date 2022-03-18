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
endif(UNIX)

# Sources
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/model)
include_directories(${CMAKE_SOURCE_DIR}/src/view)
include_directories(${CMAKE_SOURCE_DIR}/src/ctrl)
include_directories(${CMAKE_SOURCE_DIR}/src/dao)
include_directories(${CMAKE_SOURCE_DIR}/src/utils)

file(GLOB SOURCES
    src/*.cpp
    src/model/*.cpp
    src/view/*.cpp
    src/ctrl/*.cpp
    src/dao/*.cpp
    src/utils/*.cpp
    src/sim/*.cpp
)

file(GLOB HEADERS
    src/*.h
    src/model/*.h
    src/view/*.h
    src/ctrl/*.h
    src/dao/*.h
    src/utils/*.h
    src/sim/*.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Properties
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

# Copy files from source directory to destination directory, substituting any
# variables.  Create destination directory if it does not exist.
macro(configure_files srcDir destDir)
    message(STATUS "Configuring directory ${destDir}")
    make_directory(${destDir})

    file(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${destDir}/${templateFile}
                    COPYONLY)
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(configure_files)

configure_files(${CMAKE_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)
configure_files(${CMAKE_SOURCE_DIR}/ml/saved_model ${CMAKE_CURRENT_BINARY_DIR}/data/saved_model)
configure_files(${CMAKE_SOURCE_DIR}/ml/saved_model/assets ${CMAKE_CURRENT_BINARY_DIR}/data/saved_model/assets)
configure_files(${CMAKE_SOURCE_DIR}/ml/saved_model/variables ${CMAKE_CURRENT_BINARY_DIR}/data/saved_model/variables)

# Package
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

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
add_executable(
    test_convneuralnet
        tests/test_convneuralnet.cpp
        src/model/convneuralnet.cpp
        src/utils/utils.cpp
        )
add_executable(
    test_utilsmath
        tests/test_utilsmath.cpp
        src/utils/mathutils.cpp
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

set(TF_LIBRARY_DLL "tensorflow.dll")
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
add_test(test_convneuralnet test_convneuralnet)
add_test(test_utilsmath test_utilsmath)

