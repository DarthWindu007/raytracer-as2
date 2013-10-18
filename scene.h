#ifndef SCENE_H
#define SCENE_H
#include "sample.h"
#include "color.h"
#include "ray.h"
#include "film.h"

#include "sampler.h"
#include "camera.h"
#include "point.h"
#include "raytracer.h"

#include "primitive.h"
#include "light.h"
#include "shape.cpp"
#include "globaldef.cpp"

//#include "transform.h"
#include <math.h>
#include <vector>

using namespace std;

class Scene {
  public:
  	Raytracer raytracer;
  	Film film;
  	Camera camera;
  	Sampler sampler;
  	Sample sample;
  	Ray ray;
  	Color color;
  	vector<Shape*> shapes;
  	vector<Light*> lights;
  	vector<Primitive*> primitives;

    void render();
};




#endif
