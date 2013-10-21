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

Vector Ray::getReflection(Normal norm){
	Vector direct = this->dir;
	float normD = norm.x*norm.x+norm.y*norm.y+norm.z*norm.z;

	float constant = (direct*norm);
	float temp = constant*(-1.0f/normD);
	return Vector(direct + (norm*temp*2.0f));
}
float Ray::rayGetT(Point point){
	Vector v = point -this->pos;
	vec3 newD = vec3(dir.x,dir.y,dir.z);
	vec3 pDIR = vec3(v.x,v.y,v.z);
	for (int i = 0; i < 3; i ++){
        if (pDIR[i] !=0 && newD[i] !=0){
            float t = pDIR[i]/newD[i];
            if (t > 0){
                    return t;
            }
        }
	}

}
