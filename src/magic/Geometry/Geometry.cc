/*
 * (C) Copyright 2019-2019.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include <string>
#include <numeric>
#include "eckit/config/Configuration.h"
#include "eckit/exception/Exceptions.h"
#include "oops/util/Logger.h"
#include "magic/Fortran.h"
#include "magic/Geometry/GeometryFortran.h"
#include "magic/Geometry/Geometry.h"

using oops::Log;

// -----------------------------------------------------------------------------
namespace magic {
// -----------------------------------------------------------------------------
  Geometry::Geometry(const eckit::Configuration & conf,
                     const eckit::mpi::Comm & comm)
    : comm_(comm) {
    const eckit::Configuration * configc = &conf;

    grid_ = atlas::Grid(conf);

    Log::info() << "Geometry::Geometry Grid Name:        "
                << grid_.name() << std::endl;
    Log::info() << "Geometry::Geometry Number of Points: "
                << grid_.size() << std::endl;
    Log::info() << "Geometry::Geometry Grid nx, ny: "
                << grid_.nxmax() << ", " << grid_.ny() << std::endl;
    Log::info() << "Geometry::Geometry Grid y: "
                << grid_.y() << std::endl;
    Log::info() << "Geometry::Geometry Grid Projection Units: "
                << grid_.projection().units() << std::endl;

    Log::info() << "Geometry::Geometry Domain: " << grid_.domain()
                << std::endl;
    Log::info() << "Geometry::Geometry Periodic: " << grid_.periodic()
                << std::endl;
    Log::info() << "Geometry::Geometry Spec: " << grid_.spec()
                << std::endl;

    atlas::StructuredMeshGenerator meshgenerator;
    try {
        mesh_ = meshgenerator.generate(grid_);
    }
    catch ( eckit::Exception& e ) {
        Log::error() << e.what() << std::endl;
        Log::error() << e.callStack() << std::endl;
        throw e;
    }

    Log::info() << "Geometry::Geometry mesh footprint: "
                << mesh_.footprint() << std::endl;

    nLevs_ = conf.getInt("levels", 0.);
    std::vector<double> z(nLevs_);
    std::iota(std::begin(z), std::end(z), 0);
    ak_ = conf.getDoubleVector("ak");
    bk_ = conf.getDoubleVector("bk");

    vcoord_ = atlas::Vertical(nLevs_, z);

    Log::info() << "Geometry::Geometry (min, max) level: "
                << vcoord_.min() << ", "<< vcoord_.max() << std::endl;

    magic_geo_setup_f90(keyGeom_, &configc);
  }
// -----------------------------------------------------------------------------
  Geometry::Geometry(const Geometry & other)
    : comm_(other.comm_) {

    grid_ = other.grid_;
    mesh_ = other.mesh_;
    nLevs_ = other.nLevs_;
    ak_ = other.ak_;
    bk_ = other.bk_;
    vcoord_ = other.vcoord_;

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
