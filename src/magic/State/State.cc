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

#include "magic/Fields/Fields.h"
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
               const util::DateTime & vt)
    : fields_(new Fields(geom, vars, vt)), stash_() {
    Log::trace() << "State::State created." << std::endl;
  }
// -----------------------------------------------------------------------------
  State::State(const Geometry & geom,
               const oops::Variables & vars,
               const eckit::Configuration & file) {
    fields_.reset(new Fields(geom, vars, util::DateTime()));
    fields_->read(file);
    ASSERT(fields_);
    Log::trace() << "State::State created and read in." << std::endl;
  }
// -----------------------------------------------------------------------------
  State::State(const Geometry & geom, const State & other)
    : fields_(new Fields(*other.fields_, geom)), stash_() {
    ASSERT(fields_);
    Log::trace() << "State::State created by interpolation." << std::endl;
  }
// -----------------------------------------------------------------------------
  State::State(const State & other)
    : fields_(new Fields(*other.fields_)), stash_() {
    ASSERT(fields_);
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
    ASSERT(fields_);
    *fields_ = *rhs.fields_;
    return *this;
  }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// Interpolate to observation location
// -----------------------------------------------------------------------------
  void State::getValues(const ufo::Locations & locs,
                        const oops::Variables & vars,
                        ufo::GeoVaLs & cols) const {
    fields_->getValues(locs, vars, cols);
  }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// Interactions with Increments
// -----------------------------------------------------------------------------
//  State & State::operator+=(const Increment & dx) {
//    ASSERT(this->validTime() == dx.validTime());
//    ASSERT(fields_);
//    fields_->add(dx.fields());
//    return *this;
//  }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// IO operations
// -----------------------------------------------------------------------------
  void State::read(const eckit::Configuration & files) {
    Log::trace() << "State::State read started." << std::endl;
    fields_->read(files);
    Log::trace() << "State::State read done." << std::endl;
  }
// -----------------------------------------------------------------------------
  void State::write(const eckit::Configuration & files) const {
    fields_->write(files);
  }
// -----------------------------------------------------------------------------
  void State::print(std::ostream & os) const {
    os << std::endl << "  Valid time: " << validTime();
    os << *fields_;
  }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
/// For accumulator
// -----------------------------------------------------------------------------
  void State::zero() {
    fields_->zero();
  }
// -----------------------------------------------------------------------------
  void State::accumul(const double & zz, const State & xx) {
    fields_->axpy(zz, *xx.fields_);
  }
// -----------------------------------------------------------------------------
}  // namespace magic
