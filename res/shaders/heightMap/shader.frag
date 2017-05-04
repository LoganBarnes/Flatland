#version 410

layout( location = 0 ) in float height;


layout( location = 0 ) out vec4 outColor;


void main( void )
{
  vec3 color = vec3( 1.0, 0.0, 0.0 );
  if ( height < 5.0 )
  {
    color = vec3( 1.0, 1.0, 0.0 );
  }
  else if ( height < -5.0 )
  {
    color = vec3( 0.0, 0.0, 1.0 );
  }

  outColor = vec4( color, 1.0 );
}
