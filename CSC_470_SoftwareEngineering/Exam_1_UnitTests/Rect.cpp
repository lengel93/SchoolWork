#include <iostream>
#include "Shape3D.h"
#include "math.h"
#include <gtest/gtest.h>
#define _USE_MATH_DEFINES 


/*
*Constructor for Rect, fills the Location, width, height
*and depth
*/
RectParPiped::RectParPiped(Point& p, double w, double h, double d) : Shape3D(p)
{
	width = w;
	height = h;
	depth = d;
}

/*
*Checks if a point is located inside a RectPrism. It does this
*adding and substruct the center point of the prism by 1/2
*the size of each of its sides. Thus creating bounds.
*/
bool RectParPiped::contains(Point& p)
{

	double xmax, ymax, zmax;
	double xmin, ymin, zmin;

	xmax = Location.getx() + width*.5;
	xmin = Location.getx() - width*.5;
	ymax = Location.gety() + height*.5;
	ymin = Location.gety() - height*.5;
	zmax = Location.getz() + depth*.5;
	zmin = Location.getz() - depth*.5;

	if (p.getx() < xmin || p.gety() < ymin || p.getz() < zmin
		|| p.getx() > xmax || p.gety() > ymax || p.getz() > zmax)
	{
		return false;
	}
	return true;
}

/*
*Calculates the volume of the rectangular prism.
*/
double RectParPiped::volume()
{
	return width*height*depth;
}
