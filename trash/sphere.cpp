#include "ray.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
#include "sphere.h"
#include "localgeo.h"
using namespace std;

// (p−c)·(p−c)−R^2 =0 
// A sphere with center c = (xc,yc,zc) and radius R
// p(t) = e + td
// (e+td − c)·(e+td − c) − R^2 =0
// (d·d) t^2 + 2d·(e−c) t+ (e−c)·(e−c)−R^2 =0
// a = d.d
// b = 2d.(e-c)
// c = (e−c)·(e−c)−R^2 

Sphere::Sphere(float r, Point c){ //, Color coloring){
     radius = r;
     center = c;
     //Color scolor = coloring;

}

Sphere::Sphere(float r, Point c, Matrix mat, BRDF col){
  radius = r;
  center = c;
  transform = mat;
  brdf = col;
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
          /*else if(discriminant == 0){
            root1 = root2 = -b/a * 0.5;
            if(root1 < ray.t_min || root2 > ray.t_max){
            	return false;
            }
            else{
            	Point p1 = ray.rayPos(root1);
            	Vector norm1 =  (p1  - this->center).norm();
            	//*local = Localgeo(ray.rayPos(root1), Normal()); // ??????
              *thit = root1;
              local->normal = Normal(norm1);
              local->pos = p1;
              return true;
            }
            

          }
          else{*/
          bool br1;
          bool br2;
          	root1 = 0.5 * (-b + sqrt(discriminant))/a;
          	root2 = 0.5 * (-b - sqrt(discriminant))/a;
            /*if(root1 < ray.t_min || root1 > ray.t_max){
            	return false;
            }
            else{
            	 Point p1 = ray.rayPos(root1);
            	 Point p2 = ray.rayPos(root2);
            	 Vector norm1 =  (p1  - this->center).norm();
            	 Vector norm2 =  (p2  - this->center).norm();
            	 *local = Localgeo(ray.rayPos(root1), Normal()); // ??????
                 return true;
            }
          }  */   
            br1 = root1 < ray.t_min || root1 > ray.t_max;
            br2 = root2 < ray.t_min || root2 > ray.t_max;

            if(!br1)
              setLocal(this,ray, thit, local, root1);
            else if(!br2)
              setLocal(this,ray,thit,local,root2);
            else
              return false;
            return true;

    //
}

bool Sphere::intersectP(Ray& ray){
        float thit = 0.0;
        Localgeo local = Localgeo(Point(),Normal());
        return this->intersect(ray,&thit,&local);

          /*
          float root1, root2;
          float  a = dot(ray.dir,ray.dir);
          float  b = dot(ray.dir, ray.pos - this->center)*2.0;
          float  c = dot(ray.pos - this->center, ray.pos - this->center) - pow(this->radius,2);

          float discriminant = pow(b,2) - 4 * a * c;
          if(discriminant < 0){
            return false;
          }
          else if(discriminant == 0){
            root1 = root2 = -b/a * 0.5;
            if(root1 < ray.t_min || root2 > ray.t_max){
              return false;
            }
            else{
              Point p1 = ray.rayPos(root1);
              Vector norm1 =  p1  - this->center;
                 return true;
            }
            

          }
          else{
            root1 = 0.5 * (-b + sqrt(discriminant))/a;
            root2 = 0.5 * (-b - sqrt(discriminant))/a;
            if(root1 < ray.t_min || root2 > ray.t_max){
              return false;
            }
            else{
               Point p1 = ray.rayPos(root1);
               Point p2 = ray.rayPos(root2);
               Vector norm1 =  p1  - this->center;
               Vector norm2 =  p2  - this->center;
                 return true;
            }
          }    */         
    //
}


