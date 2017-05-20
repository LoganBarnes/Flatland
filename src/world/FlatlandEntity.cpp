// FlatlandEntity.cpp
#include "FlatlandEntity.hpp"
#include "FlatlandConfig.hpp"

// shared
#include "shared/graphics/OpenGLHelper.hpp"
#include "shared/graphics/GlmCamera.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>


namespace rel
{


///////////////////////////////////////////////////////////////
/// \brief FlatlandEntity::FlatlandEntity
///////////////////////////////////////////////////////////////
FlatlandEntity::FlatlandEntity( float maxTime )
  : numVertsPerShape_( 32 )
  , maxTime_( maxTime )
  , color_( 0.1f, 0.5f, 0.9f )
{
  _prepGLPipeline( );
}



///////////////////////////////////////////////////////////////
/// \brief FlatlandEntity::move
///////////////////////////////////////////////////////////////
void
FlatlandEntity::move( const double /*dt*/ )
{}


void
FlatlandEntity::render( const shg::GlmCamera< float > &camera ) const
{
  glUseProgram( *glIds_.program );

  shg::OpenGLHelper::setMatrixUniform(
                                      glIds_.program,
                                      "projectionViewMatrix",
                                      glm::value_ptr( camera.getPerspectiveProjectionViewMatrix( ) )
                                      );
  shg::OpenGLHelper::setFloatUniform(
                                     glIds_.program,
                                     "color",
                                     glm::value_ptr( color_ ),
                                     3
                                     );
  shg::OpenGLHelper::setFloatUniform(
                                     glIds_.program,
                                     "maxTime",
                                     &maxTime_
                                     );
  shg::OpenGLHelper::renderBuffer(
                                  glIds_.vao,
                                  0,
                                  numVertsPerShape_,
                                  GL_TRIANGLE_FAN
                                  );
} // FlatlandEntity::render



void
FlatlandEntity::_prepGLPipeline( )
{
  shg::ShaderVec shaders = 
  {
    { GL_VERTEX_SHADER,   rel::RES_PATH + "shaders/entity/shader.vert" },
    { GL_FRAGMENT_SHADER, rel::RES_PATH + "shaders/entity/shader.frag" }
  };

  glm::vec2 scale( 0.25f, 0.5f );
  std::vector< float > vboData;

  // center
  vboData.push_back( 0.0f );
  vboData.push_back( 0.0f );

  // circumference
  for ( auto i = 1; i < numVertsPerShape_; ++i )
  {
    float angle = ( i - 1 ) * glm::two_pi< float >( ) / ( numVertsPerShape_ - 2 );
    vboData.push_back( glm::cos( angle ) * scale.x );
    vboData.push_back( glm::sin( angle ) * scale.y );
  }

  std::vector< shg::VAOElement > vaoElements =
  {
    { "inXYCoords", 2, GL_FLOAT, nullptr }
  };

  glIds_ = shg::OpenGLHelper::createStandardPipeline(
                                                     shaders,
                                                     vboData.data( ),
                                                     vboData.size( ),
                                                     0,
                                                     vaoElements
                                                     );
} // FlatlandEntity::_prepGLPipeline



} // namespace rel
