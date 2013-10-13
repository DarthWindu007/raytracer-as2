#ifndef NORMAL_H
#define NORMAL_H
#include <iostream>
class Normal {
public:
	float x,y,z;
	Normal();
	Normal(float,float,float);
	Normal operator+(Normal);
	Normal operator-(Normal);
};

std::ostream& operator<<(std::ostream&, const Normal&);
#endif