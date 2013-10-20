#include "ray.h"
#include "localgeo.h"
#include "matrix.h"
#include "brdf.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"




class Shape{
public:
	string type;
	float radius;
	Point center;
	Point a,b,c;
	Normal normal;
	Matrix transform;
	BRDF brdf;

	Shape(){}

	Shape(string s,Matrix trans,BRDF col){
		type = s;
		transform = trans;
		brdf = col;
	}

	//Vector getNormal(Point p){	}
};

class Triangle : public Shape{
public:
	Point a,b,c;
	Triangle(Point p1, Point p2, Point p3){
	     a = p1;
	     b = p2;
	     c = p3;

	}

	Triangle(Point p1, Point p2, Point p3, Matrix mat, BRDF col){
	     a = p1;
	     b = p2;
	     c = p3;
	     transform = mat;
	     brdf = col;
	}
};

class Sphere : public Shape{
public:
	float radius;
	Point center;
	//Point(float,Point);

	Sphere(float r, Point c){ //, Color coloring){
	     radius = r;
	     center = c;
	     //Color scolor = coloring;

	}

	Sphere(float r, Point c, Matrix mat, BRDF col){
	  radius = r;
	  center = c;
	  transform = mat;
	  brdf = col;
	}
};


