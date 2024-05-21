include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

list( APPEND magic_src_files
Traits.h
)

list( APPEND magic_src_files
# Geometry
Geometry/Geometry.cc
Geometry/Geometry.h

# Fields
#Fields/Fields.cc
#Fields/Fields.h
#Fields/FieldsFortran.h

# State
State/State.cc
State/State.h

# Increment
Increment/Increment.cc
Increment/Increment.h

# IO
IO/NetCDFIO.cc
IO/NetCDFIO.h
)

ecbuild_add_library(TARGET          ${PROJECT_NAME}
                    SOURCES         ${magic_src_files}
                    INSTALL_HEADERS LISTED
                    LINKER_LANGUAGE CXX
                    )

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
                                                  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)

target_link_libraries( ${PROJECT_NAME} PUBLIC NetCDF::NetCDF_C NetCDF::NetCDF_CXX )
#target_link_libraries( ${PROJECT_NAME} PUBLIC MPI::MPI_Fortran MPI::MPI_CXX )
target_link_libraries( ${PROJECT_NAME} PUBLIC eckit )
target_link_libraries( ${PROJECT_NAME} PUBLIC fckit )
target_link_libraries( ${PROJECT_NAME} PUBLIC atlas atlas_f )
target_link_libraries( ${PROJECT_NAME} PUBLIC oops )
#target_link_libraries( ${PROJECT_NAME} PUBLIC ufo )

if(OpenMP_Fortran_FOUND)
  target_link_libraries( ${PROJECT_NAME} PUBLIC OpenMP::OpenMP_Fortran )
endif()
if(OpenMP_CXX_FOUND)
  target_link_libraries( ${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX )
endif()
