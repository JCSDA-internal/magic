/*
 * (C) Copyright 2019-2019.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef MAGIC_STATE_STATE_H_
#define MAGIC_STATE_STATE_H_

#include <ostream>
#include <string>

#include <boost/scoped_ptr.hpp>

#include "oops/base/Variables.h"
#include "oops/util/DateTime.h"
#include "oops/util/ObjectCounter.h"
#include "oops/util/Printable.h"

namespace eckit {
  class Configuration;
}

namespace oops {
  class Variables;
}

namespace ufo {
  class GeoVaLs;
  class Locations;
}

namespace magic {
  class Geometry;
  // class Increment;

// -----------------------------------------------------------------------------
/// State handles model state and everything needed to propagate forward

  class State : public util::Printable,
                private util::ObjectCounter<State> {
   public:
      static const std::string classname() {return "magic::State";}

      /// Constructor, destructor
      State(const Geometry &, const oops::Variables &,
            const util::DateTime &);
      State(const Geometry &, const oops::Variables &,
            const eckit::Configuration &);
      State(const Geometry &, const State &);
      State(const State &);
      virtual ~State();

      /// Basic operators
      State & operator=(const State &);

      /// Get state values at observation locations
      void getValues(const ufo::Locations &,
                     const oops::Variables &,
                     ufo::GeoVaLs &) const;

      /// Interactions with Increment
      // State & operator+=(const Increment &);

      /// I/O and diagnostics
      void read(const eckit::Configuration &);
      void write(const eckit::Configuration &) const;

      boost::shared_ptr<const Geometry> geometry() const {return geom_;}
      const util::DateTime & validTime() const {return time_;}
      util::DateTime & validTime() {return time_;}

      /// Other
      double norm() const;
      void zero();
      void accumul(const double &, const State &);

   private:
      void print(std::ostream &) const;
      boost::shared_ptr<const Geometry> geom_;
      oops::Variables vars_;
      util::DateTime time_;
  };
// -----------------------------------------------------------------------------

}  // namespace magic

#endif  // MAGIC_STATE_STATE_H_
