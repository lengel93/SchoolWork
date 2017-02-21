#include <iostream>
#include "Shape3D.h"
#include "math.h"
#include <gtest/gtest.h>
#define _USE_MATH_DEFINES 


/*
*Cube Constructor, fills Side and Location
*/
Cube::Cube(Point& p, double s) : Shape3D(p)
{
	side = s;
}

/*
*Checks if a point is located inside a cube. It does this
*adding and substruct the center point of the cube by 1/2
*the size of side. Thus creating bounds.
*/
bool Cube::contains(Point& p)
{
	double xmax, ymax, zmax;
	double xmin, ymin, zmin;

	xmax = Location.getx() + side*.5;
	xmin = Location.getx() - side*.5;
	ymax = Location.gety() + side*.5;
	ymin = Location.gety() - side*.5;
	zmax = Location.getz() + side*.5;
	zmin = Location.getz() - side*.5;

	if (p.getx() < xmin || p.gety() < ymin || p.getz() < zmin
		|| p.getx() > xmax || p.gety() > ymax || p.getz() > zmax)
	{
		return false;
	}
	else
		return true;
}

/*
*Checks for the voume of a cube
*/
double Cube::volume()
{
	return side * side * side;
}