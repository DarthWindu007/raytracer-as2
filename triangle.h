#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "ray.h"
#include "localgeo.h"
#include "shape.cpp"
#include "point.h"

class Triangle : public Shape{
public:
	Point a,b,c;
	Triangle(Point,Point,Point);
	//Point(float,Point);
	bool intersect(Ray&, float*, Localgeo*);
	bool intersectP(Ray&);
};

#endif