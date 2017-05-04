#version 410
#extension GL_ARB_separate_shader_objects : enable


layout( location = 0 ) in vec2 inXZCoords;
layout( location = 1 ) in vec2 inTexCoords;


uniform sampler2D heightTex;
uniform mat4 projectionView;


layout( location = 0 ) out float height;


out gl_PerVertex
{
  vec4 gl_Position;
};


void main( void )
{
  height = texture( heightTex, inTexCoords ).r;

  gl_Position = projectionView * vec4( inXZCoords.x, height, inXZCoords.y, 1.0 );
}
