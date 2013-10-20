using namespace std;
#include "matrix.h"
#include "algebra3.h"
#include "normal.h"
#include "vector.h"
#define _USE_MATH_DEFINES

Matrix::Matrix(){
	this->mat = mat4(0);
}
Matrix::Matrix(float *m){
	this->mat = mat4(vec4(m[0],m[1],m[2],m[3]),vec4(m[4],m[5],m[6],m[7]),vec4(m[8],m[9],m[10],m[11]),vec4(m[12],m[13],m[14],m[15]));
}
Matrix::Matrix(mat4 m){
	this->mat=m;
}

Matrix Matrix::operator+(Matrix m ){
	return Matrix(this->mat+m.mat);
}
Matrix Matrix::operator-(Matrix m){
	return Matrix(this->mat-m.mat);
}
Matrix Matrix::operator*(Matrix m){
	return Matrix(this->mat*m.mat);
}
Vector Matrix::operator*(Vector v){
	vec4 temp = this->mat*vec4(v.x,v.y,v.z,0);
	return Vector(temp[0],temp[1],temp[2]);
}
Normal Matrix::operator*(Normal n){
	vec4 temp = this->mat*vec4(n.x,n.y,n.z,0);
	return Normal(temp[0],temp[1],temp[2]);
}
Point Matrix::operator*(Point n){
	vec4 temp = this->mat*vec4(n.x,n.y,n.z,0);
	return Point(temp[0],temp[1],temp[2]);
}

Matrix Matrix::transMat(float x,float y,float z){
	return Matrix(translation3D(vec3(x,y,z)));
}
Matrix Matrix::scaleMat(float x,float y,float z){
	return Matrix(scaling3D(vec3(x,y,z)));
}
Matrix Matrix::rotMat(float x,float y,float z){
	float rx = M_PI*x/180;
	float ry = M_PI*y/180;
	float rz = M_PI*z/180;
	float temp[16] = {1,0,0,0,		0,cos(rx),sin(rx),0,	0,-sin(rx),cos(rx),0,	0,0,0,1};
	Matrix xmat = Matrix(temp);
	float temp2[16] = {cos(ry),0,-sin(ry),0,		0,1,0,0,	sin(ry),0,cos(ry),0,	0,0,0,1};
	Matrix ymat = Matrix(temp2);
	float temp3[16] = {cos(rz),sin(rz),0,0,		-sin(rz),cos(rz),0,0,	0,0,1,0,	0,0,0,1};
	Matrix zmat = Matrix(temp3);

	return xmat*ymat*zmat;
}
Matrix Matrix::axisRotMat(float ax,float ay,float az,float angle){
	/*
	Normal temp = Normal(ax,ay,az);
	float rangle = M_PI*angle/180;
	float x = temp.x;
	float y = temp.y;
	float z = temp.z;
	float s = sin(rangle);
	float c = cos(rangle);

	float tempmat[16] = {c+(1-c)*x*x,(1-c)*y*x+z*s,(1-c)*z*x-y*s,0,	
						(1-c)*x*y-z*s,c+(1-c)*y*y,(1-c)*z*y+x*s,0,	
						(1-c)*x*z+y*s,(1-c)*y*z-x*s,c+(1-c)*z*z,0,	
						0,0,0,1};

	return Matrix(tempmat);
	*/
	return Matrix(rotation3D(vec3(ax,ay,az),angle));
}
Matrix Matrix::identityMat(){
	return Matrix(identity3D());
}

Matrix Matrix::inverse(){
	return mat.inverse();
}
Matrix Matrix::transpose(){
	return mat.transpose();
}

ostream& operator<<(ostream &strm, const Matrix &a){
	return strm << a.mat;
}