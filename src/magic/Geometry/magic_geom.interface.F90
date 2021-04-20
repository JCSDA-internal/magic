! (C) Copyright 2019-2021 NOAA/NWS/NCEP/EMC.
!
! This software is licensed under the terms of the Apache Licence Version 2.0
! which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

!> Fortran module handling geometry

module magic_geom_mod_c

use iso_c_binding
use magic_geom_mod, only: magic_geom

implicit none
private

#define LISTED_TYPE magic_geom

!> Linked list interface - defines registry_t type
#include "oops/util/linkedList_i.f"

!> Global registry
type(registry_t), public :: magic_geom_registry

! ------------------------------------------------------------------------------
contains
! ------------------------------------------------------------------------------
!> Linked list implementation
#include "oops/util/linkedList_c.f"

! ------------------------------------------------------------------------------
!> Setup geometry object
subroutine magic_geo_setup_c(c_key_self, c_conf) &
           bind(c, name='magic_geo_setup_f90')
  integer(c_int), intent(inout) :: c_key_self
  type(c_ptr),       intent(in) :: c_conf

  type(magic_geom),  pointer :: self

  call magic_geom_registry%init()
  call magic_geom_registry%add(c_key_self)
  call magic_geom_registry%get(c_key_self,self)

  call self%init(c_conf)

end subroutine magic_geo_setup_c

! ------------------------------------------------------------------------------
!> Clone geometry object
subroutine magic_geo_clone_c(c_key_self, c_key_other) &
           bind(c, name='magic_geo_clone_f90')
  integer(c_int), intent(in   ) :: c_key_self
  integer(c_int), intent(inout) :: c_key_other

  type(magic_geom),  pointer :: self, other

  call magic_geom_registry%add(c_key_other)
  call magic_geom_registry%get(c_key_other, other)
  call magic_geom_registry%get(c_key_self , self )

  call self%clone(other)

end subroutine magic_geo_clone_c

! ------------------------------------------------------------------------------
!> Geometry destructor
subroutine magic_geo_delete_c(c_key_self) &
           bind(c, name='magic_geo_delete_f90')
  integer(c_int), intent(inout) :: c_key_self

  type(magic_geom),  pointer :: self

  call magic_geom_registry%get(c_key_self, self)
  call self%delete()
  call magic_geom_registry%remove(c_key_self)

end subroutine magic_geo_delete_c

! ------------------------------------------------------------------------------
!> Dump basic geometry info in file and std output
subroutine magic_geo_info_c(c_key_self) &
           bind(c, name='magic_geo_info_f90')
  integer(c_int), intent(in   ) :: c_key_self

  type(magic_geom),  pointer :: self

  call magic_geom_registry%get(c_key_self , self)
  call self%info()

end subroutine magic_geo_info_c

! ------------------------------------------------------------------------------

end module magic_geom_mod_c
