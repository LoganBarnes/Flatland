#version 410


//uniform sampler2D tex;
uniform vec2 framebufferSize = vec2( 2.0 );


layout( location = 0 ) out vec4 outColor;


void main( void )
{
  vec2 screenPos = gl_FragCoord.xy / framebufferSize;
  screenPos = screenPos * 2.0 - 1.0;

  outColor = vec4( screenPos * 0.5 + 0.5, 1.0, 1.0 );
}
