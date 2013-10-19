#ifndef SPHERE_H
#define SPHERE_H
#include "ray.h"
#include "localgeo.h"
#include "primitive.h"
#include "point.h"
#include "brdf.h"       //
#include <vector>         //
#include "transformation.h" //

class Sphere : public Primitive{
public:
	float radius;
	Point center;
	BRDF* brdf;
	vector<Transformation>* Tvalue;
	Sphere(float , Point ,BRDF* , vector<Transformation>* );
	float dot(Point,Point);
	float dot(Vector,Point);
	float dot(Vector,Vector);
	bool intersect(Ray&, float*, Localgeo*);
	bool intersectP(Ray&);
	bool isTransformed();
	void getBRDF(Localgeo&, BRDF*);
	vector<Transformation> getTransform();
};

#endif 