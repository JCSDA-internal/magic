! (C) Copyright 2019-2021 NOAA/NWS/NCEP/EMC.
!
! This software is licensed under the terms of the Apache Licence Version 2.0
! which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

module magic_geom_mod

use iso_c_binding
use kinds
use fckit_mpi_module, only: fckit_mpi_comm
use atlas_module

implicit none

private

!> Geometry data structure
type, public :: magic_geom
  integer :: npx, npy, npz
  real(kind=kind_real), allocatable, dimension(:) :: ak, bk
  real(kind=kind_real), allocatable, dimension(:) :: grid_xt, grid_yt
  real(kind=kind_real), allocatable, dimension(:) :: pfull, phalf
  real(kind=kind_real), allocatable, dimension(:,:) :: grid_lon, grid_lat
contains
  procedure :: init => geom_init
  procedure :: delete => geom_delete
  procedure :: clone => geom_clone
  procedure :: info => geom_info
end type magic_geom

! ------------------------------------------------------------------------------
contains
! ------------------------------------------------------------------------------

! ------------------------------------------------------------------------------
!> Initialize and allocate memory for geometry object
subroutine geom_init(self, c_conf)
  class(magic_geom), target, intent(inout) :: self
  type(c_ptr),               intent(in)    :: c_conf

  type(fckit_mpi_comm) :: f_comm

  f_comm = fckit_mpi_comm()

end subroutine geom_init
! ------------------------------------------------------------------------------

! ------------------------------------------------------------------------------
!> Geometry destructor
subroutine geom_delete(self)
  class(magic_geom), intent(inout) :: self

end subroutine geom_delete
! ------------------------------------------------------------------------------

! ------------------------------------------------------------------------------
!> Clone, self = other
subroutine geom_clone(self, other)
  class(magic_geom), intent(inout) :: self
  class(magic_geom), intent(inout) :: other

end subroutine geom_clone
! ------------------------------------------------------------------------------

! ------------------------------------------------------------------------------
!> Print geometry info to stdout
subroutine geom_info(self)
  class(magic_geom), intent(in) :: self

end subroutine geom_info
! ------------------------------------------------------------------------------

end module magic_geom_mod
