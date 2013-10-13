#ifndef LOCALGEO_H
#define LOCALGEO_H
#include "localgeo.h"
#include "normal.h"
#include "point.h"

class Localgeo {
public:
	Point pos;
	Normal normal;
	Localgeo(Point,Normal);
};

#endif