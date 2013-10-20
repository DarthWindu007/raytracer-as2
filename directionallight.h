#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include "light.h"
#include "localgeo.h"
#include "ray.h"
#include "color.h"
#include "vector.h"
#include <math.h>
#include <iostream>
#include <typeinfo>

using namespace std;

class Directionallight : public Light {
public:
    Directionallight();
    Directionallight(Vector, Color);
    
};


#endif
