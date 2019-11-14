/*
 * (C) Copyright 2019-2019.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include <string>
#include "eckit/config/Configuration.h"
#include "oops/util/Logger.h"
#include "magic/Fortran.h"
#include "magic/Geometry/GeometryFortran.h"
#include "magic/Geometry/Geometry.h"

// -----------------------------------------------------------------------------
namespace magic {
// -----------------------------------------------------------------------------
  Geometry::Geometry(const eckit::Configuration & conf,
                     const eckit::mpi::Comm & comm)
    : comm_(comm) {
    const eckit::Configuration * configc = &conf;
    magic_geo_setup_f90(keyGeom_, &configc);
  }
// -----------------------------------------------------------------------------
  Geometry::Geometry(const Geometry & other)
    : comm_(other.comm_) {
    const int key_geo = other.keyGeom_;
    magic_geo_clone_f90(key_geo, keyGeom_);
  }
// -----------------------------------------------------------------------------
  Geometry::~Geometry() {
    magic_geo_delete_f90(keyGeom_);
  }
// -----------------------------------------------------------------------------
  void Geometry::print(std::ostream & os) const {
    magic_geo_info_f90(keyGeom_);
  }
// -----------------------------------------------------------------------------
}  // namespace magic
