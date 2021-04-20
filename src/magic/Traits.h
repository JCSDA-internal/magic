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
#include "magic/Increment/Increment.h"

namespace magic {

struct Traits {
  static std::string name() {return "MAGIC";}
  static std::string nameCovar() {return "magicError";}

  typedef magic::Geometry           Geometry;
  typedef magic::State              State;
  typedef magic::Increment          Increment;
};

}  // namespace magic

#endif  // MAGIC_TRAITS_H_
