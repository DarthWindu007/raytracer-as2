#ifndef BRDF_H
#define BRDF_H
#include "color.h"
class BRDF {
public:
	Color kd,ks,ka,kr;
	Color em;
	float sp;
	BRDF();
	BRDF(Color,Color,Color,Color,Color,float);
};

#endif
