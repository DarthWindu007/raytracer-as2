#ifndef SPHERE_H
#define SPHERE_H
#include "ray.h"
#include "localgeo.h"
#include "shape.cpp"
#include "point.h"

class Sphere : public Shape{
public:
	float radius;
	Point center;
	//Point(float,Point);
	Sphere();
	Sphere(float,Point);
	float dot(Point,Point);
	float dot(Vector,Point);
	float dot(Vector,Vector);
	bool intersect(Ray&, float*, Localgeo*);
	bool intersectP(Ray&);
};

#endif