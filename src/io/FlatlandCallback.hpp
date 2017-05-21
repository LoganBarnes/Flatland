// FlatlandCallback.hpp
#pragma once

#include "shared/graphics/SharedCallback.hpp"

namespace rel
{

class FlatlandIOHandler;


class FlatlandCallback : public shs::SharedCallback
{
public:

  FlatlandCallback( FlatlandIOHandler &flatHandler );

  virtual
  ~FlatlandCallback( );


//   virtual
//   void handleMouseButton (
//                           GLFWwindow *pWindow,
//                           int         button,
//                           int         action,
//                           int         mods
//                           );

  virtual
  void handleKey (
                  GLFWwindow *pWindow,
                  int         key,
                  int         scancode,
                  int         action,
                  int         mods
                  );

   virtual
   void handleCursorPosition (
                              GLFWwindow *pWindow,
                              double      xpos,
                              double      ypos
                              );

   virtual
   void handleScroll (
                      GLFWwindow *pWindow,
                      double      xoffset,
                      double      yoffset
                      );


private:

  FlatlandIOHandler &flatHandler_;

  bool leftMouseDown_;
  bool rightMouseDown_;

  double prevX_;
  double prevY_;

};


} // namespace rel
