#ifndef COLOR_H
#define COLOR_H
#include <iostream>

class Color {
public:
	float r,b,g;
	Color();
	Color(float,float,float);
	Color operator+(Color);
	Color operator-(Color);
	Color operator*(float);
	Color operator/(float);
};

std::ostream& operator<<(std::ostream&, const Color&);

#endif