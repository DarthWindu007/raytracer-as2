#include "ray.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"

using namespace std;

Ray::Ray(){
	this->pos=Point();
	this->dir=Vector();
	this->t_min=0;
	this->t_max=0;
}
Ray::Ray(Point p, Vector d){
     this->pos = p;
     this->dir = d; 
}

Point Ray::rayPos(float time){
	return pos+dir*time;
}

float Ray::rayGetT(Point point){
	Vector v = point -this->pos;
	vec3 direction = vec3(dir.x,dir.y,dir.z);
	vec3 pDIR = vec3(v.x,v.y,v.z);
	for (int i = 0; i < 3; i ++){
        if (pDIR[i] !=0 && direction[i] !=0){
            float t = pDIR[i]/direction[i];
            if (t > 0){
                    return t;
            } else {
                    // printf(" Error: you have a negative t value. fuck off. \n");
            }
        }
	}

}
