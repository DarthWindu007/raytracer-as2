#ifndef LOCALGEO_H
#define LOCALGEO_H
#include "ray.h"

class Shape{
public:
	bool intersect(Ray&, float*, Localgeo*){return false;};
	bool intersectP(Ray&);
};

#endif