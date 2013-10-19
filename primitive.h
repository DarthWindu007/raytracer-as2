#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "ray.h"
#include "localgeo.h"
#include "brdf.h"
#include "transformation.h"
#include <vector>
using namespace std;

class Primitive {
public:
	//explicit
	virtual bool intersect(Ray&, float*, Localgeo*)=0;//{return false;};
	virtual bool intersectP(Ray&)=0;//{return false;};
	virtual void getBRDF(Localgeo&, BRDF*)=0;//{return;};
	virtual bool isTransformed()=0;//{return false;};
	virtual vector<Transformation> getTransform()=0;//{vector<Transformation> v;return v;};
	virtual void printstuff()=0;
};

#endif