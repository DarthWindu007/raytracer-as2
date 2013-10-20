#include "transformation.h"
#include "vector.h"
#include "point.h"
#include "matrix.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;

Transformation::Transformation(){
	this->m=Matrix::identityMat();
	this->minvt=m.inverse();
}
Transformation::Transformation(Matrix mat){
	this->m = mat;
	this->minvt = mat.inverse();
}

 Point Transformation::operator*(Point p){
 	vec4 temp = this->m.mat * vec4(p.x,p.y,p.z,1);
 	return Point(temp[0],temp[1],temp[2]);
 }
 Vector Transformation::operator*(Vector v){
 	vec4 temp = this->m.mat * vec4(v.x,v.y,v.z,0);
 	return Vector(temp[0],temp[1],temp[2]);
 }
 Normal Transformation::operator*(Normal v){
 	vec4 temp = this->m.mat * vec4(v.x,v.y,v.z,0);
 	return Normal(temp[0],temp[1],temp[2]);
 }
 Ray Transformation::operator*(Ray r){
 	return Ray((*this)*r.pos,(*this)*r.dir);
 }
 Localgeo Transformation::operator*(Localgeo lg){
 	return Localgeo((*this)*lg.pos,(*this)*lg.normal);
 }

 Transformation Transformation::inverse(){
 	return Transformation(this->minvt);
 }
 Transformation Transformation::transpose(){
 	return Transformation(this->m.transpose());
 }
 Transformation Transformation::identityTrans(){
 	return Transformation();
 }

//Still need to add Support Point, Vector, Normal, Ray, LocalGeo transformation by
//operator * overloading


////////
