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

#include "eckit/mpi/Comm.h"

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

      explicit Geometry(const eckit::Configuration &, const eckit::mpi::Comm &);
      Geometry(const Geometry &);
      ~Geometry();

      int& toFortran() {return keyGeom_;}
      const int& toFortran() const {return keyGeom_;}
      const eckit::mpi::Comm & getComm() const {return comm_;}

    private:
      Geometry & operator=(const Geometry &);
      void print(std::ostream &) const;
      int keyGeom_;
      const eckit::mpi::Comm & comm_;
  };
// -----------------------------------------------------------------------------

}  // namespace magic

#endif  // MAGIC_GEOMETRY_GEOMETRY_H_
