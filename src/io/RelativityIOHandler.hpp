// RelativityIOHandler.hpp
#pragma once

#include "shared/core/ImguiOpenGLIOHandler.hpp"
#include "shared/graphics/Callback.hpp"

#include <string>
#include <memory>


namespace shared
{
class World;
}


namespace rel
{


/////////////////////////////////////////////
/// \brief The RelativityIOHandler class
///
/// \author Logan Barnes
/////////////////////////////////////////////
class RelativityIOHandler : public shs::ImguiOpenGLIOHandler
{

public:

  ///////////////////////////////////////////////////////////////
  /// \brief RelativityIOHandler
  ///////////////////////////////////////////////////////////////
  RelativityIOHandler( shs::World &world );


  ///////////////////////////////////////////////////////////////
  /// \brief ~RelativityIOHandler
  ///////////////////////////////////////////////////////////////
  ~RelativityIOHandler( );


protected:

private:

  virtual
  void _onRender ( const double alpha ) final;

  virtual
  void _onGuiRender ( ) final;

};


} // namespace rel
