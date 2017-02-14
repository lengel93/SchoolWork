/***************************************************************************//**
 * @file
 *
 * @mainpage Wheel of Fortune Game
 *
 * @section course_section Course Information
 *
 * @author Dr. Paul Hinker, Samuel Patzer, Jake Miller, Lyndon Engel, 
 * Jimmy Hinker
 *
 * @par Course:
 *      CSC 300 - M001 - 10:00am
 *
 * @par Location:
 *      McLaury - 205
 *
 * @details Wheel of fortune game that is following the specifications
 * provided by Dr. Hinker. The game is made using OpenGL and glut to draw the
 * gameboard. The Game will run until the user presses escape or selects quit
 * when they lose or win a game. The way a user wins the game is by correctly
 * typing in the word. The user loses the game by guessing the word or letters
 * incorrectly 3 times. 
 *
 ******************************************************************************/

// include files
#include <iostream>
#include <stdlib.h>
#include "util.h"
#include "gameboard.h"

using namespace std;

// the GLUT header automatically includes gl.h and glu.h
#ifdef __APPLE__
  #include <GLUT/glut.h>
  #include <OpenGL/OpenGL.h>
#else
  #include <GL/glut.h>
#endif



/// symbolic constant for the escape key
const int EscapeKey = 27;

/// OpenGL callback function prototypes
/// Display handler
void display( void );
/// Handler for reshape events
void reshape( int w, int h );
/// Handler for keyboard events
void keyboard( unsigned char key, int x, int y );
/// Handler for mouse click events
void mouseClick(int button, int state, int x, int y);
/// Handler for mouse motion (i.e. drag) events
void mouseMotion(int x, int y);

// other function prototypes
/// Function to do the initialization of the openGL event handlers
void initOpenGL( const char *filename, int nrows, int ncols);

/***************************************************************************//**
 * @author Paul Hinker
 *
 * @par Description:
 * A barebones main to use OpenGL and it's callback functionality.
 ******************************************************************************/
int main( int argc, char *argv[] )
{
    // perform various OpenGL initializations
    glutInit( &argc, argv );
    initOpenGL( "Wheel of fortune", 512, 1024);

    // go into OpenGL/GLUT main loop, never to return
    glutMainLoop();

    // Keep the compiler from complaining
    return 0;
}

/***************************************************************************//**
 * @author Paul Hinker
 * 
 * @par Description: Initialize a variety of glut callback functions
 *
 * @param[in] windowTitle - The title to place on the window
 * @param[in] nrows       - Number of pixels for the window height
 * @param[in] ncols       - Number of pixels for the window width
 ******************************************************************************/
// various commands to initialize OpenGL and GLUT
void initOpenGL( const char *windowTitle, int nrows, int ncols)
{
     // 32-bit graphics and single buffering
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

    glutInitWindowSize( ncols, nrows );  // initial window size
    glutInitWindowPosition( 100, 50 );	 // initial window  position
    glutCreateWindow( windowTitle );	 // window title

    utilityCentral(Event());

    glClearColor( 0.0, 0.0, 0.0, 0.0 );	        // use black for glClear command

    // callback routines
    glutDisplayFunc( display );		// how to redisplay window
    glutReshapeFunc( reshape );		// how to resize window
    glutKeyboardFunc( keyboard );	// how to handle key presses
    glutMouseFunc(mouseClick);          // how to handle mouse clicks
    glutMotionFunc(mouseMotion);        // how to handle mouse movements
}

/******************************************************************************/
/*                          OpenGL callback functions                         */
/******************************************************************************/
// callback function that tells OpenGL how to redraw window

void display( void )
{
    // clear the display
    glClear( GL_COLOR_BUFFER_BIT );
    utilityCentral(Event());
    Gameboard();
    //drawWord("a bird jumped across the sky and landed in a pool");
    //Sends the buffered objectes
    glutSwapBuffers();
}

/******************************************************************************/

// callback function that tells OpenGL how to resize window
// note that this is called when the window is first created
void reshape( int w, int h )
{
    // how to project 3-D scene onto 2-D
    glMatrixMode( GL_PROJECTION );    // use an orthographic projection
    glLoadIdentity();		      // initialize transformation matrix
    gluOrtho2D( 0.0, w, 0.0, h );
    glViewport( 0, 0, w, h );	      // adjust viewport to new window
    glutPostRedisplay();
}

/******************************************************************************/

// callback function that tells OpenGL how to handle keystrokes
void keyboard( unsigned char key, int x, int y )
{
   if (key == EscapeKey)
      exit(0);

   utilityCentral(Event(key, x, y));
   glutPostRedisplay();
}

// Transfer mouse click events to the central processing function
void mouseClick(int button, int state, int x, int y)
{
   utilityCentral(Event(button, state, x, y));
}

// Transfer mouse movement events to the central processing function
void mouseMotion(int x, int y)
{
   utilityCentral(Event(MOUSEDRAG, x, y));
   glutPostRedisplay();
}
