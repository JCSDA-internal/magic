Encapsulation of a Model Agnostic Grid Interface Construct [MAGIC] in JEDI
==========================================================================

Requirements
------------

Tested compilers include:

- GCC 7.3.0, 7.4.0
- Intel 17.x.y.z

Required dependencies:

- NetCDF (Fortran and CXX API)
- CMake
- ecbuild
- eckit
- fckit
- ATLAS
- SABER
- OOPS

Installation
------------

MAGIC employs an out-of-source build/install based on CMake.

Make sure the ecbuild executable script is found ( `which ecbuild` ).

```bash
# 1. Create the build directory and cd into it:
mkdir build
cd build

# 2. Run ecbuild:
ecbuild /path/to/source

# 3. Compile / Install
make -j 10
make install
```

Extra flags maybe added to step 2 to fine-tune configuration.

- `--build=DEBUG|RELEASE|BIT` --- Optimisation level
  * DEBUG:   No optimisation (`-O0 -g`)
  * BIT:     Maximum optimisation while remaning bit-reproducible (`-O2 -g`)
  * RELEASE: Maximum optimisation (`-O3`)

