cmake_minimum_required ( VERSION 3.2.0 )
project ( Flatland )

option( BUILD_TESTS OFF "Build unit tests created with gmock/gtest framework"  )

# namespace used for project
set ( PROJECT_NAMESPACE rel )

# The version number.
set ( PROJECT_VERSION_MAJOR 1 )
set ( PROJECT_VERSION_MINOR 0 )
set ( PROJECT_VERSION_PATCH 0 )

# required before DefaultProjectLibrary.cmake
set( SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )

# other paths
set( SHARED_PATH ${PROJECT_SOURCE_DIR}/shared )
set( RES_PATH    ${PROJECT_SOURCE_DIR}/res    )
set( SHADER_PATH ${SHARED_PATH}/shaders       )


set( PROJECT_CONFIG_FILE ${SHARED_PATH}/src/common/ProjectConfig.hpp.in )


set( USE_GLFW   ON CACHE BOOL "" FORCE )
set( USE_GLM    ON CACHE BOOL "" FORCE )
set( USE_OPENGL ON CACHE BOOL "" FORCE )
set( USE_GUI    ON CACHE BOOL "" FORCE )

set( USE_GMOCK ${BUILD_TESTS} CACHE BOOL "" FORCE )


# set variables from shared simulation project
add_subdirectory( ${SHARED_PATH} )

# header dirs
set( PROJECT_INCLUDE_DIRS ${SRC_DIR} )

# cpp files
set(
    PROJECT_SOURCE

    # ignored by compilers but added to project files
    ${SHARED_UNCRUSTIFY_FILE}
    ${RES_PATH}/shaders/grid/shader.vert
    ${RES_PATH}/shaders/grid/shader.frag
    ${RES_PATH}/shaders/entity/shader.vert
    ${RES_PATH}/shaders/entity/shader.frag

    ${SRC_DIR}/world/RelativityWorld.hpp
    ${SRC_DIR}/world/RelativityWorld.cpp
    ${SRC_DIR}/world/RelativityEntity.hpp
    ${SRC_DIR}/world/RelativityEntity.cpp

    ${SRC_DIR}/io/RelativityIOHandler.hpp
    ${SRC_DIR}/io/RelativityIOHandler.cpp
    ${SRC_DIR}/io/Grid.hpp
    ${SRC_DIR}/io/Grid.cpp
    )

if ( ${BUILD_TESTS} )

  set(
      TESTING_SOURCE
      ${SRC_DIR}/testing/EmptyUnitTests.cpp
      )

  list( APPEND TESTING_INCLUDE_DIRS ${SRC_DIR} )

endif( ${BUILD_TESTS} )


# file with main function
set( PROJECT_MAIN ${SRC_DIR}/exec/Relativity.cpp )

set ( FORCE_CUDA_STANDARD 11 )
set ( FORCE_CPP_STANDARD  14 )
include( ${SHARED_PATH}/cmake/DefaultProjectLibrary.cmake )

