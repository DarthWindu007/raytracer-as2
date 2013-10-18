#ifndef NORMAL_H
#define NORMAL_H
#include <iostream>
#include "vector.h"
#include "point.h"
class Normal {
private:
	void setStuff(float,float,float);
public:
	float x,y,z;
	Normal();
	Normal(float,float,float);
	Normal(Vector);
	Normal(Point);
	Normal operator+(Normal);
	Normal operator-(Normal);
	float operator*(Normal);
	Normal operator*(float);
};

std::ostream& operator<<(std::ostream&, const Normal&);
#endif