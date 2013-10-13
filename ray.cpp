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
Ray::Ray(Point p, Vector d, float tmi,float tma){
     this->pos = p;
     this->dir = d;
     this->t_min = tmi;
     this->t_max = tma;  
}

Point Ray::rayPos(float time){
	return pos+dir*time;
}
