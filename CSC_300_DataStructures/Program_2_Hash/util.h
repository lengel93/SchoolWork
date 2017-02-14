/*************************************************************************//**
 * @file
 ****************************************************************************/
#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED
#include <string>
#include <vector>

using namespace std;

/// convenience typedef
typedef unsigned char byte;


/// Event enum to describing events
enum EventType
{
    INIT,
    DISPLAY,
    KEYBOARD,
    RESIZE
};

/*!
* @brief Contains information about the event that is happening
* and constructors that assign enums and data depending on what is
* passed in.  Depending on the complexity of the application, the event
* structure might need to be extended.
*/
struct Event
{
    /** \brief type of event to handle */
    EventType event;
    /** \brief keyboard key pressed by user */
    unsigned char key;
    /** \brief mouse button pressed */
    int button;
    /** \brief mouse button position (up or down) */
    int state;
    /** \brief x-coordinate of mouseclick */
    int x;
    /** \brief x-coordinate of mouseclick */
    int y;
 
    /** \brief if there are no other params, display routine */
Event() :
  event(DISPLAY) {}
  /** \brief the call from initOpenGL */
Event(int rows, int cols) : 
  event(INIT), x(rows), y(cols) {}
Event(unsigned char k, int xPos, int yPos) :
  event(KEYBOARD), key(k), x(xPos), y(yPos) {}
Event(int size, vector <int> colors) :
  event(RESIZE) {}
};

/// The main hub for collecting the various events into a central location
void utilityCentral(Event event);


#endif // UTIL_H_INCLUDED
