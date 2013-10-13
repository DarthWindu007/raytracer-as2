#include "normal.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;

Normal::Normal(){
	x=0;
	y=0;
	z=0;
}
Normal::Normal(float nx, float ny, float nz){
	Vector vec = Vector(nx,ny,nz);
	vec = vec.norm();
	x=vec.x;
	y=vec.y;
	z=vec.z;  
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




