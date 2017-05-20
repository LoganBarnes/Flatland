// FlatlandIOHandler.hpp
#pragma once

#include "shared/core/ImguiOpenGLIOHandler.hpp"
#include "shared/graphics/Callback.hpp"
#include <glm/glm.hpp>

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


  ///////////////////////////////////////////////////////////////
  /// \brief updateIO
  ///
  ///        Checks for keystrokes or mouse movement (or
  ///        alternate controllers) and updates output text,
  ///        images, or buffer swaps not handled by showWorld().
  ///
  ///////////////////////////////////////////////////////////////
  virtual
  void updateIO ( );


  void addFRUCameraMovement ( glm::ivec3 lruMoveDir );


protected:

private:

  virtual
  void _onRender ( const double alpha ) final;

  virtual
  void _onGuiRender ( ) final;

  FlatlandWorld &flatWorld_;
  std::unique_ptr< Grid > upGrid_;

  glm::ivec3 fruCameraMovement_;
  float camMovementScale_;

};


} // namespace rel
