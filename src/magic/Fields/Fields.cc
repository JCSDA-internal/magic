#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <iomanip>

#include "eckit/config/Configuration.h"
#include "oops/generic/UnstructuredGrid.h"
#include "oops/base/Variables.h"
#include "oops/util/DateTime.h"
#include "oops/util/Logger.h"
#include "ufo/GeoVaLs.h"
#include "ufo/Locations.h"

#include "magic/Geometry/Geometry.h"
#include "magic/Fields/Fields.h"

// -----------------------------------------------------------------------------
namespace magic {
// -----------------------------------------------------------------------------
  Fields::Fields(const Geometry & geom,
                 const oops::Variables & vars,
                 const util::DateTime & time):
    geom_(new Geometry(geom)), vars_(vars), time_(time) {
  }
// -----------------------------------------------------------------------------
  Fields::Fields(const Fields & other, const bool copy)
    : geom_(other.geom_), vars_(other.vars_), time_(other.time_)
  {
  }
// -----------------------------------------------------------------------------
  Fields::Fields(const Fields & other)
    : geom_(other.geom_), vars_(other.vars_), time_(other.time_)
  {
  }
// -----------------------------------------------------------------------------
  Fields::Fields(const Fields & other, const Geometry & geom)
    : geom_(new Geometry(geom)), vars_(other.vars_), time_(other.time_)
  {
  }
// -----------------------------------------------------------------------------
  Fields::Fields(const Fields & other, const oops::Variables & vars)
    : geom_(other.geom_), vars_(vars), time_(other.time_)
  {
  }
// -----------------------------------------------------------------------------
  Fields::~Fields() {
  }
// -----------------------------------------------------------------------------
  Fields & Fields::operator=(const Fields & rhs) {
    time_ = rhs.time_;
    return *this;
  }
// -----------------------------------------------------------------------------
  Fields & Fields::operator+=(const Fields & rhs) {
    return *this;
  }
// -----------------------------------------------------------------------------
  Fields & Fields::operator-=(const Fields & rhs) {
    return *this;
  }
// -----------------------------------------------------------------------------
  Fields & Fields::operator*=(const double & zz) {
    return *this;
  }
// -----------------------------------------------------------------------------
  void Fields::zero() {
  }
// -----------------------------------------------------------------------------
  void Fields::zero(const util::DateTime & time) {
    time_ = time;
  }
// -----------------------------------------------------------------------------
  void Fields::dirac(const eckit::Configuration & config) {
  }
// -----------------------------------------------------------------------------
  void Fields::axpy(const double & zz, const Fields & rhs) {
  }
// -----------------------------------------------------------------------------
  double Fields::dot_product_with(const Fields & fld2) const {
    double zz = 0;
    return zz;
  }
// -----------------------------------------------------------------------------
  void Fields::schur_product_with(const Fields & dx) {
  }
// -----------------------------------------------------------------------------
  void Fields::random() {
  }
// -----------------------------------------------------------------------------
  void Fields::getValues(const ufo::Locations & locs,
                         const oops::Variables & vars,
                         ufo::GeoVaLs & gom) const {
  }
// -----------------------------------------------------------------------------
  void Fields::changeResolution(const Fields & other) {
  }
// -----------------------------------------------------------------------------
  void Fields::add(const Fields & rhs) {
  }
// -----------------------------------------------------------------------------
  void Fields::diff(const Fields & x1, const Fields & x2) {
  }
// -----------------------------------------------------------------------------
  void Fields::ug_coord(oops::UnstructuredGrid & ug) const {
  }
// -----------------------------------------------------------------------------
  void Fields::field_to_ug(oops::UnstructuredGrid & ug,
                           const int & its) const {
  }
// -----------------------------------------------------------------------------
  void Fields::field_from_ug(const oops::UnstructuredGrid & ug,
                             const int & its) {
  }
// -----------------------------------------------------------------------------
  void Fields::read(const eckit::Configuration & config) {
  }
// -----------------------------------------------------------------------------
  void Fields::write(const eckit::Configuration & config) const {
  }
// -----------------------------------------------------------------------------
  double Fields::norm() const {
    double zz = 0.0;
    return zz;
  }
// -----------------------------------------------------------------------------
  void Fields::print(std::ostream & os) const {
    int nf = -1;
    std::vector<double> zstat(3*nf);
    for (int jj = 0; jj < nf; ++jj) {
      os << std::endl << std::right << std::setw(7) << vars_[jj]
         << "   min="  <<  std::fixed << std::setw(12) <<
                           std::right << zstat[3*jj]
         << "   max="  <<  std::fixed << std::setw(12) <<
                           std::right << zstat[3*jj+1]
         << "   mean=" <<  std::fixed << std::setw(12) <<
                           std::right << zstat[3*jj+2];
    }
  }
// -----------------------------------------------------------------------------
  bool Fields::isForModel(bool nonlinear) const {
    int nf = -1;
    bool ok = (nf >= 2);    // <---- HARD CODED STUFF ... NEED TO CHANGE
    if (nonlinear) ok = ok;  // && (nb == 2);
    return ok;
  }
// -----------------------------------------------------------------------------
}  // namespace magic
