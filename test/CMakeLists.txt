# (C) Copyright 2019-2019.
#
# This software is licensed under the terms of the Apache Licence Version 2.0
# which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
add_subdirectory(executables)

list( APPEND magic_test_input
testinput/geometry.yaml
)

# Create directory for test input/output and symlink all files
file( MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testinput )
SYMLINK_FILES( ${magic_test_input} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} )

# Add tests
ecbuild_add_test( TARGET  test_magic_geometry
                  COMMAND ${CMAKE_BINARY_DIR}/bin/magic_geometry.x
                  ARGS    "testinput/geometry.yaml"
                  DEPENDS magic_geometry.x )

