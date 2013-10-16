#ifndef RAY_H
#define RAY_H
#include "vector.h"
#include "point.h"
class Ray {
public:
    Point pos;
    Vector dir;
    float t_min;
    float t_max;
    Ray();
    Ray(Point , Vector , float ,float );
    float rayGetT(Point);
    Point rayPos(float);
};

#endif
