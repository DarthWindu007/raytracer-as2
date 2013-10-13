#ifndef BRDF_H
#define BRDF_H
#include "color.h"
class BRDF {
public:
	Color kd,ks,ka,kr;
	float p,n;
	BRDF();
	BRDF(Color,Color,Color,Color,float,float);
};

#endif
