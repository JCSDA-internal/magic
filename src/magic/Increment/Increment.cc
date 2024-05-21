// (C) Copyright 2019- NOAA/NWS/NCEP/EMC

#include <algorithm>
#include <string>
#include <vector>

#include "eckit/config/LocalConfiguration.h"
#include "eckit/exception/Exceptions.h"

#include "oops/base/Variables.h"
#include "oops/util/DateTime.h"
#include "oops/util/Duration.h"
#include "oops/util/Logger.h"

//  #include "ufo/GeoVaLs.h"
//  #include "ufo/Locations.h"

#include "magic/Geometry/Geometry.h"
#include "magic/Increment/Increment.h"
#include "magic/State/State.h"

namespace magic {

// -----------------------------------------------------------------------------
/// Constructor, destructor
// -----------------------------------------------------------------------------
  Increment::Increment(const Geometry & geom,
                       const oops::Variables & vars,
                       const util::DateTime & time)
    : geom_(new Geometry(geom)), vars_(vars), time_(time) {
    oops::Log::trace() << "Increment constructed." << std::endl;
  }
// -----------------------------------------------------------------------------
  Increment::Increment(const Geometry & geom,
                       const Increment & other)
    : geom_(new Geometry(geom)), vars_(other.vars_), time_(other.time_) {
    oops::Log::trace() << "Increment constructed from other." << std::endl;
  }
// -----------------------------------------------------------------------------
  Increment::Increment(const Increment & other,
                       const bool copy)
    : geom_(other.geom_), vars_(other.vars_), time_(other.time_) {
    if (copy) {
    } else {
    }
    oops::Log::trace() << "Increment copy-created." << std::endl;
  }
// -----------------------------------------------------------------------------
  Increment::Increment(const Increment & other)
    : geom_(other.geom_), vars_(other.vars_), time_(other.time_) {
    oops::Log::trace() << "Increment copy-created." << std::endl;
  }
// -----------------------------------------------------------------------------
  Increment::~Increment() {
    oops::Log::trace() << "Increment destructed" << std::endl;
  }
// -----------------------------------------------------------------------------
/// Basic operators
// -----------------------------------------------------------------------------
  void Increment::diff(const State & x1, const State & x2) {
    ASSERT(this->validTime() == x1.validTime());
    ASSERT(this->validTime() == x2.validTime());
    // States at increment resolution
    State x1_ir(*geom_, x1);
    State x2_ir(*geom_, x2);
  }
// -----------------------------------------------------------------------------
  Increment & Increment::operator=(const Increment & rhs) {
    time_ = rhs.time_;
    return *this;
  }
// -----------------------------------------------------------------------------
  Increment & Increment::operator+=(const Increment & dx) {
    ASSERT(this->validTime() == dx.validTime());
    return *this;
  }
// -----------------------------------------------------------------------------
  Increment & Increment::operator-=(const Increment & dx) {
    ASSERT(this->validTime() == dx.validTime());
    return *this;
  }
// -----------------------------------------------------------------------------
  Increment & Increment::operator*=(const double & zz) {
    return *this;
  }
// -----------------------------------------------------------------------------
  void Increment::zero() {
  }
// -----------------------------------------------------------------------------
  void Increment::zero(const util::DateTime & vt) {
    time_ = vt;
  }
// -----------------------------------------------------------------------------
  void Increment::axpy(const double & zz,
                       const Increment & dx,
                       const bool check) {
    ASSERT(!check || this->validTime() == dx.validTime());
  }
// -----------------------------------------------------------------------------
  void Increment::accumul(const double & zz,
                          const State & xx) {
  }
// -----------------------------------------------------------------------------
  void Increment::schur_product_with(const Increment & dx) {
  }
// -----------------------------------------------------------------------------
  double Increment::dot_product_with(const Increment & other) const {
    double zz = 0;
    return zz;
  }
// -----------------------------------------------------------------------------
  void Increment::random() {
  }
// -----------------------------------------------------------------------------
/// I/O and diagnostics
// -----------------------------------------------------------------------------
  void Increment::read(const eckit::Configuration & config) {
    // const eckit::Configuration * conf = &config;
    // util::DateTime * dtp = &time_;
  }
// -----------------------------------------------------------------------------
  void Increment::write(const eckit::Configuration & config) const {
    // const eckit::Configuration * conf = &config;
    // const util::DateTime * dtp = &time_;
  }
// -----------------------------------------------------------------------------
  double Increment::norm() const {
    double zz = 0.0;
    return zz;
  }
// -----------------------------------------------------------------------------
  void Increment::print(std::ostream & os) const {
    oops::Log::trace() << "Increment print starting." << std::endl;
    oops::Log::trace() << "Increment print done." << std::endl;
  }
// -----------------------------------------------------------------------------
  void Increment::dirac(const eckit::Configuration & config) {
    // const eckit::Configuration * conf = &config;
  }
// -----------------------------------------------------------------------------
  void Increment::jnormgrad(const State & xxf,
                            const eckit::Configuration & config) {
    oops::Log::trace() << "Increment jnormgrad starting." << std::endl;
    // const eckit::Configuration * conf = &config;
    oops::Log::trace() << "Increment jnormgrad done." << std::endl;
  }
// -----------------------------------------------------------------------------
}  // namespace magic
