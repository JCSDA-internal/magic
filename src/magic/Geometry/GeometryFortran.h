/*
 * (C) Copyright 2019-2021 NOAA/NWS/NCEP/EMC.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef MAGIC_GEOMETRY_GEOMETRYFORTRAN_H_
#define MAGIC_GEOMETRY_GEOMETRYFORTRAN_H_

#include "magic/Fortran.h"

// Forward declarations
namespace eckit {
  class Configuration;
}

namespace util {
  class DateTime;
  class Duration;
}

namespace magic {
  extern "C" {
    void magic_geo_setup_f90(F90geom &, const eckit::Configuration * const *);
    void magic_geo_clone_f90(const F90geom &, F90geom &);
    void magic_geo_info_f90(const F90geom &);
    void magic_geo_delete_f90(F90geom &);
  }
}  // namespace magic
#endif  // MAGIC_GEOMETRY_GEOMETRYFORTRAN_H_
