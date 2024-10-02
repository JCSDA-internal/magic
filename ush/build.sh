#!/bin/bash

set -eux
# Get the root of the cloned directory
#shellcheck disable=SC2155
readonly DIR_ROOT=$(cd "$(dirname "$(readlink -f -n "${BASH_SOURCE[0]}" )" )/.." && pwd -P)

#==============================================================================#
# User Options
BUILD_CLEAN=${BUILD_CLEAN:-"NO"}
BUILD_TYPE=${BUILD_TYPE:-"Release"}
COMPILER=${COMPILER:-"intel"}
BUILD_DIR=${BUILD_DIR:-"${DIR_ROOT}/build"}
INSTALL_PREFIX=${INSTALL_PREFIX:-"${DIR_ROOT}/install"}
CMAKE_OPTS=${CMAKE_OPTS:-}

#==============================================================================#
# detect the machine
source "${DIR_ROOT}/ush/detect_machine.sh"

#==============================================================================#
# Load modules from a known machine
case "${MACHINE_ID}" in
    UNKNOWN)
        echo "Unknown machine"
        ;;
    *)
        set +x
        source "${DIR_ROOT}/ush/module-setup.sh"
        module use "${DIR_ROOT}/modulefiles"
        module load "magic_${MACHINE_ID}.${COMPILER}"
        module list
        set -x
        ;;
esac

#==============================================================================#
# Collect machine specific cmake options
case "${MACHINE_ID}" in
    jet*|hera*|hercules*|orion*|s4*|wcoss2|cheyenne*)
        CMAKE_OPTS+=" -DMPIEXEC_EXECUTABLE=${MPIEXEC_EXEC} -DMPIEXEC_NUMPROC_FLAG=${MPIEXEC_NPROC}"
        ;;
    *)
        ;;
esac

# Collect BUILD Options
CMAKE_OPTS+=" -DCMAKE_BUILD_TYPE=${BUILD_TYPE}"

# Install destination for built executables, libraries, CMake Package config
CMAKE_OPTS+=" -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX}"

# Re-use or create a new BUILD_DIR (Default: create new BUILD_DIR)
[[ "${BUILD_CLEAN}" =~ [yYtT] ]] && rm -rf "${BUILD_DIR}"
mkdir -p "${BUILD_DIR}" && cd "${BUILD_DIR}"

# Configure, build, install
# shellcheck disable=SC2086
cmake ${CMAKE_OPTS} "${DIR_ROOT}/bundle"
make -j "${BUILD_JOBS:-8}" VERBOSE="${BUILD_VERBOSE:-}"
#make install

exit
