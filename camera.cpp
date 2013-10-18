#include "algebra3.h"
//#include "raytracer.h"
#include "vector.h"
#include "point.h"
#include "ray.h"
#include "sample.h"
#include "camera.h"
#include <math.h>
#include "globaldef.cpp"
#define _USE_MATH_DEFINES
using namespace std;


Camera::Camera() 
{ // lookfrom is a Point global variable
  // lookat is a Point global variable
  // up is a Vector global variable
  // computing vector W, U, V (Camera coordinates)
  this->pos = lookfrom;
  this->W = (lookfrom - lookat).norm();
  vec3 upCW = vec3(up.x,up.y,up.z)^vec3(W.x,W.y,W.z);
  this->U = Vector(upCW).norm();
  vec3 WCU = vec3(W.x,W.y,W.z)^vec3(U.x,U.y,U.z);
  this->V = Vector(WCU).norm();
}

void Camera::generateRay(Sample &sample, Ray* ray)
{ 
  float d = 2.0; // lookfrom to image plane
  float size_ratio = P_width/P_height;
  float height= d * tan(M_PI*fov/(2*180));
  float width = height * size_ratio;
  float nx = P_width;
  float ny = P_height;
  
  // dimension of the image plane, (l,t),(r,t),(l,b),(r,b)
  float t = height/2;
  float b = -t;
  float r = width/2;
  float l = -r;
  
  // pixel at position (i,j)
  float i = sample.x;
  float j = sample.y;
  // computing weights: u and v
  float u = l +(r-l)*(i+0.5)/nx;
  float v = b +(t-b)*(j+0.5)/ny;

  Vector direction_v = this->W * -d + this->U * u + this->V * v; 
  Point  origin = this->pos;
  *ray = Ray(origin,direction_v,0,10000);

}