#include "normal.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;

Normal::Normal(){
	this->x=0;
	this->y=0;
	this->z=0;
}
Normal::Normal(float nx, float ny, float nz){
	setStuff(nx,ny,nz);
}
Normal::Normal(Point p){
	setStuff(p.x,p.y,p.z);
}
Normal::Normal(Vector v){
	setStuff(v.x,v.y,v.z);
}

void Normal::setStuff(float nx, float ny, float nz){
	Vector vec = Vector(nx,ny,nz);
	vec = vec.norm();
	this->x=vec.x;
	this->y=vec.y;
	this->z=vec.z;  
}

Normal Normal::operator+(Normal n2){
    Normal  tem = Normal(this->x + n2.x,this->y + n2.y,this->z + n2.z);
    float   val = sqrt(pow(tem.x ,2) + pow(tem.y ,2) +pow(tem.z ,2));
	
	if(val == 0){
		return Normal(0,0,0); // return a zero vector if tem is a zero vector
	}
	else{
		return Normal(tem.x /val,tem.y /val,tem.z /val);
	}
}

Normal Normal::operator-(Normal n2){
    Normal  tem = Normal(this->x - n2.x,this->y - n2.y,this->z - n2.z);
    float   val = sqrt(pow(tem.x ,2) + pow(tem.y ,2) +pow(tem.z ,2));
	
	if(val == 0){
		return Normal(0,0,0); // return a zero vector if tem is a zero vector
	}
	else{
		return Normal(tem.x /val,tem.y /val,tem.z /val);
	}
}

ostream& operator<<(ostream &strm, const Normal &a){
	return strm << "Normal(" << a.x << ", " << a.y << ", " << a.z << ")";
}


////////




