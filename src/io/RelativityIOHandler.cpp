#include "RelativityIOHandler.hpp"

// project
#include "world/RelativityWorld.hpp"
#include "world/RelativityEntity.hpp"
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
/// \brief RelativityIOHandler::RelativityIOHandler
///
/// \author Logan Barnes
/////////////////////////////////////////////
RelativityIOHandler::RelativityIOHandler( RelativityWorld &world )
  : ImguiOpenGLIOHandler( world, true, defaultWidth, defaultHeight )
  , relWorld_( world )
  , upGrid_( new Grid(
                      glm::vec3( -10.0f, -10.0f, -60.0f ), // min
                      glm::vec3(  10.0f,  10.0f, 0.0f ), // max
                      glm::vec3( 5.0f ), // spacing
                      glm::vec3( 0.7f )  // color
                      ) )
{
  std::unique_ptr< shg::Callback > upCallback( new shs::SharedCallback( ) );
  imguiCallback_->setCallback( std::move( upCallback ) );

  relWorld_.addEntity( std::unique_ptr< RelativityEntity >( new RelativityEntity( 60.0f ) ) );
}



RelativityIOHandler::~RelativityIOHandler( )
{}



/////////////////////////////////////////////
/// \brief RelativityIOHandler::onRender
/// \param alpha
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
RelativityIOHandler::_onRender( const double )
{
  shg::OpenGLHelper::clearFramebuffer( );

  upGrid_->render( *upCamera_ );

  auto &entities = relWorld_.getEntities( );

  for ( auto &entity : entities )
  {
    entity->render( *upCamera_ );
  }
} // RelativityIOHandler::onRender



/////////////////////////////////////////////
/// \brief RelativityIOHandler::_onGuiRender
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
RelativityIOHandler::_onGuiRender( )
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

  ImGui::End( );
  ImGui::PopStyleVar( );
} // RelativityIOHandler::onGuiRender



} // namespace rel
