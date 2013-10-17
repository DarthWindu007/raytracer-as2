#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "primitive.h"
#include "localgeo.h"
class Intersection
{
public:
	Localgeo lg;
	Primitive* primitive;
	Intersection();
};

#endif