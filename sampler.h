#ifndef SAMPLER_H
#define SAMPLER_H
#include "algebra3.h"
#include "brdf.h"
#include "localgeo.h"
#include "sample.h"
#include <iostream>
#include <typeinfo>
using namespace std;

class Sampler {
public:
    float width, height, currentX, currentY;
    Sampler();
    Sampler(float,float);
    bool getSample(Sample*);
    
};


#endif

