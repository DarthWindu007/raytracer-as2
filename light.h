#ifndef LIGHT_H
#define LIGHT_H
#include "color.h"
#include "localgeo.h"
#include "ray.h"

class Light
{
public:

        void generateLightRay(Localgeo& local, Ray* lray, Color* lcolor);
};


#endif