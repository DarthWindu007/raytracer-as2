#include "vector.h"
#include <iostream>
#include <typeinfo>
#include <vector>
#include "math.h"
#include "primitive.h"
using namespace std;

extern Point lookfrom,lookat;
extern Vector up;
extern vector<Primitive*> prims;
extern int P_height,P_width;
extern float fov;