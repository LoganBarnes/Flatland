// Grid.cpp
#include "Grid.hpp"
#include "RelativityConfig.hpp"

#include "shared/graphics/OpenGLHelper.hpp"
#include "shared/graphics/GlmCamera.hpp"

#include <glm/gtc/type_ptr.hpp>


namespace rel
{

Grid::Grid(
           glm::vec3 minPos,
           glm::vec3 maxPos,
           glm::vec3 spacing,
           glm::vec3 color
           )
  : minPos_ ( minPos )
  , maxPos_ ( maxPos )
  , spacing_( spacing )
  , color_  ( color )
  , numVerts_( 0 )
{
  _buildGLPipeline( );
}



void
Grid::render( const shg::GlmCamera< float > &camera ) const
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
                                     "minZ",
                                     &minPos_.z
                                     );
  shg::OpenGLHelper::renderBuffer(
                                  glIds_.vao,
                                  0,
                                  numVerts_,
                                  GL_LINES
                                  );
} // Grid::render



void
Grid::_buildGLPipeline( )
{
  glIds_.program =
    shg::OpenGLHelper::createProgram(
                                     rel::RES_PATH + "shaders/grid/shader.vert",
                                     rel::RES_PATH + "shaders/grid/shader.frag"
                                     );

  const std::vector< float > vboData = _buildVBO( );
  numVerts_ = static_cast< int >( vboData.size( ) ) / 3;

  glIds_.vbo = shg::OpenGLHelper::createBuffer(
                                               vboData.data( ),
                                               vboData.size( )
                                               );

  std::vector< shg::VAOElement > vaoElements =
  {
    { "inSpacetime", 3, GL_FLOAT, 0 }
  };

  glIds_.vao = shg::OpenGLHelper::createVao(
                                            glIds_.program,
                                            glIds_.vbo,
                                            0,
                                            vaoElements
                                            );

} // Grid::_buildGLPipeline



const std::vector< float >
Grid::_buildVBO( ) const
{
  std::vector< float > vbo;

  glm::vec3 range = maxPos_ - minPos_;
  glm::ivec3 divisions( glm::floor( range / spacing_ ) );

  //////////////////////////////////////
  // parallel to z-axis:
  //////////////////////////////////////

  //
  // "floor"
  //
  for ( auto xi = 0; xi < divisions.x; ++xi )
  {
    float x = minPos_.x + xi * spacing_.x;
    vbo.push_back( x );
    vbo.push_back( minPos_.y );
    vbo.push_back( minPos_.z );
    vbo.push_back( x );
    vbo.push_back( minPos_.y );
    vbo.push_back( maxPos_.z );
  }

  vbo.push_back( maxPos_.x );
  vbo.push_back( minPos_.y );
  vbo.push_back( minPos_.z );
  vbo.push_back( maxPos_.x );
  vbo.push_back( minPos_.y );
  vbo.push_back( maxPos_.z );

  //
  // "walls"
  //
  for ( auto yi = 1; yi < divisions.y; ++yi )
  {
    float y = minPos_.y + yi * spacing_.y;
    // min
    vbo.push_back( minPos_.x );
    vbo.push_back( y );
    vbo.push_back( minPos_.z );
    vbo.push_back( minPos_.x );
    vbo.push_back( y );
    vbo.push_back( maxPos_.z );
    // max wall
    vbo.push_back( maxPos_.x );
    vbo.push_back( y );
    vbo.push_back( minPos_.z );
    vbo.push_back( maxPos_.x );
    vbo.push_back( y );
    vbo.push_back( maxPos_.z );
  }

  // min
  vbo.push_back( minPos_.x );
  vbo.push_back( maxPos_.y );
  vbo.push_back( minPos_.z );
  vbo.push_back( minPos_.x );
  vbo.push_back( maxPos_.y );
  vbo.push_back( maxPos_.z );
  // max wall
  vbo.push_back( maxPos_.x );
  vbo.push_back( maxPos_.y );
  vbo.push_back( minPos_.z );
  vbo.push_back( maxPos_.x );
  vbo.push_back( maxPos_.y );
  vbo.push_back( maxPos_.z );


  //////////////////////////////////////
  // perpendicular to z-axis:
  //////////////////////////////////////

  for ( auto zi = 0; zi < divisions.z; ++zi )
  {
    float z = minPos_.z + zi * spacing_.z;
    // floor
    vbo.push_back( minPos_.x );
    vbo.push_back( minPos_.y );
    vbo.push_back( z );
    vbo.push_back( maxPos_.x );
    vbo.push_back( minPos_.y );
    vbo.push_back( z );
    // min wall
    vbo.push_back( minPos_.x );
    vbo.push_back( minPos_.y );
    vbo.push_back( z );
    vbo.push_back( minPos_.x );
    vbo.push_back( maxPos_.y );
    vbo.push_back( z );
    // max wall
    vbo.push_back( maxPos_.x );
    vbo.push_back( minPos_.y );
    vbo.push_back( z );
    vbo.push_back( maxPos_.x );
    vbo.push_back( maxPos_.y );
    vbo.push_back( z );
  }

  // floor
  vbo.push_back( minPos_.x );
  vbo.push_back( minPos_.y );
  vbo.push_back( maxPos_.z );
  vbo.push_back( maxPos_.x );
  vbo.push_back( minPos_.y );
  vbo.push_back( maxPos_.z );
  // min wall
  vbo.push_back( minPos_.x );
  vbo.push_back( minPos_.y );
  vbo.push_back( maxPos_.z );
  vbo.push_back( minPos_.x );
  vbo.push_back( maxPos_.y );
  vbo.push_back( maxPos_.z );
  // max wall
  vbo.push_back( maxPos_.x );
  vbo.push_back( minPos_.y );
  vbo.push_back( maxPos_.z );
  vbo.push_back( maxPos_.x );
  vbo.push_back( maxPos_.y );
  vbo.push_back( maxPos_.z );

  return vbo;
} // Grid::_buildVBO



} // namespace rel
