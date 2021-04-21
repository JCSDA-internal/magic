/*
 * (C) Copyright 2019-2021 NOAA/NWS/NCEP/EMC.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef MAGIC_INCREMENT_INCREMENT_H_
#define MAGIC_INCREMENT_INCREMENT_H_

#include <memory>
#include <ostream>
#include <string>
#include <vector>

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

namespace oops {
  class Variables;
}

namespace magic {
  class Geometry;
  class State;

// -----------------------------------------------------------------------------
/// Increment handles the increment to the model state

class Increment : public util::Printable,
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

/// Serialize and deserialize
  size_t serialSize() const;
  void serialize(std::vector<double> &) const;
  void deserialize(const std::vector<double> &, size_t &);

/// Other
  void accumul(const double &, const State &);
  void jnormgrad(const State &, const eckit::Configuration &);

// Utilities
  std::shared_ptr<const Geometry> geometry() const {return geom_;}

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
  std::shared_ptr<const Geometry> geom_;
  oops::Variables vars_;
  util::DateTime time_;
};
// -----------------------------------------------------------------------------

}  // namespace magic

#endif  // MAGIC_INCREMENT_INCREMENT_H_
