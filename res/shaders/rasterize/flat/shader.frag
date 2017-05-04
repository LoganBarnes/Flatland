#version 410


//uniform sampler2D tex;
uniform vec2 framebufferSize = vec2( 2.0 );


layout( location = 0 ) out vec4 outColor;


float tMin = 0.0;
float tMax = 1.0 / 0.0; // INF?


float
min3( in vec3 v )
{
  return min( min( v.x, v.y ), v.z );
}

float
max3( in vec3 v )
{
  return max( max( v.x, v.y ), v.z );
}


///
/// \brief rtPotentialIntersection
///
/// Somewhat mimics the optix function of the same name.
/// Checks the current t value against the global min and max.
///
bool
rtPotentialIntersection( in float t )
{
  return t > tMin && t < tMax;
}


///
/// \brief rtReportIntersection
///
/// Somewhat mimics the optix function of the same name.
/// Resets the global minimum intersection distance
///
void
rtReportIntersection( in float t )
{
  tMin = t;
}



void
intersect_cube(
               in vec3  origin,
               in vec3  direction,
               in float minT
               )
{
  vec3  t0   = ( vec3( -1.0 ) - origin ) / direction;
  vec3  t1   = ( vec3(  1.0 ) - origin ) / direction;
  vec3  near = min( t0, t1 );
  vec3  far  = max( t0, t1 );
  float tmin = max3( near );
  float tmax = min3( far );

  if ( tmin <= tmax )
  {
    if ( rtPotentialIntersection( tmin ) )
    {
      rtReportIntersection( tmin );
      return;
    }

    if ( rtPotentialIntersection( tmax ) )
    {
      rtReportIntersection( tmax );
    }
  }
}



void main( void )
{
  ///\todo set tMax based on current texture height

  vec2 screenPos = gl_FragCoord.xy / framebufferSize;
  screenPos = screenPos * 2.0 - 1.0;

  outColor = vec4( screenPos, 0.0, 1.0 );
}
