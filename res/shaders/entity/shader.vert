#version 410 core
#extension GL_ARB_separate_shader_objects : enable

layout( location = 0 ) in vec2 inXYCoords;


uniform mat4  projectionViewMatrix;
uniform int   numIdsPerShape;
uniform float timeStep;
uniform vec3  color;
uniform float maxTime;


layout( location = 0 ) out vec3 clr;


out gl_PerVertex
{
  vec4 gl_Position;
};


void main( void )
{
  // int   shapeNum = mod( gl_VertexID, numIdsPerShape );
  // float time     = timeStep * shapeNum;
  float time     = 0.0;

  float fade = ( maxTime - time ) / maxTime;
  fade *= fade; // quadradic fade
  clr = color * fade;

  gl_Position = projectionViewMatrix * vec4( inXYCoords.xy, -time, 1.0 );
}
