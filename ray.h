#ifndef RAY_H
#define RAY_H
#include "vector.h"
#include "point.h"
#include "normal.h"
class Ray {
public:
    Point pos;
    Vector dir;
    float t_min;
    float t_max;
    Ray();
    Ray(Point,Vector);
    float rayGetT(Point);
    Point rayPos(float);
    Vector getReflection(Normal);
};

#endif
