#ifndef RAYTRACER_H
#define RAYTRACER_H
#include "algebra3.h"
#include "vector.h"
#include "point.h"
#include "ray.h"
#include "localgeo.h"
#include "color.h"
#include "sample.h"
#include "primitive.h"
#include "brdf.h"
#include <math.h>
#define _USE_MATH_DEFINES
using namespace std;



class Raytracer{
public:
	int threshold;
	Point camera_pos;
	vector<Primitive*> prims;
	Raytracer();
	Raytracer(int, Point);
	void trace(Ray&, int, Color*);
	Color shading(Localgeo&,BRDF, Ray&, Ray&, Color);
};


#endif