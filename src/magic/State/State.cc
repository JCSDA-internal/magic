/*
 * (C) Copyright 2019-2019.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "eckit/config/LocalConfiguration.h"
#include "eckit/exception/Exceptions.h"

#include "oops/base/Variables.h"
#include "oops/util/DateTime.h"
#include "oops/util/Duration.h"
#include "oops/util/Logger.h"

// #include "ufo/GeoVaLs.h"
// #include "ufo/Locations.h"

#include "magic/Geometry/Geometry.h"
#include "magic/Increment/Increment.h"
#include "magic/State/State.h"

namespace magic {

// -----------------------------------------------------------------------------
/// Constructor, destructor
// -----------------------------------------------------------------------------
  State::State(const Geometry & geom,
               const oops::Variables & vars,
               const util::DateTime & time)
    : geom_(new Geometry(geom)), vars_(vars), time_(time) {
    oops::Log::trace() << "State::State created." << std::endl;
  }
// -----------------------------------------------------------------------------
  State::State(const Geometry & geom,
               const eckit::Configuration & conf)
    : geom_(new Geometry(geom)), time_(util::DateTime()) {
    oops::Log::trace() << "State::State created by reading in." << std::endl;
  }
// -----------------------------------------------------------------------------
  State::State(const Geometry & geom,
               const State & other)
    : geom_(new Geometry(geom)), vars_(other.vars_), time_(other.time_) {
    oops::Log::trace() << "State::State created by interpolation." << std::endl;
  }
// -----------------------------------------------------------------------------
  State::State(const State & other)
    : geom_(other.geom_), vars_(other.vars_), time_(other.time_) {
    oops::Log::trace() << "State::State copied." << std::endl;
  }
// -----------------------------------------------------------------------------
  State::~State() {
    oops::Log::trace() << "State::State destructed." << std::endl;
  }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// Basic operators
// -----------------------------------------------------------------------------
  State & State::operator=(const State & rhs) {
    time_ = rhs.time_;
    return *this;
  }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// Interpolate to observation location
// -----------------------------------------------------------------------------
//  void State::getValues(const ufo::Locations & locs,
//                        const oops::Variables & vars,
//                        ufo::GeoVaLs & gom) const {
//    oops::Log::trace() << "State::getValues starting." << std::endl;
//    // fields_->getValues(locs, vars, gom);
//    oops::Log::trace() << "State::getValues done." << std::endl;
//  }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// Interactions with Increments
// -----------------------------------------------------------------------------
  State & State::operator+=(const Increment & dx) {
    oops::Log::trace() << "State add increment starting." << std::endl;
    ASSERT(this->validTime() == dx.validTime());
//    ASSERT(fields_);
//    fields_->add(dx.fields());
    oops::Log::trace() << "State add increment done." << std::endl;
    return *this;
  }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// IO operations
// -----------------------------------------------------------------------------
  void State::read(const eckit::Configuration & conf) {
    oops::Log::trace() << "State::State read started." << std::endl;
    // fields_->read(conf);
    oops::Log::trace() << "State::State read done." << std::endl;
  }
// -----------------------------------------------------------------------------
  void State::write(const eckit::Configuration & conf) const {
    oops::Log::trace() << "State::State write started." << std::endl;
    // fields_->write(conf);
    oops::Log::trace() << "State::State write done." << std::endl;
  }
// -----------------------------------------------------------------------------
  void State::print(std::ostream & os) const {
    oops::Log::info() << std::endl << "  Valid time: " << validTime();
  }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// Serialize and deserialize
// -----------------------------------------------------------------------------
size_t State::serialSize() const {
  oops::Log::trace() << "State::serialSize starting" << std::endl;
  size_t nn = 1;
  int sz = 0;
  nn += sz;
  nn += time_.serialSize();
  return nn;
  oops::Log::trace() << "State::serialSize done" << std::endl;
}
// -----------------------------------------------------------------------------
void State::serialize(std::vector<double> & vect) const {
  oops::Log::trace() << "State::serialize starting" << std::endl;
  int size_fld = this->serialSize() - 3;
  std::vector<double> v_fld(size_fld, 0);

  vect.insert(vect.end(), v_fld.begin(), v_fld.end());

  // Serialize the date and time
  vect.push_back(-54321.98765);
  time_.serialize(vect);

  oops::Log::trace() << "State::serialize done" << std::endl;
}
// -----------------------------------------------------------------------------
void State::deserialize(const std::vector<double> & vect, size_t & index) {
  oops::Log::trace() << "State::deserialize starting" << std::endl;

  ASSERT(vect.at(index) == -54321.98765);
  ++index;

  time_.deserialize(vect, index);
  oops::Log::trace() << "State::deserialize done" << std::endl;
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// For accumulator
// -----------------------------------------------------------------------------
  void State::zero() {
    oops::Log::trace() << "State zeroed." << std::endl;
  }
// -----------------------------------------------------------------------------
  void State::accumul(const double & zz, const State & xx) {
    oops::Log::trace() << "State accumululated." << std::endl;
  }
// -----------------------------------------------------------------------------
  double State::norm() const {
    oops::Log::trace() << "State norm starting." << std::endl;
    double zz = 0.0;
    return zz;
    oops::Log::trace() << "State norm done." << std::endl;
  }
// -----------------------------------------------------------------------------
}  // namespace magic
