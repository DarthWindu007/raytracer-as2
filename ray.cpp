#include "ray.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;

Ray::Ray(){
	pos=Point();
	dir=Vector();
	t_min=0;
	t_max=0;
}
Ray::Ray(Point p, Vector d, float tmi,float tma){
     pos = p;
     dir = d;
     t_min = tmi;
     t_max = tma;  
}

Point Ray::rayPos(float time){
	return pos+dir*time;
}
