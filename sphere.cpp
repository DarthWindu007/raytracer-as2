#include "ray.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
#include "sphere.h"
#include "localgeo.h"
#include "brdf.h"       //
#include <vector>         //
#include "transformation.h" //
using namespace std;

// (p−c)·(p−c)−R^2 =0 
// A sphere with center c = (xc,yc,zc) and radius R
// p(t) = e + td
// (e+td − c)·(e+td − c) − R^2 =0
// (d·d) t^2 + 2d·(e−c) t+ (e−c)·(e−c)−R^2 =0
// a = d.d
// b = 2d.(e-c)
// c = (e−c)·(e−c)−R^2 

Sphere::Sphere(float r, Point c,BRDF* brdf_sphere, vector<Transformation>* TransValue){ //, Color coloring){
     radius = r;
     center = c;
     brdf = brdf_sphere;
     Tvalue = TransValue;
}

float Sphere::dot(Point p1, Point p2){
	return p1.x*p2.x+p1.y*p2.y+p1.z*p2.z;
}

float Sphere::dot(Vector p1, Point p2){
	return p1.x*p2.x+p1.y*p2.y+p1.z*p2.z;
}

float Sphere::dot(Vector p1, Vector p2){
  return p1.x*p2.x+p1.y*p2.y+p1.z*p2.z;
}

void setLocal(Sphere* s, Ray& ray, float* thit, Localgeo* local, float root1){
  *thit = root1;
  Point p1 = ray.rayPos(root1);
  Vector norm1 = (p1-s->center).norm();
  local->normal = Normal(norm1);
  local->pos=p1;
}

bool Sphere::intersect(Ray& ray, float* thit, Localgeo* local){
          float root1, root2;
          float  a = dot(ray.dir,ray.dir);
          float  b = dot(ray.dir, ray.pos - this->center)*2.0;
          float  c = dot(ray.pos - this->center, ray.pos - this->center) - pow(this->radius,2);

          float discriminant = pow(b,2) - 4 * a * c;
          if(discriminant < 0){
          	return false;
          }
          bool br1;
          bool br2;
          	root1 = 0.5 * (-b + sqrt(discriminant))/a;
          	root2 = 0.5 * (-b - sqrt(discriminant))/a;  
            br1 = root1 < ray.t_min || root1 > ray.t_max;
            br2 = root2 < ray.t_min || root2 > ray.t_max;

            if(!br1)
              setLocal(this,ray, thit, local, root1);
            else if(!br2)
              setLocal(this,ray,thit,local,root2);
            else
              return false;
            return true;

}

bool Sphere::isTransformed(){
     if((this->Tvalue)->size() == 0){
      return false;
     }
     return true;
}

void Sphere::getBRDF(Localgeo& loc, BRDF* brdf){
     brdf = this->brdf;
}

vector<Transformation> Sphere::getTransform(){
     return  *Tvalue;
}

bool Sphere::intersectP(Ray& ray){
        float thit = 0.0;
        Localgeo local = Localgeo(Point(),Normal());
        return this->intersect(ray,&thit,&local);
}




