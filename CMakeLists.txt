################################################################################
# MAGIC - Model Agnostic Grid Interface Construct for JEDI
################################################################################

cmake_minimum_required( VERSION 3.12 FATAL_ERROR )

project( magic VERSION 0.0.1 LANGUAGES C CXX Fortran)

find_package( ecbuild 3.5 REQUIRED )
include( ecbuild_system NO_POLICY_SCOPE )
ecbuild_declare_project()

list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )
include( ${PROJECT_NAME}_compiler_flags )
include( ${PROJECT_NAME}_extra_macros )
include( GNUInstallDirs )

################################################################################
# Dependencies
################################################################################
find_package( NetCDF REQUIRED COMPONENTS C CXX Fortran )
#find_package( gsl-lite REQUIRED HINTS $ENV{gsl_list_DIR})
find_package( eckit  1.24.4   REQUIRED)
find_package( fckit  0.11.0   REQUIRED)
find_package( atlas  0.35.0   REQUIRED)
find_package( oops   1.10.0   REQUIRED)
#find_package( vader  1.7.0    REQUIRED)
#find_package( saber  1.10.0   REQUIRED)
#find_package( ioda   2.9.0    REQUIRED)
#find_package( ufo    1.10.0   REQUIRED)

################################################################################
# Sources
################################################################################

add_subdirectory( src )
add_subdirectory( test )

# Build Doxygen documentation
if( ENABLE_DOCS )
  add_subdirectory( docs )
endif()

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
