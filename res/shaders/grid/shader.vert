#version 410 core
#extension GL_ARB_separate_shader_objects : enable

layout( location = 0 ) in vec3 inSpacetime;


uniform mat4 projectionViewMatrix;
uniform vec3 color;
uniform float minZ;


layout( location = 0 ) out vec3 clr;


out gl_PerVertex
{
  vec4 gl_Position;
};


void main( void )
{
  float fade = ( minZ - inSpacetime.z ) / minZ;
  fade *= fade; // quadradic fade
  clr = color * fade;
  gl_Position = projectionViewMatrix * vec4( inSpacetime, 1.0 );
}
