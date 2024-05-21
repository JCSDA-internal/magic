#!/bin/bash

# Detect if set -x was set before calling this script
setx=${-//[^x]/}

# Disable set -x for this part
set +x
# Get the root of the cloned directory
#shellcheck disable=SC2155
readonly DIR_ROOT=$(cd "$(dirname "$(readlink -f -n "${BASH_SOURCE[0]}" )" )/.." && pwd -P)

COMPILER=${COMPILER:-"intel"}

source "${DIR_ROOT}/ush/detect_machine.sh"

# Load modules from a known machine
case "${MACHINE_ID}" in
    UNKNOWN)
        echo "Unknown machine"
        ;;
    *)
        source "${DIR_ROOT}/ush/module-setup.sh"
        module use "${DIR_ROOT}/modulefiles"
        module load "magic_${MACHINE_ID}.${COMPILER}"
        module list
        ;;
esac

# Re-enable set -x if it was set before calling this script
if [[ -n "${setx}" ]]; then set -x; else set +x; fi