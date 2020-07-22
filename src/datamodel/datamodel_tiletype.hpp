#ifndef INCLUDED_DATAMODEL_TILETYPE_HPP
#define INCLUDED_DATAMODEL_TILETYPE_HPP

#include <memory>
#include <map>
#include "datamodel_tiletypestate.hpp"

namespace raycaster {
  namespace datamodel {

    struct TileTypeData {
      std::string name;
      std::map<std::string,TileTypeState> valid_states;
    };
    
    struct TileType {
      const std::shared_ptr<const TileTypeData> data;
      TileType( const TileTypeData& data_in ) :data(std::make_shared<TileTypeData>(data_in)) {}
      TileType( const TileType& c ) :data(c.data) {}
      TileType() {}
    };
  }
}

#endif
