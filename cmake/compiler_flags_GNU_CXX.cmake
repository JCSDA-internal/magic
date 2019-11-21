# (C) Copyright 2019-2019.
#
# This software is licensed under the terms of the Apache Licence Version 2.0
# which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

####################################################################
# FLAGS COMMON TO ALL BUILD TYPES
####################################################################

if( HAVE_OMP )
  set( CMAKE_CXX_FLAGS     "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-declarations -fopenmp")
else( )
  set( CMAKE_CXX_FLAGS     "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-declarations -fno-openmp")
endif( )

####################################################################
# RELEASE FLAGS
####################################################################

set( CMAKE_CXX_FLAGS_RELEASE     "-O3 -std=c++17" )

####################################################################
# DEBUG FLAGS
####################################################################

set( CMAKE_CXX_FLAGS_DEBUG       "-O0 -g -std=c++17" )

####################################################################
# BIT REPRODUCIBLE FLAGS
####################################################################

set( CMAKE_CXX_FLAGS_BIT         "-O2 -std=c++17" )

####################################################################
# LINK FLAGS
####################################################################

set( CMAKE_CXX_LINK_FLAGS        "" )

####################################################################

# Meaning of flags
# ----------------
# todo
