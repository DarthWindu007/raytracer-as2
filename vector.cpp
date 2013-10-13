#include "vector.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;

Vector::Vector(){
	x=0;
	y=0;
	z=0;
}
Vector::Vector(float nx, float ny, float nz){
	x=nx;
	y=ny;
	z=nz;  
}

Vector Vector::operator+(Vector v2){
	return Vector(this->x+v2.x,this->y+v2.y,this->z+v2.z);
}
Vector Vector::operator-(Vector v2){
	return (*this)+(v2*-1.0f); // is the same as this.operator+(v2*-1.0f);
}
Vector Vector::operator*(float v2){
	return Vector(v2*this->x,v2*this->y,v2*this->z);
}
Vector Vector::operator/(float v2){
	return (*this)*(1.0f/v2);
}
Vector Vector::norm(){
	float d = sqrt(pow(this->x,2)+pow(this->y,2)+pow(this->z,2));
	if(d==0)
		return Vector(0,0,0);
	else
		return (*this)/d;
}

ostream& operator<<(ostream &strm, const Vector &a){
	return strm << "Vector(" << a.x << ", " << a.y << ", " << a.z << ")";
}

Vector operator+(Vector v2, float f2){
	return v2+Vector(f2,f2,f2);
}
Vector operator-(Vector v2, float f2){
	return v2+(Vector(f2,f2,f2)*-1.0f);
}
Vector operator+(float f2, Vector v2){
	return v2+Vector(f2,f2,f2);
}
Vector operator-(float f2, Vector v2){
	return Vector(f2,f2,f2)-v2;
}
Vector operator*(float f2, Vector v2){
	return v2*f2;
}

////////



