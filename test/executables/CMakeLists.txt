# (C) Copyright 2019- NOAA/NWS/NCEP/EMC

# Create executables that may/may not be used more than once in tests that follow.
ecbuild_add_executable( TARGET  magic_geometry.x
                        SOURCES TestGeometry.cc
                        LIBS    magic )

#ecbuild_add_executable( TARGET  magic_state.x
#                        SOURCES TestState.cc
#                        LIBS    magic )
