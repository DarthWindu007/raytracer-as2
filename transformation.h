#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include "matrix.h"
#include "point.h"
#include "vector.h"
#include "normal.h"
#include "ray.h"
#include "localgeo.h"

class Transformation {
public:
	 Matrix m;
	 Matrix minvt;
	 Transformation();
	 Transformation(Matrix);

	 Point operator*(Point);
	 Vector operator*(Vector);
	 Normal operator*(Normal);
	 Ray operator*(Ray);
	 Localgeo operator*(Localgeo);

	 Transformation trans();
	 Transformation inv();
	 Transformation identityTrans();
};

#endif
