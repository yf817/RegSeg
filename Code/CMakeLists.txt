cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
#######################################

if(UNIX)
#    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    #SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS ")
endif()

FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR
          "Please Set ITK_DIR")
ENDIF(ITK_FOUND)


FIND_PACKAGE( Boost 1.49 COMPONENTS program_options filesystem system REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

FIND_PATH(JsonCpp_INCLUDE_DIR     
  NAMES 
        jsoncpp/json/json.h   
  PATHS
        /usr/local/include
        /usr/include
)
INCLUDE_DIRECTORIES(${JsonCpp_INCLUDE_DIR})

find_library(JsonCpp_LIBRARY 
    NAMES 
        jsoncpp
        libjsoncpp
    PATHS
       /usr/lib 
       /usr/local/lib
)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

SET( CORE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Core )
SET( ITKRV_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Modules/ITKReviewed )
SET( IO_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Modules/IO )

SET( OBSERVERS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Observers )
SET( OBSERVERS_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Modules/Functional )

SET( FUNCTIONAL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Functional )
SET( FUNCTIONAL_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Modules/Functional )

SET( OPTIMIZERS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Optimizers )
SET( OPTIMIZERS_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Modules/Optimizers )

SET( TRANSFORM_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Transform )
SET( TRANSFORM_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Modules/Transform )

SET( FILTERING_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Filtering )
SET( FILTERING_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Modules/Filtering )

SET( VTKHAUSSDORF_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Hausdorff )
SET( VTKHAUSSDORF_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/Hausdorff )

INCLUDE_DIRECTORIES( ${OPTIMIZERS_SOURCE_DIR}/include
                     ${FUNCTIONAL_SOURCE_DIR}/include
                     ${FILTERING_SOURCE_DIR}/include
                     ${TRANSFORM_SOURCE_DIR}/include
                     ${IO_SOURCE_DIR}/include
                     ${OBSERVERS_SOURCE_DIR}/include
                     ${CORE_SOURCE_DIR}/include
                     ${ITKRV_SOURCE_DIR}/include
                     ${VTKHAUSSDORF_SOURCE_DIR}
)

ENABLE_TESTING()


ADD_SUBDIRECTORY( Modules/Core )

ADD_SUBDIRECTORY( ThirdParty/Hausdorff )
SET( VTKHAUSDORFF_LIB "vtkHausdorffDistance" )

ADD_SUBDIRECTORY( Modules/Observers )
SET( OBSERVERS_LIB "RSTKFunctional" )


ADD_SUBDIRECTORY( Modules/Functional )
SET( FUNCTIONAL_LIB "RSTKFunctional" )

ADD_SUBDIRECTORY( Modules/Optimizers )
SET( OPTIMIZERS_LIB "RSTKOptimizers" )

ADD_SUBDIRECTORY( Modules/Transform )
SET( TRANSFORM_LIB "RSTKTransform" )

ADD_SUBDIRECTORY( Modules/Filtering )
SET( FILTERING_LIB "RSTKFiltering" )

ADD_SUBDIRECTORY( Examples/ )

ADD_SUBDIRECTORY( Applications/ )

#######################################
# if(WIN32 OR NOT EXISTS /dev/urandom)
#   cmake_minimum_required(VERSION 2.8.5)
# endif()
# 
# project(ACWERegistration)
# 
# if( WIN32 )
#   string( LENGTH "${CMAKE_CURRENT_SOURCE_DIR}" n )
#   if( n GREATER 50 )
#     message(
#       FATAL_ERROR
#       "ACWERegistration source code directory path length is too long (${n} > 50)."
#       "Please move the ACWERegistration source code directory to a directory with a shorter path."
#       )
#   endif()
# 
#   string( LENGTH "${CMAKE_CURRENT_BINARY_DIR}" n )
#   if( n GREATER 50 )
#     message(
#       FATAL_ERROR
#       "ACWERegistration build directory path length is too long (${n} > 50)."
#       "Please set the ACWERegistration build directory to a directory with a shorter path."
#       )
#   endif()
# endif()
# 
# 
# set( CMAKE_MODULE_PATH /home/oesteban/workspace/ITK/src/CMake ${CMAKE_MODULE_PATH} )
# include(ITKModuleMacros)
# 
# SET (RSTK_VERSION_MAJOR 0)
# SET (RSTK_VERSION_MINOR 1)
# SET (RSTK_RELEASE "0")
# 
# if(NOT RSTK_INSTALL_RUNTIME_DIR)
#   set(RSTK_INSTALL_RUNTIME_DIR bin)
# endif()
# if(NOT RSTK_INSTALL_LIBRARY_DIR)
#   set(RSTK_INSTALL_LIBRARY_DIR lib)
# endif()
# if(NOT RSTK_INSTALL_ARCHIVE_DIR)
#   set(RSTK_INSTALL_ARCHIVE_DIR lib)
# endif()
# if(NOT RSTK_INSTALL_INCLUDE_DIR)
#   set(RSTK_INSTALL_INCLUDE_DIR include/RSTK-${RSTK_VERSION_MAJOR}.${RSTK_VERSION_MINOR})
# endif()
# if(NOT RSTK_INSTALL_DATA_DIR)
#   set(RSTK_INSTALL_DATA_DIR share/RSTK-${RSTK_VERSION_MAJOR}.${RSTK_VERSION_MINOR})
# endif()
# if(NOT RSTK_INSTALL_DOC_DIR)
#   set(RSTK_INSTALL_DOC_DIR share/doc/RSTK-${RSTK_VERSION_MAJOR}.${RSTK_VERSION_MINOR})
# endif()
# if(NOT RSTK_INSTALL_PACKAGE_DIR)
#   set(RSTK_INSTALL_PACKAGE_DIR "lib/cmake/RSTK-${RSTK_VERSION_MAJOR}.${RSTK_VERSION_MINOR}")
# endif()
# 
# configure_file (
#   "${PROJECT_SOURCE_DIR}/RSTKConfig.h.in"
#   "${PROJECT_BINARY_DIR}/RSTKConfig.h"
# )
# 
# FIND_PACKAGE(ITK)
# IF(ITK_FOUND)
#   INCLUDE(${ITK_USE_FILE})
# ELSE(ITK_FOUND)
#   MESSAGE(FATAL_ERROR
#           "Please Set ITK_DIR")
# ENDIF(ITK_FOUND)
# 
# #-----------------------------------------------------------------------------
# # Set a default build type if none was specified
# if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
#   message(STATUS "Setting build type to 'Release' as none was specified.")
#   set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
#   # Set the possible values of build type for cmake-gui
#   set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
# endif()
# 
# #-----------------------------------------------------------------------------
# # RSTK build configuration options.
# option(BUILD_SHARED_LIBS "Build RSTK with shared libraries." OFF)
# set(RSTK_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
# 
# 
# message(INFO " RSTK_BINARY_DIR=${RSTK_BINARY_DIR}" )
# # Setup build locations.
# if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
#   set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RSTK_BINARY_DIR}/bin)
# endif()
# if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
#   set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RSTK_BINARY_DIR}/lib)
# endif()
# if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
#   set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RSTK_BINARY_DIR}/lib)
# endif()
# set(RSTK_MODULES_DIR "${RSTK_BINARY_DIR}/${RSTK_INSTALL_PACKAGE_DIR}/Modules")
# 
# #----------------------------------------------------------------------
# # Load the module DAG.
# set(RSTK_MODULES_ALL)
# file(GLOB meta RELATIVE "${PROJECT_SOURCE_DIR}"
#    "${PROJECT_SOURCE_DIR}/*/*/itk-module.cmake" # grouped modules
#   )
# 
# 
# foreach(f ${meta})
#   include(${PROJECT_SOURCE_DIR}/${f})
#   list(APPEND RSTK_MODULES_ALL ${itk-module})
#   get_filename_component(${itk-module}_BASE ${f} PATH)
#   set(${itk-module}_SOURCE_DIR ${PROJECT_SOURCE_DIR}/${${itk-module}_BASE})
#   message(INFO "Module detected: ${${itk-module}_SOURCE_DIR}" )
#   set(${itk-module}_BINARY_DIR ${RSTK_BINARY_DIR}/${${itk-module}_BASE})
#   if(BUILD_TESTING AND EXISTS ${${itk-module}_SOURCE_DIR}/test)
#     list(APPEND RSTK_MODULES_ALL ${itk-module-test})
#     set(${itk-module-test}_SOURCE_DIR ${${itk-module}_SOURCE_DIR}/test)
#     set(${itk-module-test}_BINARY_DIR ${${itk-module}_BINARY_DIR}/test)
#     set(${itk-module-test}_IS_TEST 1)
#     set(${itk-module}_TESTED_BY ${itk-module-test})
#     set(${itk-module-test}_TESTS_FOR ${itk-module})
#   endif()
# 
#   # Reject bad dependencies.
#   string(REGEX MATCHALL ";(RSTKDeprecated|RSTKReview|RSTKIntegratedTest);"
#     _bad_deps ";${RSTK_MODULE_${itk-module}_DEPENDS};${RSTK_MODULE_${itk-module-test}_DEPENDS};")
#   foreach(dep ${_bad_deps})
#     if(NOT "${itk-module}" MATCHES "^(${dep}|RSTKIntegratedTest)$")
#       message(FATAL_ERROR
#         "Module \"${itk-module}\" loaded from\n"
#         "  ${${itk-module}_BASE}/itk-module.cmake\n"
#         "may not depend on module \"${dep}\".")
#     endif()
#   endforeach()
# endforeach()
# # Clear variables set later in each module.
# unset(itk-module)
# unset(itk-module-test)
# 
#  
#SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS -Wunused-local-typedefs")
