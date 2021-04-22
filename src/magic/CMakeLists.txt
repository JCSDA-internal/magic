# (C) Copyright 2019-2021 NOAA/NWS/NCEP/EMC.
#
# This software is licensed under the terms of the Apache Licence Version 2.0
# which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

list( APPEND magic_src_files
# Geometry
Geometry/Geometry.cc
Geometry/Geometry.h
#Geometry/GeometryFortran.h
#Geometry/magic_geom.interface.F90
#Geometry/magic_geom_mod.f90

# Fields
Fields/Fields.cc
Fields/Fields.h
#Fields/FieldsFortran.h

# State
State/State.cc
State/State.h

# Increment
Increment/Increment.cc
Increment/Increment.h

# IO
IO/NetCDFIO.cc
IO/NetCDFIO.h

Traits.h
Fortran.h
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

