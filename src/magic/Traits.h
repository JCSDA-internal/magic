// (C) Copyright 2019- NOAA/NWS/NCEP/EMC

#pragma once

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

