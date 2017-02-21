class Point
{
public:
	Point(double x, double y, double z);
	double distance(const Point& p);
	
	double getx() { return xCoord; };
	double gety() { return yCoord; };
	double getz() { return zCoord; };
private:
	double xCoord;
	double yCoord;
	double zCoord;
};

class Shape3D :public Point
{
public:
	Shape3D(Point& p);
	virtual bool contains(Point& p) = 0;
	virtual double volume() = 0;
protected:
	Point Location;
};

class Sphere :public Shape3D
{
public:
	Sphere(Point& p, double radius);

	double getradius() { return radius; };
	Point GetLocation() { return Location; };

	bool contains(Point& p);
	double volume();
private:
	double radius;
};

class Cube :public Shape3D
{
public:
	Cube(Point& p, double side);

	double getside() { return side; };
	Point GetLocation() { return Location; };

	bool contains(Point& p);
	double volume();
private:
	double side;
};

class RectParPiped :public Shape3D
{
public:
	RectParPiped(Point& p, double w, double h, double d);
	
	double getwidth() { return width; };
	double getheight() { return height; };
	double getdepth() { return depth; };
	Point GetLocation() { return Location; };

	bool contains(Point& p);
	double volume();
private:
	double width;
	double height;
	double depth;
};