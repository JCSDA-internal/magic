# (C) Copyright 2019-2019.
#
# This software is licensed under the terms of the Apache Licence Version 2.0
# which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

# Create executables that may/may not be used more than once in tests that follow.
ecbuild_add_executable( TARGET  magic_geometry.x
                        SOURCES executables/TestGeometry.cc
                        LIBS    magic )

# Add tests
ecbuild_add_test( TARGET  test_magic_geometry
                  COMMAND ${CMAKE_BINARY_DIR}/bin/magic_geometry.x
                  ARGS    "testinput/geometry.yaml"
                  DEPENDS magic_geometry.x )


