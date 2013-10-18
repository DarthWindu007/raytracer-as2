#include "vector.h"
#include <iostream>
#include <typeinfo>
#include <vector>
#include "math.h"
#include "primitive.h"
using namespace std;

Point lookfrom,lookat;
Vector up;
vector<Primitive*> prims;
vector<Shape*> shapes;
vector<Light*> lights;
int P_height,P_width;
float fov;