#include <iostream>
#include "Shape3D.h"
#include "math.h"
#include <gtest/gtest.h>
#define _USE_MATH_DEFINES 


/*
*Point classes constructor, used to fill x,y,z
*/
Point::Point(double x, double y, double z)
{
	xCoord = x;
	yCoord = y;
	zCoord = z;
}

/*
*Standard distace between two points function
*/
double Point::distance(const Point& p)
{
	double x, y, z;

	x = p.xCoord - xCoord;
	x = x * x;

	y = p.yCoord - yCoord;
	y = y * y;

	z = p.zCoord - zCoord;
	z = z * z;

	return sqrt(x + y + z);
}

//Shape3D functs
/*
*Shape3D constructor used to fill Location
*/
Shape3D::Shape3D(Point& p) : Point(p), Location(p)
{
}
