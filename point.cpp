#include "vector.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;

Point::Point(){
	x=0;
	y=0;
	z=0;
}
Point::Point(float nx, float ny, float nz){
	x=nx;
	y=ny;
	z=nz;  
}

Point Point::operator+(Vector n2){
    return Point(this->x + n2.x,this->y + n2.y,this->z + n2.z);
}
Point Point::operator-(Vector n2){
    return Point(this->x - n2.x,this->y - n2.y,this->z - n2.z);
}


Point operator+(Vector n2, Point p){
    return p+n2;
}
Point operator-(Vector n2, Point p){
    return Point(-p.x,-p.y,-p.z)+n2;
}


ostream& operator<<(ostream &strm, const Point &a){
	return strm << "Point(" << a.x << ", " << a.y << ", " << a.z << ")";
}