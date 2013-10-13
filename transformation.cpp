#include "transformation.h"
#include "vector.h"
#include "point.h"
#include "matrix.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;

Transformation::Transformation(){
	m=Matrix::identityMat();
	minvt=m.inv();
}
Transformation::Transformation(Matrix mat){
	m = mat;
	minvt = mat.inv();;
}

 Point Transformation::operator*(Point p){
 	vec4 temp = m.mat * vec4(p.x,p.y,p.z,1);
 	return Point(temp[0],temp[1],temp[2]);
 }
 Vector Transformation::operator*(Vector v){
 	vec4 temp = m.mat * vec4(v.x,v.y,v.z,0);
 	return Vector(temp[0],temp[1],temp[2]);
 }
 Normal Transformation::operator*(Normal v){
 	vec4 temp = m.mat * vec4(v.x,v.y,v.z,0);
 	return Normal(temp[0],temp[1],temp[2]);
 }
 Ray Transformation::operator*(Ray){
 	return Ray();
 }
 Localgeo Transformation::operator*(Localgeo){
 	return Localgeo(Point(),Normal());
 }

 Transformation Transformation::inv(){
 	return Transformation(this->minvt);
 }
 Transformation Transformation::trans(){
 	return Transformation(this->m.trans());
 }
 Transformation Transformation::identityTrans(){
 	return Transformation();
 }

//Still need to add Support Point, Vector, Normal, Ray, LocalGeo transformation by
//operator * overloading


////////
