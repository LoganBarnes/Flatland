#version 410 core
#extension GL_ARB_separate_shader_objects : enable


layout( location = 0 ) in vec3 inPlanePos;
layout( location = 1 ) in vec2 inTexCoords;


uniform vec2 planeSize = vec2( 2.0 );


layout( location = 0 ) out vec2 texCoords;


out gl_PerVertex
{
  vec4 gl_Position;
};


void main( void )
{
  vec2 radius    = planeSize * 0.5;
  vec2 screenPos = ( inPlanePos.xy - radius ) / radius;

  texCoords = inTexCoords;

  gl_Position = vec4( screenPos, inPlanePos.z, 1.0 );
}
