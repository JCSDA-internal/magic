/*
 * (C) Copyright 2019-2019.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef MAGIC_INCREMENT_INCREMENT_H_
#define MAGIC_INCREMENT_INCREMENT_H_

#include <ostream>
#include <string>
#include <vector>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "oops/base/GeneralizedDepartures.h"
#include "oops/base/Variables.h"
#include "oops/util/DateTime.h"
#include "oops/util/dot_product.h"
#include "oops/util/Duration.h"
#include "oops/util/ObjectCounter.h"
#include "oops/util/Printable.h"

#include "magic/Geometry/Geometry.h"
#include "magic/State/State.h"

namespace eckit {
  class Configuration;
}

namespace ufo {
  class GeoVaLs;
  class Locations;
}

namespace oops {
  class Variables;
}

namespace magic {
  class Geometry;
  class State;

// -----------------------------------------------------------------------------
/// Increment handles the increment to the model state

class Increment : public oops::GeneralizedDepartures,
                  public util::Printable,
                  private util::ObjectCounter<Increment> {
 public:
  static const std::string classname() {return "magic::Increment";}

/// Constructor, destructor
  Increment(const Geometry &, const oops::Variables &, const util::DateTime &);
  Increment(const Geometry &, const Increment &);
  Increment(const Increment &, const bool);
  Increment(const Increment &);
  virtual ~Increment();

/// Basic operators
  void diff(const State &, const State &);
  void zero();
  void zero(const util::DateTime &);
  Increment & operator =(const Increment &);
  Increment & operator+=(const Increment &);
  Increment & operator-=(const Increment &);
  Increment & operator*=(const double &);
  void axpy(const double &, const Increment &, const bool check = true);
  double dot_product_with(const Increment &) const;
  void schur_product_with(const Increment &);
  void random();
  void dirac(const eckit::Configuration &);

/// I/O and diagnostics
  void read(const eckit::Configuration &);
  void write(const eckit::Configuration &) const;
  double norm() const;

/// Other
  void accumul(const double &, const State &);
  void jnormgrad(const State &, const eckit::Configuration &);

// Utilities
  boost::shared_ptr<const Geometry> geometry() const {return geom_;}

  void updateTime(const util::Duration & dt) {time_ += dt;}
  const util::DateTime & time() const {return time_;}
  util::DateTime & time() {return time_;}
  const util::DateTime & validTime() const {return time_;}
  util::DateTime & validTime() {return time_;}

  int & toFortran() {return keyInc_;}
  const int & toFortran() const {return keyInc_;}

// Private methods and variables
 private:
  void print(std::ostream &) const;
  F90inc keyInc_;
  boost::shared_ptr<const Geometry> geom_;
  oops::Variables vars_;
  util::DateTime time_;
};
// -----------------------------------------------------------------------------

}  // namespace magic

#endif  // MAGIC_INCREMENT_INCREMENT_H_
