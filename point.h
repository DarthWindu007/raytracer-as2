#ifndef POINT_H
#define POINT_H
#include "vector.h"
#include <iostream>

class Point {
public:
	float x,y,z;
	Point();
	Point(float,float,float);
	Point operator+(Vector);
	Point operator-(Vector);
	Vector operator-(Point);
};

std::ostream& operator<<(std::ostream&, const Point&);

#endif
