// (C) Copyright 2019- NOAA/NWS/NCEP/EMC

#include <string>
#include <numeric>

#include "eckit/config/Configuration.h"
#include "eckit/exception/Exceptions.h"

#include "oops/util/Logger.h"

#include "magic/Geometry/Geometry.h"

// -----------------------------------------------------------------------------
namespace magic {
// -----------------------------------------------------------------------------
  const int HALO_SIZE = 1;
// -----------------------------------------------------------------------------
  Geometry::Geometry(const eckit::Configuration & conf,
                     const eckit::mpi::Comm & comm)
    : comm_(comm) {
    const eckit::Configuration * configc = &conf;

    eckit::LocalConfiguration atlas_config = conf.getSubConfiguration("atlas");
    grid_type_ = atlas_config.getString("type", "structured");
    halo_size_ = atlas_config.getInt("halo", HALO_SIZE);

    // Initialize eckit communicator for atlas
    eckit::mpi::setCommDefault(comm_.name().c_str());

    // Create the grid
    grid_ = atlas::Grid(atlas_config);

    // Generate the partitioner
    partitioner_ = atlas::grid::Partitioner("equal_regions");

    // Generate the distribution based on the grid and partitioner
    distribution_ = atlas::grid::Distribution(grid_, partitioner_);

    // Generate the mesh based on the grid and distribution
    // (this is for the structured grid!)
    mesh_ = atlas::MeshGenerator("structured").generate(grid_, partitioner_);

    // Generate the function space
    functionSpace_ = atlas::functionspace::StructuredColumns(grid_,
                     atlas_config, atlas::option::halo(halo_size_));
    atlas::functionspace::StructuredColumns fs(functionSpace_);

    auto vGhost = atlas::array::make_view<int, 1>(fs.ghost());
    auto vLonlat = atlas::array::make_view<double, 2>(fs.lonlat());

    atlas::Field owned = fs.createField<int>(atlas::option::name("owned") |
                                             atlas::option::levels(1));
    auto vOwned = atlas::array::make_view<int, 2>(owned);

    auto view_i = atlas::array::make_view<int, 1>(fs.index_i());
    auto view_j = atlas::array::make_view<int, 1>(fs.index_j());
    for (atlas::idx_t j = fs.j_begin_halo(); j < fs.j_end_halo(); ++j) {
      for (atlas::idx_t i = fs.i_begin_halo(j); i < fs.i_end_halo(j); ++i) {
        atlas::idx_t jnode = fs.index(i, j);
        vOwned(jnode, 0) = vGhost(jnode) > 0 ? 0 : 1;
      }
    }

    nLevs_ = atlas_config.getInt("levels", 0.);
    std::vector<double> z(nLevs_);
    std::iota(std::begin(z), std::end(z), 0);
    ak_ = conf.getDoubleVector("ak");
    bk_ = conf.getDoubleVector("bk");

    vcoord_ = atlas::Vertical(nLevs_, z);

    atlas::Field vert_coord = fs.createField<double>(
                                atlas::option::name("vert_coord") |
                                atlas::option::levels(nLevs_));
    auto vVert_coord = atlas::array::make_view<double, 2>(vert_coord);

    fields_ = atlas::FieldSet();
    fields_.add(owned);

    // Print a summary of the geometry
    this->print(oops::Log::info());
  }
// -----------------------------------------------------------------------------
  Geometry::Geometry(const Geometry & other)
    : comm_(other.comm_) {

    grid_ = other.grid_;
    mesh_ = other.mesh_;
    nLevs_ = other.nLevs_;
    ak_ = other.ak_;
    bk_ = other.bk_;
    vcoord_ = other.vcoord_;
  }
// -----------------------------------------------------------------------------
  Geometry::~Geometry() {
  }
// -----------------------------------------------------------------------------
  void Geometry::print(std::ostream & os) const {
    os << "Geometry:" << std::endl;
    os << "  Grid Name: " << grid_.name() << std::endl;
    os << "  Number of Points: " << grid_.size() << std::endl;
    os << "  Grid nx, ny: " << grid_.nxmax() << ", " << grid_.ny() << std::endl;
    os << "  Grid y: " << grid_.y() << std::endl;
    os << "  Grid Projection Units: " << grid_.projection().units()
       << std::endl;
    os << "  Domain: " << grid_.domain() << std::endl;
    os << "  Periodic: " << grid_.periodic() << std::endl;
    os << "  Spec: " << grid_.spec() << std::endl;

    os << "  mesh number of nodes: " << mesh_.nodes().size() << std::endl;
    os << "  mesh footprint: " << mesh_.footprint() << std::endl;

    os << "  (min, max) level: " << vcoord_.min() << ", " << vcoord_.max()
       << std::endl;

    os << "  function space size: " << functionSpace_.size() << std::endl;
  }
// -----------------------------------------------------------------------------
  void Geometry::latlon(std::vector<double> & lats,
                        std::vector<double> & lons,
                        const bool halo) const {
    // get the number of total grid points (including halo)
    int gridSizeWithHalo = functionSpace_.size();
    auto vLonlat = atlas::array::make_view<double, 2>(functionSpace_.lonlat());

    // count the number of owned non-ghost points
    auto vGhost = atlas::array::make_view<int, 1>(functionSpace_.ghost());
    int gridSizeNoHalo = 0;
    for (size_t i = 0; i < gridSizeWithHalo; i++) {
      if (vGhost(i) == 0) gridSizeNoHalo++;
    }

    // allocate arrays
    int gridSize = (halo) ? gridSizeWithHalo : gridSizeNoHalo;
    lons.resize(gridSize);
    lats.resize(gridSize);

    // fill
    int idx = 0;
    for (size_t i=0; i < gridSizeWithHalo; i++) {
      if (!halo && vGhost(i)) continue;
      double lon = vLonlat(i, 0);
      double lat = vLonlat(i, 1);
      lats[idx] = lat;
      lons[idx++] = lon;
    }
    ASSERT(idx == gridSize);
  }
// -----------------------------------------------------------------------------
}  // namespace magic
