#ifndef CAMERA_H
#define CAMERA_H
#include "sample.h"
#include <iostream>
#include "algebra3.h"
#include "raytracer.h"
#include "vector.h"
#include "point.h"
#include "ray.h"
#include <math.h>
#define _USE_MATH_DEFINES

class Camera {
public:
	Vector W,U,V;
	Point pos;
	Camera();
    void generateRay(Sample&, Ray*);
};


#endif