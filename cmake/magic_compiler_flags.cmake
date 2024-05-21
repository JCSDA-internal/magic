# (C) Copyright 2019- NOAA/NWS/NCEP/EMC

if( NOT CMAKE_BUILD_TYPE MATCHES "Debug" )
  add_definitions( -DNDEBUG )
endif( )

#######################################################################################
# Fortran
#######################################################################################

if( CMAKE_Fortran_COMPILER_ID MATCHES "GNU" )
  include( compiler_flags_GNU_Fortran )
elseif( CMAKE_Fortran_COMPILER_ID MATCHES "Intel" )
  include( compiler_flags_Intel_Fortran )
else()
  message( STATUS "Fortran compiler with ID ${CMAKE_CXX_COMPILER_ID} will be used with CMake default options")
endif()

#######################################################################################
# C
#######################################################################################

# todo

#######################################################################################
# C++
#######################################################################################

if( CMAKE_CXX_COMPILER_ID MATCHES "GNU" )
  include( compiler_flags_GNU_CXX )
elseif( CMAKE_CXX_COMPILER_ID MATCHES "Intel" )
  include( compiler_flags_Intel_CXX )
else()
  message( STATUS "C++ compiler with ID ${CMAKE_CXX_COMPILER_ID} will be used with CMake default options")
endif()
