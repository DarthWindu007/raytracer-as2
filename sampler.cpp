#include "vector.h"
#include "sample.h"
#include "sampler.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;

extern float currentX, currentY;
extern int P_width, P_height;
Sampler::Sampler(){
	this->width=0;
	this->height=0;
}
Sampler::Sampler(float w, float h){ // PASS IN MAX WIDTH AND HEIGHT
	this->width=w;
	this->height=h; 
    // starts at the (l,t) left, top of the sample. 
    // (0,0) but add 0.5 to x and y 
    // to take the center of the pixel.
    //currentX = 0.0 + 0.5; 
    //currentY = 0.0 + 0.5; 
}

bool Sampler::getSample(Sample* sample){
   if(currentY > P_height && currentX > P_width){ // check if max height or max width is reached
            return false;
   }
    if(currentX > P_width){  // scan horizontally, if currentx == width, jump to the next row
            currentX = 0.5;
            currentY += 1;
    }
    *sample = Sample(currentX, currentY); // increament currentx 
    currentX += 1;
    return true;
}

