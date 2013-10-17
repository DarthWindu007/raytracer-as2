#include "pointlight.h"
#include "color.h"
#include "localgeo.h"
#include "ray.h"
#include "light.h"

Pointlight::Pointlight()
{
        this->pos = Point();
        this->color = Color(1.0,1,1);
}

Pointlight::Pointlight(Point p, Color c){
        this->pos = p;
        this->color = c;
}

void Pointlight::generateLightRay(Localgeo& local, Ray* lray, Color* lcolor) {
        Vector rayDir = (this->pos - local.pos).norm();
        *lray = Ray(local.pos, rayDir, 0,100); // ???? not sure what the t_min and t_max are suppose to be  ????
        *lcolor = this->color;
}
