#ifndef LIGHT_H
#define LIGHT_H
#include "color.h"
#include "localgeo.h"
#include "ray.h"

class Light
{
public:
	Vector dir;
	Point pos;
	Color color;
	string type;
};


#endif