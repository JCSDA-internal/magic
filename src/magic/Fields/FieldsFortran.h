/*
 * (C) Copyright 2019-2019.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef MAGIC_FIELDS_FIELDSFORTRAN_H_
#define MAGIC_FIELDS_FIELDSFORTRAN_H_

#include "magic/Fortran.h"

// Forward declarations
namespace eckit {
  class Configuration;
}

namespace util {
  class DateTime;
  class Duration;
}

namespace magic {
  extern "C" {
    void magic_fld_create_f90(F90flds &, const F90geom &,
                              const eckit::Configuration * const *);
    void magic_fld_delete_f90(F90flds &);
    void magic_fld_copy_f90(const F90flds &, const F90flds &);
    void magic_fld_zero_f90(const F90flds &);

    void magic_fld_self_add_f90(const F90flds &, const F90flds &);
    void magic_fld_self_sub_f90(const F90flds &, const F90flds &);
    void magic_fld_self_mul_f90(const F90flds &, const double &);
    void magic_fld_axpy_f90(const F90flds &, const double &,
                            const F90flds &);
    void magic_fld_dot_prod_f90(const F90flds &, const F90flds &,
                                const F90geom &, double &);
    void magic_fld_self_schur_f90(const F90flds &, const F90flds &);

    void magic_fld_random_f90(const F90flds &);
    void magic_fld_dirac_f90(const F90flds &, const F90geom &,
                             const eckit::Configuration * const *);

    void magic_fld_add_incr_f90(const F90flds &, const F90flds &);
    void magic_fld_diff_incr_f90(const F90flds &, const F90flds &,
                                 const F90flds &);

    void magic_fld_change_resol_f90(const F90flds &, const F90flds &);
    void magic_fld_read_file_f90(const F90flds &, const F90geom &,
                                 const eckit::Configuration * const *,
                                 util::DateTime * const *);
    void magic_fld_write_file_f90(const F90flds &, const F90geom &,
                                  const eckit::Configuration * const *,
                                  const util::DateTime * const *);

    void magic_fld_interp_nl_f90(const F90flds &, const F90geom &,
                                 const F90locs &,
                                 const eckit::Configuration * const *,
                                 const F90goms &);

    void magic_fld_ug_coord_f90(const F90flds &, const F90geom &,
                                const int &);
    void magic_fld_field_to_ug_f90(const F90flds &, const F90geom &,
                                   const int &,
                                   const int &);
    void magic_fld_field_from_ug_f90(const F90flds &, const F90geom &,
                                     const int &,
                                     const int &);

    void magic_fld_gpnorm_f90(const F90flds &, const F90geom &,
                              const int &, double &);
    void magic_fld_sizes_f90(const F90flds &, int &);
    void magic_fld_rms_f90(const F90flds &, const F90geom &, double &);
  }
}  // namespace magic
#endif  // MAGIC_FIELDS_FIELDSFORTRAN_H_
