/*************************************************************************//**
* @file
*****************************************************************************/
#include <iostream>
#include "util.h"
#include "mouse.h"
#include "gameboard.h"

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
    Gameboard g;
   static Mouse mouse;

    //switch the enum containing type of event
    //call appropriate function in container
    switch (event.event)
    {
    case INIT:
        {
           break;
        } 
    case DISPLAY:
        {
#ifdef DEBUG
            cout << "Display Event" << endl;
#endif
            break;
        }
    case KEYBOARD:
        g.letterEnterGuess(event.key);
        break;
    case MOUSECLICK:
        mouse.mouseClick(event.button, event.state, event.x, event.y);
        if (mouse.mouseClicked())
#ifdef DEBUG
           cout << "Mouse click event at [" << event.x << ", " << event.y << "]" << endl;
#endif
        break;
    case MOUSEDRAG:
        mouse.mouseDrag(event.x, event.y);
#ifdef DEBUG
           cout << "Mouse drag event" << endl;
#endif
        break;
    }
}
