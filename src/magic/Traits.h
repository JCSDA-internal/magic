/*
 * (C) Copyright 2019-2019.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef MAGIC_TRAITS_H_
#define MAGIC_TRAITS_H_

#include <string>

#include "magic/Geometry/Geometry.h"
#include "magic/State/State.h"
//  #include "magic/Increment/Increment.h"

#include "ioda/ObsSpace.h"
#include "ioda/ObsVector.h"

#include "ufo/GeoVaLs.h"
#include "ufo/LinearObsOperator.h"
#include "ufo/ObsBias.h"
#include "ufo/ObsBiasIncrement.h"
#include "ufo/ObsBiasCovariance.h"
#include "ufo/ObsOperator.h"
#include "ufo/Locations.h"

namespace magic {

struct Traits {
  static std::string name() {return "MAGIC";}
  static std::string nameCovar() {return "magicError";}

  typedef magic::Geometry           Geometry;
  typedef magic::State              State;
//  typedef magic::Increment          Increment;

  typedef ufo::ObsBias              ObsAuxControl;
  typedef ufo::ObsBiasIncrement     ObsAuxIncrement;
  typedef ufo::ObsBiasCovariance    ObsAuxCovariance;
//  typedef ufo::ObsCheck             ObsCheck;
  typedef ufo::ObsOperator          ObsOperator;
  typedef ufo::LinearObsOperator    LinearObsOperator;
  typedef ufo::GeoVaLs              GeoVaLs;
  typedef ufo::Locations            Locations;
  typedef ioda::ObsSpace            ObsSpace;
  typedef ioda::ObsVector           ObsVector;
  template <typename DATA> using ObsDataVector = ioda::ObsDataVector<DATA>;
};

}  // namespace magic

#endif  // MAGIC_TRAITS_H_
