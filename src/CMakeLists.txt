# (C) Copyright 2019-2019.
#
# This software is licensed under the terms of the Apache Licence Version 2.0
# which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

#add_subdirectory( magic )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

list( APPEND magic_src_files
# Geometry
magic/Geometry/Geometry.cc
magic/Geometry/Geometry.h
magic/Geometry/GeometryFortran.h
magic/Geometry/magic_geom.interface.F90
magic/Geometry/magic_geom_mod.f90

# Fields
#magic/Fields/Fields.cc
#magic/Fields/Fields.h
#magic/Fields/FieldsFortran.h

# State
magic/State/State.cc
magic/State/State.h

# Increment
magic/Increment/Increment.cc
magic/Increment/Increment.h

# IO
magic/IO/NetCDFIO.cc
magic/IO/NetCDFIO.h

magic/Traits.h
magic/Fortran.h
)

ecbuild_add_library( TARGET             ${PROJECT_NAME}
                     SOURCES            ${magic_src_files}
                     INSTALL_HEADERS    LISTED
                     HEADER_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
                     LINKER_LANGUAGE    CXX
                    )

target_compile_features( ${PROJECT_NAME} PUBLIC cxx_std_11 )
if(OpenMP_Fortran_FOUND)
  target_link_libraries( ${PROJECT_NAME} PUBLIC OpenMP::OpenMP_Fortran )
endif()
if(OpenMP_CXX_FOUND)
  target_link_libraries( ${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX )
endif()

target_link_libraries( ${PROJECT_NAME} PUBLIC NetCDF::NetCDF_C NetCDF::NetCDF_CXX NetCDF::NetCDF_Fortran )
#target_link_libraries( ${PROJECT_NAME} PUBLIC MPI::MPI_Fortran MPI::MPI_CXX )
target_link_libraries( ${PROJECT_NAME} PUBLIC ${LAPACK_LIBRARIES} )
target_link_libraries( ${PROJECT_NAME} PUBLIC Eigen3::Eigen )
target_link_libraries( ${PROJECT_NAME} PUBLIC Boost::boost )
target_link_libraries( ${PROJECT_NAME} PUBLIC eckit eckit_mpi )
target_link_libraries( ${PROJECT_NAME} PUBLIC fckit )
target_link_libraries( ${PROJECT_NAME} PUBLIC atlas atlas_f )
target_link_libraries( ${PROJECT_NAME} PUBLIC oops )
target_link_libraries( ${PROJECT_NAME} PUBLIC ufo )

target_include_directories( ${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                                                      $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

ecbuild_add_test( TARGET magic_coding_norms
                  TYPE SCRIPT
                  COMMAND ${CMAKE_BINARY_DIR}/bin/cpplint.py
                  ARGS --quiet --recursive ${CMAKE_CURRENT_SOURCE_DIR}
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
