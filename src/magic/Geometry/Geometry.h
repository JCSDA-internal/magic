/*
 * (C) Copyright 2019-2019.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef MAGIC_GEOMETRY_GEOMETRY_H_
#define MAGIC_GEOMETRY_GEOMETRY_H_

#include <ostream>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "eckit/mpi/Comm.h"

#include "atlas/grid.h"
#include "atlas/grid/detail/grid/GridFactory.h"
#include "atlas/grid/Vertical.h"
#include "atlas/mesh/Mesh.h"
#include "atlas/meshgenerator.h"

#include "oops/util/ObjectCounter.h"
#include "oops/util/Printable.h"

#include "magic/Fortran.h"
#include "magic/Geometry/GeometryFortran.h"

namespace eckit {
  class Configuration;
}

namespace magic {

// -----------------------------------------------------------------------------
/// Geometry handles geometry.

  class Geometry : public util::Printable,
                   private util::ObjectCounter<Geometry> {
   public:
     static const std::string classname() {return "magic::Geometry";}

     explicit Geometry(const eckit::Configuration &,
                       const eckit::mpi::Comm &);
     Geometry(const Geometry &);
     ~Geometry();

     std::vector<double> getAk() const {return ak;}
     std::vector<double> getBk() const {return bk;}
     const atlas::StructuredGrid & getGrid() const {return grid_;}
     const atlas::Vertical & getVerticalCoord() const {return vcoord_;}
     const eckit::mpi::Comm & getComm() const {return comm_;}
     int& toFortran() {return keyGeom_;}
     const int& toFortran() const {return keyGeom_;}

   private:
     Geometry & operator=(const Geometry &);
     void print(std::ostream &) const;
     const eckit::mpi::Comm & comm_;
     atlas::StructuredGrid grid_;
     atlas::Vertical vcoord_;
     atlas::Mesh mesh_;
     std::vector<double> ak, bk;
     boost::shared_ptr<const Geometry> geom_;
     int keyGeom_;
  };
// -----------------------------------------------------------------------------

}  // namespace magic

#endif  // MAGIC_GEOMETRY_GEOMETRY_H_
