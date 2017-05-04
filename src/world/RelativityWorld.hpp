// RelativityWorld.hpp
#pragma once

#include "shared/core/World.hpp"

#include <vector>
#include <memory>


namespace rel
{

class RelativityEntity;


/////////////////////////////////////////////
/// \brief The RelativityWorld class
///
/// \author Logan Barnes
/////////////////////////////////////////////
class RelativityWorld : public shs::World
{

public:

  ///////////////////////////////////////////////////////////////
  /// \brief RelativityWorld
  ///////////////////////////////////////////////////////////////
  RelativityWorld( );


  ///////////////////////////////////////////////////////////////
  /// \brief ~RelativityWorld
  ///////////////////////////////////////////////////////////////
  ~RelativityWorld( );


  ///////////////////////////////////////////////////////////////
  /// \brief update
  ///////////////////////////////////////////////////////////////
  virtual
  void update (
               const double worldTime, ///< update to this time
               const double timestep   ///< interval since last update
               ) final;


  ///////////////////////////////////////////////////////////////
  /// \brief addEntity
  /// \param upEntity
  ///////////////////////////////////////////////////////////////
  void addEntity ( std::unique_ptr< RelativityEntity > upEntity );


  ///////////////////////////////////////////////////////////////
  /// \brief getEntities
  /// \return
  ///////////////////////////////////////////////////////////////
  const std::vector< std::unique_ptr< RelativityEntity > > &getEntities ( ) const;


private:

  float timePosition_;
  std::vector< std::unique_ptr< RelativityEntity > > entities_;

};


} // namespace rel
