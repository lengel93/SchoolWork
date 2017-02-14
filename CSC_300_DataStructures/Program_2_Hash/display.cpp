#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "util.h"
#include "constants.h"
//#include "mouse.h"
#include "display.h"

using namespace std;


void display( void )
{       
  // clear the display
  glClear( GL_COLOR_BUFFER_BIT );

  utilityCentral(Event());
  glutSwapBuffers();
}

// from Dr. Weiss's example
void DrawTextString ( string str, int x, int y, const float color [] )
{
    int i = 0;
    int end = str.length();

    glColor3fv( color );
    glRasterPos2i ( x, y );
    while ( i != end )
    {
        glutBitmapCharacter ( GLUT_BITMAP_8_BY_13, str[i] );
        i++;
    }

}

// from Dr. Weiss's example
void drawRectangle ( int x1, int y1, int x2, int y2, const float color[] )
{
    glColor3fv ( color );
    glBegin ( GL_POLYGON );
    
    glVertex2f ( x1, y1 );
    glVertex2f ( x2, y1 );
    glVertex2f ( x2, y2 );
    glVertex2f ( x1, y2 );
    
    glEnd();
    glFlush(); 
}

xy getDim(int tabsize)
{
  int track = tabsize;
  int temp = 0;
  float row = 1;
  float col = tabsize;
  xy ret;

  while(row < col/5)
    {
      if (track%2 != 0)
	temp += 1;

      track /= 2;
      row *= 2;
      col /= 2;
    }
  ret.y = row;
  if (temp)
    ret.y += 1;
  ret.x = col;

  //cout << "h = " << ret.y << " and w = " << ret.x << endl;
  return ret;
}

xy getSize(xy dim)
{
  int totx, toty;
  xy ret;
  
  totx = winWidth - (4 * dim.x + 4);
  toty = winHeight - (4 * dim.y + 4) - 15;
  
  ret.x = totx / dim.x;
  ret.y = toty / dim.y;

  if (ret.x <= 2 || ret.y <= 1)
    {
      ret.x = minPixx;
      ret.y = minPixy;
    }
  
  return ret;
}