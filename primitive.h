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
	virtual bool intersect(Ray&, float*, Localgeo*);
	virtual bool intersectP(Ray&);
	virtual void getBRDF(Localgeo&, BRDF*);

	virtual bool isTransformed();
	virtual vector<Transformation> getTrans();
};

#endif