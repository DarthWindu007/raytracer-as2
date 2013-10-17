#include "geometricprimitive.h"
#include "matrix.h"


GeometricPrimitive::GeometricPrimitive(Shape* shape, Transformation transformation, Material* mat){
	this->objToWorld = transformation;
	this->worldToObj = transformation.inv();
	this->shape = shape;
	this->mat = mat;
}
GeometricPrimitive::GeometricPrimitive(Shape* shape,Vector rot,Vector scale,Vector trans,Color ka,Color kd,Color ks,float p){
	Matrix ro = Matrix::rotMat(rot.x,rot.y,rot.z);
	Matrix sc = Matrix::scaleMat(scale.x,scale.y,scale.z);
	Matrix tr = Matrix::transMat(trans.x,trans.y,trans.z);

	BRDF brdf = BRDF(ka,kd,ks,Color(),p,1.0);


	this->objToWorld.m = tr*ro*sc;
	this->worldToObj = this->objToWorld.m.inv();
	this->shape = shape;
	this->mat->constantBRDF=brdf;
}

GeometricPrimitive::GeometricPrimitive(Shape* shape,Vector rot,Vector scale,Vector trans,float angle,Color ka,Color kd,Color ks,float p){
	Matrix ro = Matrix::axisRotMat(rot.x,rot.y,rot.z,angle);
	Matrix sc = Matrix::scaleMat(scale.x,scale.y,scale.z);
	Matrix tr = Matrix::transMat(trans.x,trans.y,trans.z);

	BRDF brdf = BRDF(ka,kd,ks,Color(),p,1.0);

	this->objToWorld.m = tr*ro*sc;
	this->worldToObj = this->objToWorld.m.inv();
	this->shape = shape;
	this->mat->constantBRDF=brdf;
}

bool GeometricPrimitive::intersect(Ray& ray, float* thit,Intersection* in){
    Ray newRay = this->worldToObj*ray;
    float newThit;
    Localgeo lgO;
    if (shape->intersect(newRay,&newThit,&lgO)){
        *thit = newThit;
        in->lg = this->objToWorld*lgO;
        in->primitive = this;
        return true;
    }
    else
    	return false;
}
bool GeometricPrimitive::intersectP(Ray& ray){
	Ray newRay = this->worldToObj*ray;
	float newThit;
	Localgeo lgO;
	if (shape->intersect(newRay,&newThit,&lgO)){
	    return true;
	} 
	else
	    return false;
}
void GeometricPrimitive::getBRDG(Localgeo& loc,BRDF* brdf){
	*brdf = this->mat->constantBRDF;
}

