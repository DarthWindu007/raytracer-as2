#include "localgeo.h"
#include "normal.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;

Localgeo::Localgeo(){
	this->pos=Point();
	this->normal=Normal();
}
Localgeo::Localgeo(Point p, Normal nom){
   this->pos = p;
   this->normal = nom; 
}


