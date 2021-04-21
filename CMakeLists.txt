# (C) Copyright 2019-2021 NOAA/NWS/NCEP/EMC.
#
# This software is licensed under the terms of the Apache Licence Version 2.0
# which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

################################################################################
# MAGIC - Model Agnostic Grid Interface Construct for JEDI
################################################################################

cmake_minimum_required( VERSION 3.3.2 FATAL_ERROR )

project( magic VERSION 0.0.1 LANGUAGES C CXX Fortran)

find_package( ecbuild 3.5 REQUIRED )

include( ecbuild_system NO_POLICY_SCOPE )
ecbuild_declare_project()

list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

option( ENABLE_MKL "Use MKL for LAPACK implementation (if available)" ON )

set( ECBUILD_DEFAULT_BUILD_TYPE Release )

include( ${PROJECT_NAME}_compiler_flags )
include( ${PROJECT_NAME}_extra_macros )
include( GNUInstallDirs )

################################################################################
# Dependencies
################################################################################

if( ENABLE_MKL )
    find_package( MKL )
endif()
if( MKL_FOUND )
    set( LAPACK_LIBRARIES ${MKL_LIBRARIES} )
else()
    find_package( LAPACK REQUIRED )
endif()

find_package( Eigen3 REQUIRED NO_MODULE HINTS
    $ENV{Eigen3_ROOT} $ENV{EIGEN3_ROOT} $ENV{Eigen_ROOT} $ENV{EIGEN_ROOT}
    $ENV{Eigen3_PATH} $ENV{EIGEN3_PATH} $ENV{Eigen_PATH} $ENV{EIGEN_PATH})
find_package( OpenMP COMPONENTS CXX Fortran )
find_package( MPI REQUIRED COMPONENTS C CXX Fortran )
find_package( NetCDF REQUIRED COMPONENTS C CXX Fortran )
find_package( Boost 1.64.0 REQUIRED)
find_package( eckit 1.11.6 REQUIRED COMPONENTS MPI )
find_package( fckit 0.7.0 REQUIRED )
if(OpenMP_FOUND)
    find_package( atlas 0.20.2 REQUIRED COMPONENTS OMP OMP_Fortran )
else()
    find_package( atlas 0.20.2 REQUIRED )
endif()
find_package( saber 0.0.1 REQUIRED )
find_package( oops 0.0.1 REQUIRED )
find_package( ioda 0.0.1 REQUIRED )
find_package( ufo  0.0.1 REQUIRED )

################################################################################
# Sources
################################################################################

add_subdirectory( src )
add_subdirectory( test )

# Build Doxygen documentation
#add_subdirectory( doc )

if( ECBUILD_INSTALL_FORTRAN_MODULES )
  install( DIRECTORY ${CMAKE_Fortran_MODULE_DIRECTORY}/${CMAKE_CFG_INTDIR} DESTINATION ${INSTALL_INCLUDE_DIR} )
endif()

################################################################################
# Finalise configuration
################################################################################

# prepares a tar.gz of the sources and/or binaries
ecbuild_install_project( NAME ${PROJECT_NAME} )

# print the summary of the configuration
ecbuild_print_summary()
