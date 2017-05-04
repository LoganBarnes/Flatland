// RelativityEntity.cpp
#include "RelativityEntity.hpp"
#include "RelativityConfig.hpp"

// shared
#include "shared/graphics/OpenGLHelper.hpp"
#include "shared/graphics/GlmCamera.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>


namespace rel
{


///////////////////////////////////////////////////////////////
/// \brief RelativityEntity::RelativityEntity
///////////////////////////////////////////////////////////////
RelativityEntity::RelativityEntity( float maxTime )
  : numVertsPerShape_( 32 )
  , maxTime_( maxTime )
  , color_( 0.1f, 0.5f, 0.9f )
{
  _prepGLPipeline( );
}



///////////////////////////////////////////////////////////////
/// \brief RelativityEntity::move
///////////////////////////////////////////////////////////////
void
RelativityEntity::move( const double /*dt*/ )
{}


void
RelativityEntity::render( const shg::GlmCamera< float > &camera ) const
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
} // RelativityEntity::render



void
RelativityEntity::_prepGLPipeline( )
{
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

  glIds_ =
    shg::OpenGLHelper::createStandardPipeline(
                                              rel::RES_PATH + "shaders/entity/shader.vert",
                                              rel::RES_PATH + "shaders/entity/shader.frag",
                                              vboData.data( ),
                                              vboData.size( ),
                                              0,
                                              vaoElements
                                              );
} // RelativityEntity::_prepGLPipeline



} // namespace rel
