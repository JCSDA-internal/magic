# (C) Copyright 2019-2019.
#
# This software is licensed under the terms of the Apache Licence Version 2.0
# which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

list( APPEND magic_src_files
# Geometry
Geometry/Geometry.cc
Geometry/Geometry.h
Geometry/GeometryFortran.h
Geometry/magic_geom.interface.F90
Geometry/magic_geom_mod.f90

# Fields
#Fields/Fields.cc
#Fields/Fields.h
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

ecbuild_add_library( TARGET   magic
                     SOURCES  ${magic_src_files}
                     LIBS     ${LAPACK_LIBRARIES} ${NETCDF_LIBRARIES}
                              eckit eckit_mpi fckit atlas atlas_f saber oops ioda ufo
                     INSTALL_HEADERS LISTED
                     LINKER_LANGUAGE ${MAGIC_LINKER_LANGUAGE}
                    )
