/*
 * (C) Copyright 2019-2019.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include <algorithm>
#include <string>
#include <vector>
#include <utility>

#include "eckit/config/LocalConfiguration.h"
#include "eckit/exception/Exceptions.h"

#include "oops/base/Variables.h"
#include "oops/util/DateTime.h"
#include "oops/util/Duration.h"
#include "oops/util/Logger.h"

#include "ufo/GeoVaLs.h"
#include "ufo/Locations.h"

#include "magic/Geometry/Geometry.h"
// #include "magic/Increment/Increment.h"
#include "magic/State/State.h"

using oops::Log;

namespace magic {

// -----------------------------------------------------------------------------
/// Constructor, destructor
// -----------------------------------------------------------------------------
  State::State(const Geometry & geom,
               const oops::Variables & vars,
               const util::DateTime & time)
    : geom_(new Geometry(geom)), vars_(vars), time_(time) {
    Log::trace() << "State::State created." << std::endl;
  }
// -----------------------------------------------------------------------------
  State::State(const Geometry & geom,
               const oops::Variables & vars,
               const eckit::Configuration & conf)
    : geom_(new Geometry(geom)), vars_(vars), time_(util::DateTime()) {
    Log::trace() << "State::State created by reading in." << std::endl;
  }
// -----------------------------------------------------------------------------
  State::State(const Geometry & geom,
               const State & other)
    : geom_(new Geometry(geom)), vars_(other.vars_), time_(other.time_) {
    Log::trace() << "State::State created by interpolation." << std::endl;
  }
// -----------------------------------------------------------------------------
  State::State(const State & other)
    : geom_(other.geom_), vars_(other.vars_), time_(other.time_) {
    Log::trace() << "State::State copied." << std::endl;
  }
// -----------------------------------------------------------------------------
  State::~State() {
    Log::trace() << "State::State destructed." << std::endl;
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
  void State::getValues(const ufo::Locations & locs,
                        const oops::Variables & vars,
                        ufo::GeoVaLs & gom) const {
    Log::trace() << "State::getValues starting." << std::endl;
    // fields_->getValues(locs, vars, gom);
    Log::trace() << "State::getValues done." << std::endl;
  }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// Interactions with Increments
// -----------------------------------------------------------------------------
//  State & State::operator+=(const Increment & dx) {
//    Log::trace() << "State add increment starting." << std::endl;
//    ASSERT(this->validTime() == dx.validTime());
//    ASSERT(fields_);
//    fields_->add(dx.fields());
//    Log::trace() << "State add increment done." << std::endl;
//    return *this;
//  }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// IO operations
// -----------------------------------------------------------------------------
  void State::read(const eckit::Configuration & conf) {
    Log::trace() << "State::State read started." << std::endl;
    // fields_->read(conf);
    Log::trace() << "State::State read done." << std::endl;
  }
// -----------------------------------------------------------------------------
  void State::write(const eckit::Configuration & conf) const {
    Log::trace() << "State::State write started." << std::endl;
    // fields_->write(conf);
    Log::trace() << "State::State write done." << std::endl;
  }
// -----------------------------------------------------------------------------
  void State::print(std::ostream & os) const {
    Log::info() << std::endl << "  Valid time: " << validTime();
  }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// For accumulator
// -----------------------------------------------------------------------------
  void State::zero() {
    Log::trace() << "State zeroed." << std::endl;
  }
// -----------------------------------------------------------------------------
  void State::accumul(const double & zz, const State & xx) {
    Log::trace() << "State accumululated." << std::endl;
  }
// -----------------------------------------------------------------------------
}  // namespace magic
