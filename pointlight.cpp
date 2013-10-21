#include "pointlight.h"
#include "color.h"
#include "localgeo.h"
#include "ray.h"
#include "light.h"

Pointlight::Pointlight()
{
        this->pos = Point();
        this->color = Color(1.0,1,1);
        this->type = "point";
}

Pointlight::Pointlight(Point p, Color c, Color at){
        this->pos = p;
        this->color = c;
        this->type = "point";
        this-> att = at;
}
