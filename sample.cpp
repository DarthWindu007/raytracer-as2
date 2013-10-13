#include "sample.h"
#include "vector.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;

Sample::Sample(){
	this->x=0;
	this->y=0;
}
Sample::Sample(float nx, float ny){
	this->x=nx;
	this->y=ny;  
}

