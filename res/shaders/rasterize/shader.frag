#version 410 core

layout( location = 0 ) in vec2 texCoords;


uniform sampler2D tex;


layout( location = 0 ) out vec4 outColor;


void main( void )
{
  outColor = vec4( texCoords, 1.0, 1.0 );
}
