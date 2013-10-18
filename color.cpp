#include "color.h"
#include "vector.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;

Color::Color(){
	this->r=0;
	this->g=0;
	this->b=0;
}
Color::Color(float red, float green, float blue){
	this->r=red;
	this->g=green;
	this->b=blue;  
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
Color Color::operator*(Color c){
    return Color(this->r * c.r,this->g * c.g,this->b * c.b);
}
Color Color::operator/(float scalar){
    return Color(this->r / scalar,this->g / scalar,this->b / scalar);
}

ostream& operator<<(ostream &strm, const Color &a){
	return strm << "Color(" << a.r << ", " << a.g << ", " << a.b << ")";
}