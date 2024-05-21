// (C) Copyright 2019- NOAA/NWS/NCEP/EMC

#include <math.h>

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>

#include <boost/math/special_functions/fpclassify.hpp>

#include "oops/mpi/mpi.h"
#include "oops/util/abor1_cpp.h"
#include "oops/util/DateTime.h"
#include "oops/util/Duration.h"
#include "oops/util/Logger.h"
#include "oops/util/missingValues.h"

#include "magic/IO/NetCDFIO.h"

////////////////////////////////////////////////////////////////////////
// Implementation of IO for NetCDF.
////////////////////////////////////////////////////////////////////////

namespace magic {

// -----------------------------------------------------------------------------
/// Constructor, destructor
// -----------------------------------------------------------------------------
  NetCDFIO::NetCDFIO(const std::string & FileName, const std::string & FileMode)
    : fname_(FileName), fmode_(FileMode) {

    oops::Log::trace() << __func__
                       << " fname_: " << fname_
                       << " fmode_: " << fmode_ << std::endl;

    // Open the file. The fmode_ values that are recognized are:
    //    "r" - read
    //    "w" - write, disallow overriting an existing file
    //    "W" - write, allow overwriting an existing file
    if (fmode_ == "r") {
      ncfile_.reset(new netCDF::NcFile(fname_, netCDF::NcFile::read));
    } else if (fmode_ == "w") {
      ncfile_.reset(new netCDF::NcFile(fname_, netCDF::NcFile::newFile));
    } else if (fmode_ == "W") {
      ncfile_.reset(new netCDF::NcFile(fname_, netCDF::NcFile::replace));
    } else {
      oops::Log::error() << "NetCDFIO::NetCDFIO: "
                         << "Unrecognized FileMode: " << fmode_ << std::endl;
      oops::Log::error() << "NetCDFIO::NetCDFIO: "
                         << "Must use one of: 'r', 'w', 'W'" << std::endl;
      ABORT("Unrecognized file mode for NetCDFIO constructor");
    }

    // Abort if open failed
    if (ncfile_->isNull()) {
      oops::Log::error() << __func__ << ": Unable to open file '" << fname_
                         << "' in mode: " << fmode_ << std::endl;
      ABORT("Unable to open file");
    }

    // Find count of objects in the file
    if (fmode_ == "r") {
      dimMap_ = ncfile_->getDims();
      varMap_ = ncfile_->getVars();
      attMap_ = ncfile_->getAtts();
    }

    // When in write mode, do nothing for now
    if ((fmode_ == "W") || (fmode_ == "w")) {
      ABORT("Write file mode for NetCDFIO constructor not implemented.");
    }
  }
// -----------------------------------------------------------------------------
  NetCDFIO::~NetCDFIO() {
    oops::Log::trace() << __func__ << " fname_: " << fname_ << std::endl;
    ncfile_->close();
  }
// -----------------------------------------------------------------------------
  void NetCDFIO::CheckNcCall(int RetCode, const std::string & ErrorMsg) {
    if (RetCode == NC_NOERR)
      return;
    oops::Log::error() << ErrorMsg << " [NetCDF message: '"
                       << nc_strerror(RetCode) << "']" << std::endl;
    ABORT(ErrorMsg);
  }
// -----------------------------------------------------------------------------
  void NetCDFIO::print(std::ostream & os) const {
    os << "NetCDFIO: In " << __FILE__ << " @ " << __LINE__ << std::endl;
  }
// -----------------------------------------------------------------------------
  bool NetCDFIO::dimExists(const std::string dimStr) {
    bool RetCode = false;
    dimIter_ = dimMap_.find(dimStr);
    if ( dimIter_ != dimMap_.end() ) RetCode = true;
    return RetCode;
  }
// -----------------------------------------------------------------------------
  void NetCDFIO::getDimInfo(const std::string dimStr,
                            int & dimId,
                            std::string & dimName,
                            std::size_t & dimSize ) {
    dimIter_ = dimMap_.find(dimStr);
    netCDF::NcDim dim = dimIter_->second;
    dimId = dim.getId();
    dimName = dim.getName();
    dimSize = dim.getSize();
  }
// -----------------------------------------------------------------------------
  int NetCDFIO::getDimId(const std::string dimStr) {
      return dimMap_.find(dimStr)->second.getId();
  }
// -----------------------------------------------------------------------------
  std::string NetCDFIO::getDimName(const std::string dimStr) {
      return dimMap_.find(dimStr)->second.getName();
  }
// -----------------------------------------------------------------------------
  std::size_t NetCDFIO::getDimSize(const std::string dimStr) {
      return dimMap_.find(dimStr)->second.getSize();
  }
// -----------------------------------------------------------------------------
  bool NetCDFIO::varExists(const std::string varStr) {
    bool RetCode = false;
    varIter_ = varMap_.find(varStr);
    if ( varIter_ != varMap_.end() ) RetCode = true;
    return RetCode;
  }
// -----------------------------------------------------------------------------
  void NetCDFIO::getVarInfo(const std::string varStr,
                            int & varId,
                            std::string & varName,
                            std::vector<netCDF::NcDim> & varDims) {
    varIter_ = varMap_.find(varStr);
    netCDF::NcVar var = varIter_->second;
    varId = var.getId();
    varName = var.getName();
    varDims = var.getDims();
  }
// -----------------------------------------------------------------------------
  template <typename DataType>
  void NetCDFIO::readVar(const std::string varStr,
                         DataType & varData) {
    varIter_ = varMap_.find(varStr);
    netCDF::NcVar var = varIter_->second;
    var.getVar(varData);
  }
// -----------------------------------------------------------------------------
}  // namespace magic
