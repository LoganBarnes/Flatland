#version 410 core
#extension GL_ARB_separate_shader_objects : enable


layout( location = 0 ) in vec3 inScreenPos;


out gl_PerVertex
{
  vec4 gl_Position;
};


void main( void )
{
  gl_Position = vec4( inScreenPos, 1.0 );
}
