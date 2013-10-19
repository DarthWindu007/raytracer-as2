#include "algebra3.h"
//#include "raytracer.h"
#include "vector.h"
#include "point.h"
#include "ray.h"
#include "sample.h"
#include "camera.h"
#include <math.h>

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
  /*
  float d = 2.0; // lookfrom to image plane
  float size_ratio = P_width/P_height;
  float height= d * tan(M_PI*fov/(2*180));
  float width = d * tan(M_PI*(fov*size_ratio)/(2*180)) * size_ratio;
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
  *ray = Ray(origin,direction_v.norm(),0,100);
  */
    /*
    Vector dir = lookat-this->pos;
    dir.norm();
    Vector u = dir^up;
    u.norm();
    Vector v = u^dir;
    v.norm();
 
        Vector xinc = u*2*tan(fov*M_PI/180/2)/P_width * P_width/P_height;
    Vector yinc = v*2*tan(fov*M_PI/180/2)/P_height;

    Vector vec = dir + yinc*0.5*(2*sample.y+1-P_height) + xinc*0.5*(2*sample.x+1-P_width);
    vec.norm();
 
    *ray = Ray(pos, vec, 1, 100);
    */
      /*
        vec3 w = eye - this->pos;
        w.normalize();
        
        vec3 u;
        u = up^w;//cross(u, up, w);
        u.normalize();

        vec3 v;
        v = w^u;//cross(v, w, u);
        
        double z = P_height/2/tan(fov/2*nv_to_rad);
        double fovxTerm =  2 * atan(P_width/2/z);
        double alpha, beta;
        alpha = tan(fovxTerm/2)*((sample.x-((double) P_width/2.0))/((double) P_width/2.0));
        beta = tan((fov/2.0)*nv_to_rad)*((((double) P_height/2.0)-sample.y)/((double) P_height/2.0));
        vec3 direction = alpha*u + beta*v - w;
        direction.normalize();

        Point eyePoint = Point(eye.x, eye.y, eye.z);
        ray->pos = eyePoint;
        ray->dir = direction;
        ray->t_min = 0.001;
        ray->t_max = 8000;
        */
    float fovrad = (fov/2.0)*3.14159265/180.0;
    float beta = tan(fovrad)*(-(P_height/2.0) + sample.y)/(P_height/2.0);
    float alpha = tan(fovrad)*(P_width/P_height)*((sample.x - (P_width - 1.0)/2.0))/((P_width - 1.0)/2.0);

    vec3 t1 = vec3(U.x*alpha,U.y*alpha,U.z*alpha); //u*alpha
    vec3 t2 = vec3(V.x*beta,V.y*beta,V.z*beta);  //v*beta
    vec3 t3 = vec3(0,0,0);
    vec3 t4 = vec3(0,0,0);
    t4 = t1 +t2;  //add alpha*u and beta*v components
    t3 = t4-vec3(W.x,W.y,W.z);  // subtract w
    t3.normalize();// t3 = (alpha*u + beta*v - w)/ |(alpha*u + beta*v - w)|    a.k.a direction normalized
    Point newlf = Point(lookfrom.x,lookfrom.y,lookfrom.z);
    *ray = Ray(newlf, t3, 0.0001,1000); //ray = eye + (alpha*u + beta*v - w)/ |(alpha*u + beta*v - w)|

}