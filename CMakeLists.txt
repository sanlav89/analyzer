# CMAKE VERSION
cmake_minimum_required(VERSION 3.5)

# PROJECT
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(PROJECT_NAME "cnn_analyzer" CACHE STRING "Project name")
project(${PROJECT_NAME} VERSION ${PROJECT_VESRION})

# Subprojects
add_subdirectory(src/analyzer analyzer)
add_subdirectory(src/detector detector)
add_subdirectory(tests)

# ------------------------------------------------------------------------------
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

set(TF_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/tensorflow/include/)
set(TF_LIBRARY ${CMAKE_SOURCE_DIR}/tensorflow/lib/tensorflow.lib)
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
