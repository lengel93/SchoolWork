#include <iostream>
#include "Shape3D.h"
#include "math.h"
#include <gtest/gtest.h>
#define _USE_MATH_DEFINES 


/*
*Sphere Constructor, fills radius and Location
*/
Sphere::Sphere(Point& p, double r) : Shape3D(p)
{
	radius = r;
}

/*
*Checks where a point is located in a sphere using
*the distance function.
*/
bool Sphere::contains(Point& p)
{
	double dist;

	dist = distance(p);

	if (dist <= radius)
	{
		return true;
	}
	return false;
}

/*
*Function to calculate the volume of a sphere
*/
double Sphere::volume()
{
	return (double(4) / double(3))*M_PI*(radius*radius*radius);
}