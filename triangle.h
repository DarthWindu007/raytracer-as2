#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "ray.h"
#include "localgeo.h"
#include "primitive.h"
#include "point.h"

#include "brdf.h"       //
#include <vector>         //
#include "transformation.h" //
class Triangle : public Primitive{
public:
	Point a,b,c;
	BRDF* brdf;
	vector<Transformation>* transformations;
	Triangle(Point,Point,Point,BRDF*,vector<Transformation>*);
	//Point(float,Point);
	bool isTransformed();
	void getBRDF(Localgeo&, BRDF*);
	vector<Transformation> getTransform();
	bool intersect(Ray&, float*, Localgeo*);
	bool intersectP(Ray&);
	void printstuff();
};

#endif