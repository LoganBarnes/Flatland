#version 410 core

layout( location = 0 ) in vec3 clr;

layout( location = 0 ) out vec4 outColor;

void main( void )
{
  outColor = vec4( clr, 1.0 );
}
