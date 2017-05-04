#version 410 core
#extension GL_ARB_conservative_depth : enable

//
// middle, radius, cornerRadius, pixelSize
//
uniform vec4 M_R_CR_PS;


//
// will only increase depth value
//
layout ( depth_greater ) out float gl_FragDepth;


void main( void )
{
  float middle       = M_R_CR_PS.x;
  float radius       = M_R_CR_PS.y;
  float cornerRadius = M_R_CR_PS.z;
  float pixelSize    = M_R_CR_PS.w;

  float centerRadius = radius - cornerRadius;

  //
  // point relative to center of tool
  //
  vec2 p = ( gl_FragCoord.xy - vec2( middle ) ) * pixelSize;

  float distance = length( p );

  //
  // final output height
  //
  float finalHeight;

  //
  // flat middle portion of tool
  //
  if ( distance < centerRadius )
  {
    finalHeight = 1.0; // normalized height
  }

  //
  // rounded "corner" section of tool
  //
  else if ( distance < radius )
  {
    float cornerDistance = distance - centerRadius;
    float height         = sqrt( cornerRadius * cornerRadius
                                 - cornerDistance * cornerDistance );
    // normalized height
    finalHeight = height / cornerRadius;
  }

  //
  // outside tool range
  //
  else
  {
    finalHeight = 0.0;
  }

  //
  // invert heights for now
  //
  finalHeight = 1.0 - finalHeight;

  //
  // normalize for depth values
  //
  float far   = gl_DepthRange.far;
  float near  = gl_DepthRange.near;
  float range = far - near;

  gl_FragDepth = finalHeight * range + near;
}
