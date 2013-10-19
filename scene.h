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



//#include "transform.h"
#include <math.h>
#include <vector>

using namespace std;


class Scene {
public:
  Film film;


	vector<Primitive*> primitives;

  void loadScene(string);
  void render();
};




#endif
