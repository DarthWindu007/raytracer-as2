#ifndef MATRIX_H
#define MATRIX_H
#include "algebra3.h"

class Matrix {
public:
    mat4 mat;
    Matrix();
    Matrix(float*);
    Matrix(mat4);
    Matrix operator+(Matrix);
	Matrix operator-(Matrix);
	Matrix operator*(Matrix);
	static Matrix transMat(float,float,float);
	static Matrix scaleMat(float,float,float);
	static Matrix rotMat(float,float,float);
	static Matrix axisRotMat(float,float,float,float);
	static Matrix identityMat();
	
	Matrix inv();
	Matrix trans();
};

std::ostream& operator<<(std::ostream&, const Matrix&);

#endif