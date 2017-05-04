// Grid.hpp
#pragma once

#include "shared/graphics/GraphicsForwardDeclarations.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace rel
{

class Grid
{
public:

  explicit
  Grid(
       glm::vec3 minPos,
       glm::vec3 maxPos,
       glm::vec3 spacing,
       glm::vec3 color = glm::vec3( 1.0f )
       );


  void render ( const shg::GlmCamera< float > &camera ) const;


private:

  void _buildGLPipeline ( );

  const std::vector< float > _buildVBO ( ) const;

  shg::StandardPipeline glIds_;
  glm::vec3 minPos_;
  glm::vec3 maxPos_;
  glm::vec3 spacing_;

  glm::vec3 color_;

  int numVerts_;
};

} // namespace rel
