#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "light.h"
#include "localgeo.h"
#include "ray.h"
#include "color.h"
#include "point.h"

#include <iostream>
#include <typeinfo>

using namespace std;

class Pointlight : public Light {
public:
    Point pos;
    Color color;
    Pointlight();
    Pointlight(Point, Color);
    void generateLightRay(Localgeo&, Ray*, Color*);
    
};


#endif
