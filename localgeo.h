#ifndef LOCALGEO_H
#define LOCALGEO_H
#include "localgeo.h"
#include "normal.h"
#include "point.h"

class Localgeo {
public:
	Point pos;
	Normal normal;
	bool isDefined;
	Localgeo();
	Localgeo(Point,Normal);
};

#endif