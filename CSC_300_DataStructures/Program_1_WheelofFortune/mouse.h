/***************************************************************************//**
 * @file
 ******************************************************************************/
#include <iostream>
#ifdef __APPLE__
  #include <GLUT/glut.h>
  #include <OpenGL/OpenGL.h>
#else
  #include <GL/glut.h>
#endif

/// MouseClicked enum
enum MouseClicked
{
   RIGHT_CLICKED = 1,
   LEFT_CLICKED = 2,
};

/***************************************************************************//**
 * @class Mouse
 *
 * @brief
 *    This class keeps track of mouse information.
 *
 * @par Description
 *    Keeps the mouse state between events.
 ******************************************************************************/
class Mouse
{
   /// Is the left mouse button down
   bool leftDown;
   /// Is the right mouse button down
   bool rightDown;
   /// Was the mouse clicked
   int clicked;
   /// Where was the button down event (x-coord)
   int downX;
   /// Where was the button down event (y-coord)
   int downY;

public:
   /// Constructor
   Mouse(){}
   /// Destructor
   ~Mouse(){}

   /// Called when a mouse click event happens
   void mouseClick(int button, int state, int x, int y);
   /// Called when a mouse drag event is raised
   void mouseDrag(int x, int y);
   /// Boolean telling if a mouse click happen (click is down then up)
   int mouseClicked() { return clicked ; }
};



