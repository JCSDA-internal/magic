# (C) Copyright 2019- NOAA/NWS/NCEP/EMC

# Extra macros to eliminate repetition

# Macro to SYMLINK a FILELIST from SRCDIR to DSTDIR
macro( SYMLINK_FILES FILELIST SRCDIR DSTDIR )
  foreach( FILENAME ${FILELIST} )
    execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
      ${SRCDIR}/${FILENAME}
      ${DSTDIR}/${FILENAME} )
  endforeach( FILENAME )
endmacro()

