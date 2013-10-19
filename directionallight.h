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
    Vector dir;
    Color color;
    Directionallight();
    Directionallight(Vector, Color);
    void generateLightRay(Localgeo&, Ray*, Color*);
    
};


#endif
