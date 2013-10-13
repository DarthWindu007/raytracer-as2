#include "brdf.h"
#include "vector.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;
BRDF::BRDF(){
	this->ka=Color(0.1,0.1,0.1);
	this->kd=Color();
	this->ks=Color();
	this->kr=Color();
	this->p=1;
	this->n=0;
}
BRDF::BRDF(Color a,Color b, Color c,Color d,float p,float n){
    this->ka = a;
    this->kd = b;
    this->ks = c;
    this->kr = d;
    this->p=p;
    this->n=n; 
}
