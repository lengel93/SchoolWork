#ifndef __DISPLAY__H__
#define __DISPLAY__H__
#include <string>
#include <vector>
#include "hash.h"
#include "constants.h"

using namespace std;

#ifdef __APPLE__
  #include <GLUT/glut.h>
  #include <OpenGL/OpenGL.h>
#else
  #include <GL/glut.h>
#endif

void display( void );
void DrawTextString ( string string, int x, int y, const float color [] );
void drawRectangle ( int x1, int y1, int x2, int y2, const float color[] );
xy getDim(int tabsize);
xy getSize(xy dim);
char * d2s(double num);
char * i2s(int num);


template <typename K, typename V>
  void redisplay(xy tileSize, xy dim, int tabsize, Hash <K, V> &hashtab)
{
  int i, j, x1, x2, y1, y2, lesssize, k;
  int * probedarr;
  string out;
  // clear the display
	  glClear( GL_COLOR_BUFFER_BIT );

	  x1 = 4;
	  if (tileSize.x == minPixx)
	    x2 = tileSize.x;
	  else
	    x2 = tileSize.x + 4;
	  
	  y1 = 4;
	  if (tileSize.y == minPixy)
	    y2 = tileSize.y;
	  else
	    y2 = tileSize.y + 4;
	  
	  lesssize = tabsize / dim.x;
	  i = 0;
	  k = 0;

	  probedarr = hashtab.bucketProbed();
	  for (; i < lesssize; i++)
	    {
	      j = 0;
	      for (; j < dim.x; j++)
		{
		 if (probedarr[k] == 0)
		   drawRectangle(x1, y1, x2, y2, white);
		 
		 else if (probedarr[k] > 0 && probedarr[k] <= 2)
		   drawRectangle(x1, y1, x2, y2, blue);
		 
		 else if (probedarr[k] > 2 && probedarr[k] <= 4)
		   drawRectangle(x1, y1, x2, y2, green);
		 
		 else if (probedarr[k] > 4 && probedarr[k] <= 6)
		   drawRectangle(x1, y1, x2, y2, gold);
		 
		 else if (probedarr[k] > 6 && probedarr[k] <= 8)
		   drawRectangle(x1, y1, x2, y2, orange);
		 
		 else if (probedarr[k] > 8)
		   drawRectangle(x1, y1, x2, y2, red);
		  
		  tabsize -= 1;
		  if (tileSize.x == minPixx)
		    {
		      x1 += tileSize.x;
		      x2 += tileSize.x;
		    }
		  else
		    {	
		      x1 += tileSize.x + 4;
		      x2 += tileSize.x + 4;
		    }
		  k++;
		}
	      x1 = 4;
	      if (tileSize.x == minPixx)
		x2 = tileSize.x;
	      else
		x2 = tileSize.x + 4;

	      if (tileSize.y == minPixy)
		{
		  y1 += tileSize.y;
		  y2 += tileSize.y;
		}
	      else
		{
		  y1 += tileSize.y + 4;
		  y2 += tileSize.y + 4;
		}
	    }
	  while (tabsize > 0) 
	    {
	      if (probedarr[k] == 0)
		   drawRectangle(x1, y1, x2, y2, white);
		 
		 else if (probedarr[k] > 0 && probedarr[k] <= 2)
		   drawRectangle(x1, y1, x2, y2, blue);
		 
		 else if (probedarr[k] > 2 && probedarr[k] <= 4)
		   drawRectangle(x1, y1, x2, y2, green);
		 
		 else if (probedarr[k] > 4 && probedarr[k] <= 6)
		   drawRectangle(x1, y1, x2, y2, gold);
		 
		 else if (probedarr[k] > 6 && probedarr[k] <= 8)
		   drawRectangle(x1, y1, x2, y2, orange);
		 
		 else if (probedarr[k] > 8)
		   drawRectangle(x1, y1, x2, y2, red);
	      
	      tabsize -= 1;
	      if (tileSize.x == minPixx)
		{
		  x1 += tileSize.x;
		  x2 += tileSize.y;
		}
	      else
		{	
		  x1 += tileSize.x + 4;
		  x2 += tileSize.x + 4;
		}
	      k++;
	    }

	  //d2s(hashtab.loadFactor());
	  out = "Load Factor: ";
	  out += to_string(hashtab.loadFactor() * 100);
	  out += "% ; Max Frequency: ";
	  out += to_string(hashtab.maxFreq);
	  out += " ; Most Frequent Key: ";
	  out += hashtab.maxKey;
	  
	  DrawTextString (out , ((winWidth/2)-200), (winHeight-15), white);

	  
	  //utilityCentral(Event());
	  glutSwapBuffers();
}
#endif