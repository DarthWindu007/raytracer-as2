#ifndef GEOMETRIC_PRIMITIVE_H
#define GEOMETRIC_PRIMITIVE_H
#include "ray.h"
#include "localgeo.h"
#include "transformation.h"
#include "shape.cpp"
#include "brdf.h"
#include "material.h"
#include "intersection.h"
class GeometricPrimitive : public Primitive
{
public:
	Shape* shape;
	Material* mat;
	Transformation objToWorld, worldToObj;
	GeometricPrimitive(Shape*,Transformation,Material*);
	GeometricPrimitive(Shape*,Vector,Vector,Vector,Color,Color,Color,float);
	GeometricPrimitive(Shape*,Vector,Vector,Vector,float,Color,Color,Color,float);
	bool intersect(Ray&, float*,Intersection*);
	bool intersectP(Ray&);
	void getBRDG(Localgeo&,BRDF*);

};

#endif