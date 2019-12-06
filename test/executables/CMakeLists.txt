# (C) Copyright 2019-2019.
#
# This software is licensed under the terms of the Apache Licence Version 2.0
# which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

# Create executables that may/may not be used more than once in tests that follow.
ecbuild_add_executable( TARGET  magic_geometry.x
                        SOURCES TestGeometry.cc
                        LIBS    magic )

ecbuild_add_executable( TARGET  magic_state.x
                        SOURCES TestState.cc
                        LIBS    magic )
