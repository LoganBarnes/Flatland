#version 410 core
#extension GL_ARB_conservative_depth : enable


layout( location = 0 ) in vec2 texCoords;


uniform sampler2D toolTex;


out float gl_FragDepth;


void main( void )
{
  float near  = gl_DepthRange.near;
  float far   = gl_DepthRange.far;
  float range = far - near;

  float depth = texture( toolTex, texCoords ).r;

  gl_FragDepth = range * depth + near;
}
