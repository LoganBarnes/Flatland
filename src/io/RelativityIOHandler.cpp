#include "RelativityIOHandler.hpp"

// shared
#include "shared/graphics/OpenGLHelper.hpp"
#include "shared/graphics/GlmCamera.hpp"
#include "shared/graphics/ImguiCallback.hpp"
#include "shared/graphics/SharedCallback.hpp"
#include <imgui.h>

// system
#include <vector>
#include <algorithm>

namespace rel
{


namespace
{
constexpr int defaultWidth  = 1024;
constexpr int defaultHeight = 1024;
}


/////////////////////////////////////////////
/// \brief RelativityIOHandler::RelativityIOHandler
///
/// \author Logan Barnes
/////////////////////////////////////////////
RelativityIOHandler::RelativityIOHandler( shs::World &world )
  : ImguiOpenGLIOHandler( world, true, defaultWidth, defaultHeight )
{
  std::unique_ptr< shg::Callback > upCallback( new shs::SharedCallback( ) );
  imguiCallback_->setCallback( std::move( upCallback ) );
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
