#include "vector.h"
#include <iostream>
#include <typeinfo>
#include <vector>
#include "math.h"
#include "primitive.h"
#include "camera.h"
#include "sampler.h"
#include "sample.h"
#include "raytracer.h"
#include "color.h"
#include "ray.h"
using namespace std;

Point lookfrom,lookat;
Vector up;


vector<Light*> lights;
int P_height,P_width;
float fov;
int maxdepth;

Raytracer raytracer;

Camera camera;
Sampler sampler;
Sample sample;
Ray ray;
Color color;