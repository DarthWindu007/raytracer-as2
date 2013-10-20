#ifndef MATRIX_H
#define MATRIX_H
#include "algebra3.h"
#include "vector.h"
#include "normal.h"

class Matrix {
public:
    mat4 mat;
    Matrix();
    Matrix(float*);
    Matrix(mat4);
    Matrix operator+(Matrix);
	Matrix operator-(Matrix);
	Matrix operator*(Matrix);
	Vector operator*(Vector);
	Normal operator*(Normal);
	Point operator*(Point);
	static Matrix transMat(float,float,float);
	static Matrix scaleMat(float,float,float);
	static Matrix rotMat(float,float,float);
	static Matrix axisRotMat(float,float,float,float);
	static Matrix identityMat();
	
	Matrix inverse();
	Matrix transpose();
};

std::ostream& operator<<(std::ostream&, const Matrix&);

#endif