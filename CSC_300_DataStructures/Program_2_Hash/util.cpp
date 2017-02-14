/*************************************************************************//**
* @file
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

#include "constants.h"
#include "util.h"
#include "mouse.h"
#include "display.h"

using namespace std;





/**************************************************************************//**
 * @author Paul Hinker
 *
 * @par Description:
 * This function gets called when an event happens in callbacks. Depending on 
 * the enum and data passed in it will do different things. When a mouse click 
 * is passed in, it sends that data to the click function in the container 
 * class screen. When a mouse drag is sent in, it sends it to the clickAndDrag 
 * function in screen.  It does the same for keyboard presses, sending them to 
 * keyboardAction in screen.
 *
 * @param[in] event - structure that contains data about the event to handle
 *****************************************************************************/
void utilityCentral(Event event)
{
  switch (event.event)
    {
    case INIT:
	break;
	
    case DISPLAY:
#ifdef DEBUG
	cout << "Display Event" << endl;
#endif
	break;
	
case KEYBOARD:
#ifdef DEBUG
      cout << "Keyboard event" << endl;
#endif
      break;
	
    case RESIZE:
#ifdef DEBUG
      cout << "Yes" << endl;
#endif
      break;
    }
	//glutSwapBuffers();

}
