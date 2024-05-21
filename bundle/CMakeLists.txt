cmake_minimum_required( VERSION 3.12 FATAL_ERROR )

project( magic-bundle VERSION 0.0.1 LANGUAGES C CXX Fortran )

find_package( ecbuild 3.5 REQUIRED )
include( ecbuild_bundle )

ecbuild_bundle_initialize()

#===============================================================================
# user options
#===============================================================================
option(TEST_IODA "download and ioda-data repo needed for ioda ctests" OFF)
option(TEST_UFO "download and ufo-data repo needed for ufo ctests" OFF)
option(TEST_SABER "download and saber-data repo needed for ioda ctests" OFF)

#===============================================================================
# required repositories
#===============================================================================
ecbuild_bundle( PROJECT jedicmake GIT    "https://github.com/jcsda-internal/jedi-cmake.git" UPDATE BRANCH develop RECURSIVE )
ecbuild_bundle( PROJECT oops      GIT    "https://github.com/JCSDA-Internal/oops.git"       UPDATE BRANCH develop )
#ecbuild_bundle( PROJECT vader     GIT    "https://github.com/JCSDA-Internal/vader.git"      UPDATE BRANCH develop )
#ecbuild_bundle( PROJECT saber     GIT    "https://github.com/JCSDA-Internal/saber.git"      UPDATE BRANCH develop )
#ecbuild_bundle( PROJECT ioda      GIT    "https://github.com/JCSDA-Internal/ioda.git"       UPDATE BRANCH develop )
#ecbuild_bundle( PROJECT ufo       GIT    "https://github.com/JCSDA-Internal/ufo.git"        UPDATE BRANCH develop )
ecbuild_bundle( PROJECT magic     SOURCE "../" )

#===============================================================================
# required repositories
#===============================================================================
include( jedicmake/cmake/Functions/git_functions.cmake  )

#===============================================================================
# optional test data for the upstream repos
#===============================================================================
if ( TEST_IODA )
  find_branch_name(REPO_DIR_NAME ioda)
  if( NOT DEFINED ENV{LOCAL_PATH_JEDI_TESTFILES} AND NOT DEFINED ${GIT_TAG_FUNC} )
    ecbuild_bundle( PROJECT ioda-data GIT "https://github.com/JCSDA-internal/ioda-data.git" BRANCH develop UPDATE )
  endif()
endif ()

if ( TEST_UFO )
  find_branch_name(REPO_DIR_NAME ufo)
  if( NOT DEFINED ENV{LOCAL_PATH_JEDI_TESTFILES} AND NOT DEFINED ${GIT_TAG_FUNC} )
    ecbuild_bundle( PROJECT ufo-data GIT "https://github.com/JCSDA-internal/ufo-data.git" BRANCH develop UPDATE )
  endif()
endif ()

if ( TEST_SABER )
  find_branch_name(REPO_DIR_NAME saber)
  if( NOT DEFINED ENV{LOCAL_PATH_JEDI_TESTFILES} AND NOT DEFINED ${GIT_TAG_FUNC} )
    ecbuild_bundle( PROJECT saber-data GIT "https://github.com/JCSDA-internal/saber-data.git" BRANCH develop UPDATE )
  endif()
endif ()

#===============================================================================

ecbuild_bundle_finalize()
