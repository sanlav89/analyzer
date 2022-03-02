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

if (Qt5Gui_FOUND)
  get_target_property(QT_INCLUDE_DIR Qt5::Gui INTERFACE_INCLUDE_DIRECTORIES)
endif ()

# Qwt
set(QWT_INCLUDE_DIR "C:/qwt-6.1.5/src")
find_path ( QWT_INCLUDE_DIR
  NAMES qwt_plot.h
  HINTS ${QT_INCLUDE_DIR}
  PATH_SUFFIXES qwt qwt-qt5 qwt6
)
message("${QWT_INCLUDE_DIR}")

set ( QWT_INCLUDE_DIRS ${QWT_INCLUDE_DIR} )

# version
set ( _VERSION_FILE ${QWT_INCLUDE_DIR}/qwt_global.h )
if ( EXISTS ${_VERSION_FILE} )
  file ( STRINGS ${_VERSION_FILE} _VERSION_LINE REGEX "define[ ]+QWT_VERSION_STR" )
  if ( _VERSION_LINE )
    string ( REGEX REPLACE ".*define[ ]+QWT_VERSION_STR[ ]+\"([^\"]*)\".*" "\\1" QWT_VERSION_STRING "${_VERSION_LINE}" )
  endif ()
endif ()
unset ( _VERSION_FILE )

find_library ( QWT_LIBRARY
  NAMES qwt qwt-qt5
  HINTS ${QT_LIBRARY_DIR}
)

set ( QWT_LIBRARIES ${QWT_LIBRARY} )

include ( FindPackageHandleStandardArgs )
find_package_handle_standard_args( Qwt REQUIRED_VARS QWT_LIBRARY QWT_INCLUDE_DIR VERSION_VAR QWT_VERSION_STRING )

if (Qwt_FOUND AND NOT TARGET Qwt::Qwt)
  add_library(Qwt::Qwt UNKNOWN IMPORTED)
  set_target_properties(Qwt::Qwt PROPERTIES
                        INTERFACE_INCLUDE_DIRECTORIES "${QWT_INCLUDE_DIRS}"
                        IMPORTED_LOCATION "${QWT_LIBRARIES}")
endif ()

mark_as_advanced (
  QWT_LIBRARY
  QWT_INCLUDE_DIR
)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

#set(QWT_INCLUDE_DIR "C:/qwt-6.1.5/src")
#set(QWT_LIBRARY_DIR "C:/qwt-6.1.5/lib")

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
#add_library(qwt SHARED IMPORTED)
#set_property(TARGET qwt PROPERTY IMPORTED_LOCATION ${QWT_LIBRARY_DIR}/qwt.dll)
target_include_directories(${PROJECT_NAME} PRIVATE ${QWT_INCLUDE_DIR})
#target_include_directories(${PROJECT_NAME} PRIVATE ${QWT_LIBRARY_DIR})

#find_library(QWT_LIBRARY NAMES qwt qwt-qt5 HINTS ${QWT_LIBRARY_DIR})
#target_link_libraries(test PUBLIC ${QWT_LIBRARY})

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE
            Qt${QT_VERSION_MAJOR}::Widgets
            C:/qwt-6.1.5/lib/qwt.dll
)

message("${PROJECT_NAME}")
message("${QWT_LIBRARY}")

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

