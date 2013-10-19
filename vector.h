#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include "algebra3.h"


class Vector {
public:
	float x,y,z;
	Vector();
	Vector(vec3);
	Vector(float,float,float);
	Vector operator+(Vector);
	Vector operator-(Vector);
	float operator*(Vector);
	Vector operator*(float);
	Vector operator/(float);
	Vector norm();
	Vector operator^(Vector);
};

std::ostream& operator<<(std::ostream&, const Vector&);
Vector operator+(Vector v2, float f2);
Vector operator-(Vector v2, float f2);
Vector operator+(float f2, Vector v2);
Vector operator-(float f2, Vector v2);
Vector operator*(float f2, Vector v2);

#endif
