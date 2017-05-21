// FlatlandCallback.cpp
#include "FlatlandCallback.hpp"
#include "FlatlandIOHandler.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>



namespace rel
{


FlatlandCallback::FlatlandCallback( FlatlandIOHandler &flatHandler )
  : shs::SharedCallback( &flatHandler )
  , flatHandler_   ( flatHandler )
  , leftMouseDown_ ( false )
  , rightMouseDown_( false )
{}



FlatlandCallback::~FlatlandCallback( )
{}



// void
// FlatlandCallback::handleMouseButton(
//                                    GLFWwindow *pWindow,
//                                    int         button,
//                                    int         action,
//                                    int
//                                    )
// {
//   if ( button == GLFW_MOUSE_BUTTON_1 )
//   {
//     if ( action == GLFW_PRESS )
//     {
//       leftMouseDown_ = true;
//       glfwGetCursorPos( pWindow, &prevX_, &prevY_ );

//       quadrant_ = Quadrant::NUM_QUADRANT_TYPES;
//       auto xyPair = getRelativeScreenspace( pWindow, prevX_, prevY_ );

//       if ( xyPair.first != 0.0f || xyPair.second != 0.0f )
//       {
//         handler_.setPointScreenSpace( xyPair.first, xyPair.second );
//       }
//     }
//     else
//     {
//       leftMouseDown_ = false;
//     }
//   }
//   else
//   if ( button == GLFW_MOUSE_BUTTON_2 )
//   {
//     if ( action == GLFW_PRESS )
//     {
//       rightMouseDown_ = true;
//       glfwGetCursorPos( pWindow, &prevX_, &prevY_ );
//     }
//     else
//     {
//       rightMouseDown_ = false;
//     }
//   }
// } // handleMouseButton



void
FlatlandCallback::handleKey(
                            GLFWwindow *pWindow,
                            int         key,
                            int         scancode,
                            int         action,
                            int         mods
                            )
{
  SharedCallback::handleKey( pWindow, key, scancode, action, mods );

  glm::ivec3 moveDir( 0 );

  if ( action == GLFW_PRESS )
  {
    switch ( key )
    {
    case GLFW_KEY_W:
      moveDir.x += 1;
      break;

    case GLFW_KEY_A:
      moveDir.y -= 1;
      break;

    case GLFW_KEY_S:
      moveDir.x -= 1;
      break;

    case GLFW_KEY_D:
      moveDir.y += 1;
      break;

    case GLFW_KEY_E:
      moveDir.z += 1;
      break;

    case GLFW_KEY_Q:
      moveDir.z -= 1;
      break;

    default:
      break;
    } // switch

  }
  else
  if ( action == GLFW_RELEASE )
  {
    switch ( key )
    {
    case GLFW_KEY_W:
      moveDir.x -= 1;
      break;

    case GLFW_KEY_A:
      moveDir.y += 1;
      break;

    case GLFW_KEY_S:
      moveDir.x += 1;
      break;

    case GLFW_KEY_D:
      moveDir.y -= 1;
      break;

    case GLFW_KEY_E:
      moveDir.z -= 1;
      break;

    case GLFW_KEY_Q:
      moveDir.z += 1;
      break;

    default:
      break;
    } // switch

  }

  flatHandler_.addFRUCameraMovement( moveDir );

} // FlatlandCallback::handleKey



 void
 FlatlandCallback::handleCursorPosition(
                                       GLFWwindow *,
                                       double      xpos,
                                       double      ypos
                                       )
 {
   if ( leftMouseDown_ )
   {}
   else
   if ( rightMouseDown_ )
   {}

   prevX_ = xpos;
   prevY_ = ypos;
 } // handleCursorPosition



 void
 FlatlandCallback::handleScroll(
                               GLFWwindow*,
                               double,
                               double
                               )
 {}



} //  namespace rel
