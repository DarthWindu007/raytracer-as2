#include "directionallight.h"
#include "color.h"
#include "localgeo.h"
#include "ray.h"
#include <math.h>
#define _USE_MATH_DEFINES

Directionallight::Directionallight()
{
        this->dir = Vector(1,1,1);
        this->color = Color(1,1,1);
        this->type = "directional";
}

Directionallight::Directionallight(Vector v, Color c){
	    //This Constructor takes in the direction of the light pointing 
	    //Same as what we did in directional light in as1
        this->dir = v;
        this->color = c;
        this->type = "directional";
}

