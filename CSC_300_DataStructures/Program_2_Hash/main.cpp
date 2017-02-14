#include "hash.h"
#include <stdlib.h>
#include <chrono>
#include <thread>
#include "constants.h"
#include "util.h"
#include "display.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

// Handler for reshape events
void reshape( int w, int h );
// Handler for keyboard events
void keyboard( unsigned char key, int x, int y );
// Handler for mouse click events
void mouseClick(int button, int state, int x, int y);
// Handler for mouse motion (i.e. drag) events
void mouseMotion(int x, int y);
// Background hash calculations
void whenIdle(int val);
// Function to do the initialization of the openGL event handlers
void initOpenGL( const char *filename, int nrows, int ncols);

int main(int argc, char *argv[])
{
  glutInit( &argc, argv );
  initOpenGL( argv[1], winHeight, winWidth);

  glutMainLoop();
  
  return 0;
}

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
    glutTimerFunc(0, whenIdle, 0);
}

void reshape( int w, int h )
{
    // how to project 3-D scene onto 2-D
    glMatrixMode( GL_PROJECTION );    // use an orthographic projection
    glLoadIdentity();		      // initialize transformation matrix
    gluOrtho2D( 0.0, w, 0.0, h );
    glViewport( 0, 0, w, h );	      // adjust viewport to new window
    glutPostRedisplay();
}


// callback function that tells OpenGL how to handle keystrokes
void keyboard( unsigned char key, int x, int y )
{
   if (key == EscapeKey)
      exit(0);

   utilityCentral(Event(key, x, y));
   //glutPostRedisplay();
}

// Transfer mouse click events to the central processing function
void mouseClick(int button, int state, int x, int y)
{
  //utilityCentral(Event(button, state, x, y));
}

// Transfer mouse movement events to the central processing function
void mouseMotion(int x, int y)
{
  //utilityCentral(Event(MOUSEDRAG, x, y));
   glutPostRedisplay();
   }

void whenIdle(int val)
{
  int k, i;
  xy dim, tileSize;
  vector <int> colors;
  fstream fin;
  string word;
  string key;
  
  Hash<string, string> Hash;
  
  fin.open("test.dat");
  
  dim = getDim(Hash.size());
  tileSize = getSize(dim);
  redisplay(tileSize, dim, Hash.size(), Hash);
  i = 0;
  k = 0;
  while (fin >> word)
    {
      i = i +1;
      key = word;
      //word = i;
      Hash.insert(key,word);
      
      dim = getDim(Hash.size());
      tileSize = getSize(dim);
      if (Hash.size() < 500)
	redisplay(tileSize, dim, Hash.size(), Hash);

      else if (Hash.size() < 5000 && k >= 20)
	{
	  redisplay(tileSize, dim, Hash.size(), Hash);
	  k = 0;
	}

      else if (Hash.size() < 10000 && k >= 100)
	{
	  redisplay(tileSize, dim, Hash.size(), Hash);
	  k = 0;
	}

      else if (Hash.size() < 20000 && k >= 200)
	{
	  redisplay(tileSize, dim, Hash.size(), Hash);
	  k = 0;
	}
      
      else if (Hash.size() < 50000 && k >= 1000)
      {
	 redisplay(tileSize, dim, Hash.size(), Hash);
	 k = 0;
      }

      else if (Hash.size() < 100000 && k >= 10000)
	{
	  redisplay(tileSize, dim, Hash.size(), Hash);
	  k = 0;
	}

      else if (k >= 100000)
	{
	  redisplay(tileSize, dim, Hash.size(), Hash);
	  k = 0;
	}
      k++;
      //Hash.print();
    }

  redisplay(tileSize, dim, Hash.size(), Hash);
   
  fin.close();
}