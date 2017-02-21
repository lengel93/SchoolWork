#include <iostream>
#include "Shape3D.h"
#include "math.h"
#include <gtest/gtest.h>
#define _USE_MATH_DEFINES 

using namespace std;

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/*
*Set of tests that make sures each shape classes
*constructor is working properly
*/
TEST(ConstructorTest, PointCons)
{
	Point test(6, 3, -8);
	EXPECT_TRUE(test.getx() == 6) << "X is incorrect should be 6";
	EXPECT_TRUE(test.gety() == 3) << "Y is incorrect should be 3";
	EXPECT_TRUE(test.getz() == -8) << "Z is incorrect should be -8";
}
TEST(ConstructorTest, SphereCons)
{
	Point center(1, 1, 1);
	Sphere test(center, 20);

	EXPECT_TRUE(test.getradius() == 20) << "Radius should be 20";
}
TEST(ConstructorTest, CubeCons)
{
	Point center(1, 1, 1);
	Cube test(center, 14);
	EXPECT_TRUE(test.getside() == 14) << "Side should be 14";
}
TEST(ConstructorTest, RectCons)
{
	Point center(1, 1, 1);
	RectParPiped test(center, 13, -34, -5);
	EXPECT_TRUE(test.getwidth() == 13) << "Width should be 13";
	EXPECT_TRUE(test.getheight() == -34) << "Height should be -34";
	EXPECT_TRUE(test.getdepth() == -5) << "Depth should be -5";
}

/*
*Set that makes sure each shape class constructor
*is filling the Location Point correctly
*/
TEST(LocationTest, SphereLocs)
{
	Point center(6, -3, 8);
	Sphere test(center, 20);
	EXPECT_TRUE(test.GetLocation().getx() == center.getx()) << "Location x should be 6";
	EXPECT_TRUE(test.GetLocation().gety() == center.gety()) << "Location y should be -3";;
	EXPECT_TRUE(test.GetLocation().getz() == center.getz()) << "Location z should be 8";;
}
TEST(LocationTest, CubeLocs)
{
	Point center(4, -10, -20);
	Cube test(center, 14);
	EXPECT_TRUE(test.GetLocation().getx() == center.getx());
	EXPECT_TRUE(test.GetLocation().gety() == center.gety());
	EXPECT_TRUE(test.GetLocation().getz() == center.getz());
}
TEST(LocationTest, RectLocs)
{
	Point center(-2, 4, 15);
	RectParPiped test(center, 13, -34, -5);
	EXPECT_TRUE(test.GetLocation().getx() == center.getx());
	EXPECT_TRUE(test.GetLocation().gety() == center.gety());
	EXPECT_TRUE(test.GetLocation().getz() == center.getz());
}

/*
*Test whether the distance fucntion is working correctly.
*/
TEST(DistanceTest, Distance)
{
	Point point1(1, 1, 1);
	Point point2(5, -3, -6);
	EXPECT_EQ(9, point1.distance(point2)) << "Distance should be 9";
}

/*
*Set of tests that make sures each shape classes
*volume function is working correctly
*/
TEST(VolumeTest, SphereVolume)
{
	Point center(1, 1, 1);
	Sphere sph(center, 9);
	EXPECT_EQ(3053, int(sph.volume())) <<"Sphere Volume should be 3053";
}
TEST(VolumeTest, CubeVolume)
{
	Point center(1, 1, 1);
	Cube cu(center, 9);
	EXPECT_EQ(729, int(cu.volume())) << "Cube Volume should be 729";
}
TEST(VolumeTest, RectVolume)
{
	Point center(1, 1, 1);
	RectParPiped rect(center, 9, 13, 16);
	EXPECT_EQ(1872, int(rect.volume())) <<"Rect Volume should be 1872";
}

/*
 *Set of tests that make sures each shape classes
 *contain function is working correctly
 */
TEST(ContainsTest, SphereCon)
{
	Point center(1, 1, 1);
	Point test(10, 1, 1);
	Point test2(1, 10, 1);
	Point test3(1, 1, -8);

	Sphere sph(center, 9);

	EXPECT_TRUE(sph.contains(test)) << "X axis bound failed";
	EXPECT_TRUE(sph.contains(test2)) << "Y axis bound failed";
	EXPECT_TRUE(sph.contains(test3)) << "Z axis bound failed";
}
TEST(ContainsTest, CubeCon)
{
	Point center(1, 1, 1);
	Point test(6,1,1);
	Point test2(-4, 1, 1);
	Point test3(1, 1, 6);
	
	Cube cu(center, 10);

	EXPECT_TRUE(cu.contains(test)) << "X axis bound failed";
	EXPECT_TRUE(cu.contains(test2)) << "Y axis bound failed";
	EXPECT_TRUE(cu.contains(test3)) << "Z axis bound failed";
}
TEST(ContainsTest, RectCon)
{
	Point center(1, 1, 1);
	Point test(4, 1, 1);
	Point test2(1, -4, 1);
	Point test3(1, 1, 3);

	RectParPiped rect(center, 6, 10, 4);

	EXPECT_TRUE(rect.contains(test)) << "X axis bound failed";
	EXPECT_TRUE(rect.contains(test2)) << "Y axis bound failed";
	EXPECT_TRUE(rect.contains(test3)) << "Z axis bound failed";
}