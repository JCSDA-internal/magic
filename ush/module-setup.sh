#!/bin/bash
set -u

case "${MACHINE_ID}" in
    jet*)
        # We are on NOAA Jet
        if ( ! eval module help > /dev/null 2>&1 ) ; then
            source /apps/lmod/lmod/init/bash
        fi
        export LMOD_SYSTEM_DEFAULT_MODULES=contrib
        module reset
        ;;
    hera*)
        # We are on NOAA Hera
        if ( ! eval module help > /dev/null 2>&1 ) ; then
            source /apps/lmod/lmod/init/bash
        fi
        export LMOD_SYSTEM_DEFAULT_MODULES=contrib
        set +u
        module reset
        set -u
        ;;
    hercules*)
        # We are on Hercules
        if ( ! eval module help > /dev/null 2>&1 ) ; then
            source /apps/other/lmod/lmod/init/bash
        fi
        export LMOD_SYSTEM_DEFAULT_MODULES=contrib
        set +u
        module reset
        set -u
        ;;
    orion*)
        # We are on Orion
        if ( ! eval module help > /dev/null 2>&1 ) ; then
            source /apps/lmod/lmod/init/bash
        fi
        #export LMOD_SYSTEM_DEFAULT_MODULES=git/2.28.0  # contrib has a lot of stuff we shouldn't put in MODULEPATH
        #set +u
        module purge # reset causes issues on Orion sometimes.
        #set -u
        ;;
    s4*)
        # We are on SSEC Wisconsin S4
        if ( ! eval module help > /dev/null 2>&1 ) ; then
            source /usr/share/lmod/lmod/init/bash
        fi
        export LMOD_SYSTEM_DEFAULT_MODULES=license_intel
        module reset
        ;;
    wcoss2)
        # We are on WCOSS2
        module reset
        ;;
    cheyenne*)
        # We are on NCAR Cheyenne
        if ( ! eval module help > /dev/null 2>&1 ) ; then
            source /glade/u/apps/ch/modulefiles/default/localinit/localinit.sh
        fi
        module purge
        ;;
    stampede*)
        # We are on TACC Stampede
        if ( ! eval module help > /dev/null 2>&1 ) ; then
            source /opt/apps/lmod/lmod/init/bash
        fi
        module purge
        ;;
    gaea*)
        # We are on GAEA.
        if ( ! eval module help > /dev/null 2>&1 ) ; then
            # We cannot simply load the module command.  The GAEA
            # /etc/profile modifies a number of module-related variables
            # before loading the module command.  Without those variables,
            # the module command fails.  Hence we actually have to source
            # /etc/profile here.
            source /etc/profile
            __ms_source_etc_profile=yes
        else
            __ms_source_etc_profile=no
        fi
        module purge
        # clean up after purge
        unset _LMFILES_
        unset _LMFILES_000
        unset _LMFILES_001
        unset LOADEDMODULES
        module load modules
        if [[ -d /opt/cray/ari/modulefiles ]] ; then
            module use -a /opt/cray/ari/modulefiles
        fi
        if [[ -d /opt/cray/pe/ari/modulefiles ]] ; then
            module use -a /opt/cray/pe/ari/modulefiles
        fi
        if [[ -d /opt/cray/pe/craype/default/modulefiles ]] ; then
            module use -a /opt/cray/pe/craype/default/modulefiles
        fi
        if [[ -s /etc/opt/cray/pe/admin-pe/site-config ]] ; then
            source /etc/opt/cray/pe/admin-pe/site-config
        fi
        if [[ "${__ms_source_etc_profile}" == yes ]] ; then
            source /etc/profile
            unset __ms_source_etc_profile
        fi
        ;;
    expanse*)
        # We are on SDSC Expanse
        if ( ! eval module help > /dev/null 2>&1 ) ; then
            source /etc/profile.d/modules.sh
        fi
        module purge
        module load slurm/expanse/20.02.3
        ;;
    discover*)
        # We are on NCCS discover
        export SPACK_ROOT=/discover/nobackup/mapotts1/spack
        export PATH=${PATH}:${SPACK_ROOT}/bin
        . "${SPACK_ROOT}/share/spack/setup-env.sh"
        ;;
    noaacloud*)
        # TODO: This can likely be made more general once other cloud platforms come online.
        export SPACK_ROOT=/contrib/global-workflow/spack-stack/spack
        export PATH=${PATH}:${SPACK_ROOT}/bin
        . "${SPACK_ROOT}/share/spack/setup-env.sh"
        ;;
    *)
        echo WARNING: UNKNOWN PLATFORM 1>&2
        ;;
esac

# If this function exists in the environment, run it; else do not
ftype=$(type -t set_strict || echo "")
if [[ "${ftype}" == "function" ]]; then
    set_strict
else
    set +u
fi
