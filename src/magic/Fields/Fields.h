/*
 * (C) Copyright 2019-2021 NOAA/NWS/NCEP/EMC.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef MAGIC_FIELDS_FIELDS_H_
#define MAGIC_FIELDS_FIELDS_H_

#include <ostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include "oops/base/Variables.h"
#include "oops/util/DateTime.h"
#include "oops/util/Duration.h"
#include "oops/util/ObjectCounter.h"
#include "oops/util/Printable.h"

#include "magic/Fortran.h"

// Forward declarations
namespace eckit {
  class Configuration;
}

namespace oops {
  class UnstructuredGrid;
}

namespace ufo {
  class GeoVaLs;
  class Locations;
}

namespace magic {
  class Geometry;
}

namespace magic {

// -----------------------------------------------------------------------------
/// Class to represent Fields

  class Fields : public util::Printable,
                 private util::ObjectCounter<Fields> {
   public:
      static const std::string classname() {return "magic::Fields";}

      // Constructors and basic operators
      Fields(const Geometry &, const oops::Variables &, const util::DateTime &);
      Fields(const Fields &, const Geometry &);
      Fields(const Fields &, const oops::Variables &);
      Fields(const Fields &, const bool);
      Fields(const Fields &);
      ~Fields();

      // Basic operators
      Fields & operator=(const Fields &);
      Fields & operator+=(const Fields &);
      Fields & operator-=(const Fields &);
      Fields & operator*=(const double &);

      // Basic functions
      void zero();
      void zero(const util::DateTime &);
      void dirac(const eckit::Configuration &);
      void axpy(const double &, const Fields &);
      double dot_product_with(const Fields &) const;
      void schur_product_with(const Fields &);
      void random();

      // Interpolate to given location
      void getValues(const ufo::Locations &, const oops::Variables &,
                           ufo::GeoVaLs &) const;

      // Interpolate full fields
      void changeResolution(const Fields &);
      void add(const Fields &);
      void diff(const Fields &, const Fields &);

      // Unstructured grid
      void ug_coord(oops::UnstructuredGrid &) const;
      void field_to_ug(oops::UnstructuredGrid &, const int &) const;
      void field_from_ug(const oops::UnstructuredGrid &, const int &);

      // Utilities
      void read(const eckit::Configuration &);
      void write(const eckit::Configuration &) const;
      double norm() const;
      boost::shared_ptr<const Geometry> geometry() const {return geom_;}
      const util::DateTime & time() const {return time_;}
      util::DateTime & time() {return time_;}
      int & toFortran() {return keyFlds_;}
      const int & toFortran() const {return keyFlds_;}
      bool isForModel(const bool) const;

   private:
      void print(std::ostream &) const;
      F90flds keyFlds_;
      boost::shared_ptr<const Geometry> geom_;
      oops::Variables vars_;
      util::DateTime time_;
  };
// -----------------------------------------------------------------------------
}  // namespace magic
#endif  // MAGIC_FIELDS_FIELDS_H_
