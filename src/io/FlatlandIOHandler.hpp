// FlatlandIOHandler.hpp
#pragma once

#include "shared/core/ImguiOpenGLIOHandler.hpp"
#include "shared/graphics/Callback.hpp"

#include <string>
#include <memory>


namespace rel
{

class FlatlandWorld;
class Grid;

/////////////////////////////////////////////
/// \brief The FlatlandIOHandler class
///
/// \author Logan Barnes
/////////////////////////////////////////////
class FlatlandIOHandler : public shs::ImguiOpenGLIOHandler
{

public:

  ///////////////////////////////////////////////////////////////
  /// \brief FlatlandIOHandler
  ///////////////////////////////////////////////////////////////
  FlatlandIOHandler( FlatlandWorld &world );


  ///////////////////////////////////////////////////////////////
  /// \brief ~FlatlandIOHandler
  ///////////////////////////////////////////////////////////////
  ~FlatlandIOHandler( );


protected:

private:

  virtual
  void _onRender ( const double alpha ) final;

  virtual
  void _onGuiRender ( ) final;

  FlatlandWorld &relWorld_;
  std::unique_ptr< Grid > upGrid_;

};


} // namespace rel
