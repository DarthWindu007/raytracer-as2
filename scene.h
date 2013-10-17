#ifndef SCENE_H
#define SCENE_H
#include "sample.h"
#include "color.h"
#include "film.h"
#include "sampler.h"
#include "point.h"
#include "ray.h"
#include "camera.h"
#include "raytracer.h"
//#include "transform.h"
#include <math.h>
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
    Scene();
    void render();
};




#endif
