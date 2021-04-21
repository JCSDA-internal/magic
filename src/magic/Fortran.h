/*
 * (C) Copyright 2019-2021 NOAA/NWS/NCEP/EMC.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef MAGIC_FORTRAN_H_
#define MAGIC_FORTRAN_H_

// Forward declarations
namespace eckit {
  class Configuration;
}

namespace util {
  class DateTime;
  class Duration;
}

namespace magic {

// Geometry key type
typedef int F90geom;
// Feilds key type
typedef int F90flds;
// State key
typedef int F90state;
// Increment key
typedef int F90inc;
// Locations key type
typedef int F90locs;
// Goms key type
typedef int F90goms;
// Trajectory key type
typedef int F90traj;
// Background error covariance key type
typedef int F90bmat;
// Localization matrix
typedef int F90locmat;
// ObOp trajectory
typedef int F90ootrj;
// LinearVariableChange keys
typedef int F90lvcc2a;
typedef int F90lvca2m;
// VariableChange keys
typedef int F90vca2m;

}  // namespace magic
#endif  // MAGIC_FORTRAN_H_
