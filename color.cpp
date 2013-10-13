#include "color.h"
#include "vector.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;

Color::Color(){
	r=0;
	g=0;
	b=0;
}
Color::Color(float red, float green, float blue){
	r=red;
	g=green;
	b=blue;  
}

Color Color::operator+(Color n2){
    return Color(this->r + n2.r,this->g + n2.g,this->b + n2.b);
}
Color Color::operator-(Color n2){
    return Color(this->r - n2.r,this->g - n2.g,this->b - n2.b);
}
Color Color::operator*(float scalar){
    return Color(this->r * scalar,this->g * scalar,this->b * scalar);
}
Color Color::operator/(float scalar){
    return Color(this->r / scalar,this->g / scalar,this->b / scalar);
}

ostream& operator<<(ostream &strm, const Color &a){
	return strm << "Color(" << a.r << ", " << a.g << ", " << a.b << ")";
}