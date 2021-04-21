/*
 * (C) Copyright 2019-2021 NOAA/NWS/NCEP/EMC.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef MAGIC_IO_NETCDFIO_H_
#define MAGIC_IO_NETCDFIO_H_

#include <netcdf>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "oops/util/DateTime.h"
#include "oops/util/ObjectCounter.h"

////////////////////////////////////////////////////////////////////////
// Implementation of IO for NetCDF.
////////////////////////////////////////////////////////////////////////

namespace magic {

// -----------------------------------------------------------------------------
class NetCDFIO : private util::ObjectCounter<NetCDFIO> {
 public:
  static const std::string classname() {return "NetCDFIO";}

  NetCDFIO(const std::string &, const std::string &);
  virtual ~NetCDFIO();

  bool dimExists(const std::string);
  void getDimInfo(const std::string, int &, std::string &, std::size_t &);
  int getDimId(const std::string);
  std::string getDimName(const std::string);
  std::size_t getDimSize(const std::string);

  bool varExists(const std::string);
  void getVarInfo(const std::string,
                  int &, std::string &, std::vector<netCDF::NcDim> &);
  template <typename DataType>
  void readVar(const std::string, DataType &);

 private:
  // For the oops::Printable base class
  void print(std::ostream &) const;

  void CheckNcCall(int, const std::string &);

  void CreateNcDim(const std::string &, const std::size_t &);

  // Data members
  std::unique_ptr<netCDF::NcFile> ncfile_;

  std::multimap<std::string, netCDF::NcDim> dimMap_;
  std::multimap<std::string, netCDF::NcDim>::iterator dimIter_;

  std::multimap<std::string, netCDF::NcVar> varMap_;
  std::multimap<std::string, netCDF::NcVar>::iterator varIter_;

  std::multimap<std::string, netCDF::NcGroupAtt> attMap_;
  std::multimap<std::string, netCDF::NcGroupAtt>::iterator attIter_;

  std::string fname_;
  std::string fmode_;
};
// -----------------------------------------------------------------------------

}  // namespace magic

#endif  // MAGIC_IO_NETCDFIO_H_
