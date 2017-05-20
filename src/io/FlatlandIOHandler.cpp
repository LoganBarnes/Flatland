#include "FlatlandIOHandler.hpp"

// project
#include "world/FlatlandWorld.hpp"
#include "world/FlatlandEntity.hpp"
#include "io/FlatlandCallback.hpp"
#include "io/Grid.hpp"

// shared
#include "shared/graphics/OpenGLHelper.hpp"
#include "shared/graphics/GlmCamera.hpp"
#include "shared/graphics/ImguiCallback.hpp"
#include "shared/graphics/SharedCallback.hpp"
#include <imgui.h>

// system
#include <vector>
#include <algorithm>
#include <memory>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

namespace rel
{


namespace
{
constexpr int defaultWidth  = 1280;
constexpr int defaultHeight = 720;
}


/////////////////////////////////////////////
/// \brief FlatlandIOHandler::FlatlandIOHandler
///
/// \author Logan Barnes
/////////////////////////////////////////////
FlatlandIOHandler::FlatlandIOHandler( FlatlandWorld &world )
  : ImguiOpenGLIOHandler( world, true, defaultWidth, defaultHeight )
  , flatWorld_( world )
  , upGrid_( new Grid(
                      glm::vec3( -10.0f, -10.0f, -60.0f ), // min
                      glm::vec3(  10.0f,  10.0f, 0.0f ), // max
                      glm::vec3( 5.0f ), // spacing
                      glm::vec3( 0.7f )  // color
                      ) )
  , fruCameraMovement_( 0.0f )
  , camMovementScale_( 0.1f )
{
  std::unique_ptr< FlatlandCallback > flatCallback( new FlatlandCallback( *this ) );
  imguiCallback_->setCallback( std::move( flatCallback ) );

  flatWorld_.addEntity( std::unique_ptr< FlatlandEntity >( new FlatlandEntity( 60.0f ) ) );
}



FlatlandIOHandler::~FlatlandIOHandler( )
{}



///////////////////////////////////////////////////////////////
/// \brief FlatlandIOHandler::updateIO
///
/// \author Logan Barnes
///////////////////////////////////////////////////////////////
void
FlatlandIOHandler::updateIO( )
{
  OpenGLIOHandler::updateIO( );

  //
  // process camera movement
  //
  glm::vec3 eye = upCamera_->getEyeVector( );

  // no movement (zero vec)
  if ( fruCameraMovement_.x == fruCameraMovement_.y == fruCameraMovement_.z == 0 )
  {
    return;
  }

  glm::vec3 fruMoveDir( fruCameraMovement_ );
  fruMoveDir = glm::normalize( fruMoveDir ) * camMovementScale_;

  eye += upCamera_->getLookVector( )  * fruMoveDir.x;
  eye += upCamera_->getRightVector( ) * fruMoveDir.y;
  eye += upCamera_->getUpVector( )    * fruMoveDir.z;

  upCamera_->setEye( eye );
} // FlatlandIOHandler::updateIO



///////////////////////////////////////////////////////////////
/// \brief FlatlandIOHandler::addLRUCameraMovement
/// \param lruMoveDir
///
/// \author Logan Barnes
///////////////////////////////////////////////////////////////
void
FlatlandIOHandler::addFRUCameraMovement( glm::ivec3 lruMoveDir )
{
  fruCameraMovement_ += lruMoveDir;
  fruCameraMovement_  = glm::clamp( fruCameraMovement_, -1, 1 );
}



///////////////////////////////////////////////////////////////
/// \brief FlatlandIOHandler::onRender
/// \param alpha
///
/// \author Logan Barnes
///////////////////////////////////////////////////////////////
void
FlatlandIOHandler::_onRender( const double )
{
  shg::OpenGLHelper::clearFramebuffer( );

  upGrid_->render( *upCamera_ );

  auto &entities = flatWorld_.getEntities( );

  for ( auto &entity : entities )
  {
    entity->render( *upCamera_ );
  }
} // FlatlandIOHandler::onRender



///////////////////////////////////////////////////////////////
/// \brief FlatlandIOHandler::_onGuiRender
///
/// \author Logan Barnes
///////////////////////////////////////////////////////////////
void
FlatlandIOHandler::_onGuiRender( )
{
  bool alwaysOpen = true;

  ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );

  ImGui::SetNextWindowPos ( ImVec2( 0, 0 ) );
  ImGui::Begin( "Settings", &alwaysOpen, ImVec2( ), 1.0f, ImGuiWindowFlags_AlwaysAutoResize );

  // FPS
  ImGui::Text(
              "Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO( ).Framerate,
              ImGui::GetIO( ).Framerate
              );

  ImGui::Separator( );

  ImGui::Text( "World Time: %.3f", flatWorld_.getTimePosition( ) );

  ImGui::End( );
  ImGui::PopStyleVar( );
} // FlatlandIOHandler::onGuiRender



} // namespace rel
