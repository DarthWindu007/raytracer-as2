#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "ray.h"
#include "localgeo.h"
#include "brdf.h"
#include "intersection.h"

class Primitive{
public:
	virtual bool intersect(Ray& ray, float* thit, Localgeo* local){return false;};
	virtual bool intersectP(Ray& ray){return false;};
	virtual void getBRDF(Localgeo& local, BRDF* brdf){};
};

#endif