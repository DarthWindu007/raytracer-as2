#include "ray.h"
#include "localgeo.h"

class Shape{
public:
	virtual bool intersect(Ray&, float*, Localgeo*){return false;};
	virtual bool intersectP(Ray&){return false;};
};
