// FlatlandEntity.hpp
#pragma once

#include <glm/glm.hpp>
#include "shared/graphics/GraphicsForwardDeclarations.hpp"


struct State
{
  glm::vec3 spacetime_ = glm::vec3( 0.0f ); // m,m,s (2D spacial plus time)
  glm::vec2 vel_       = glm::vec2( 0.0f ); // m
  float mass_          = 1.0f;              // kg
};


namespace rel
{


/////////////////////////////////////////////
/// \brief The FlatlandEntity class
///
/// \author Logan Barnes
/////////////////////////////////////////////
class FlatlandEntity
{

public:

  ///////////////////////////////////////////////////////////////
  /// \brief FlatlandEntity
  ///////////////////////////////////////////////////////////////
  FlatlandEntity( float maxTime );


  ///////////////////////////////////////////////////////////////
  /// \brief move
  ///////////////////////////////////////////////////////////////
  void move ( const double dt );


  ///////////////////////////////////////////////////////////////
  /// \brief render
  ///////////////////////////////////////////////////////////////
  void render ( const shg::GlmCamera< float > &camera ) const;


private:

  void _prepGLPipeline ( );

  State prevState_;
  State currState_;

  shg::StandardPipeline glIds_;

  int numVertsPerShape_;

  float maxTime_;
  glm::vec3 color_;


};


} // namespace rel
