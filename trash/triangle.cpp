#include "ray.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
#include "triangle.h"
#include "algebra3.h"
using namespace std;

// (p−c)·(p−c)−R^2 =0 
// A sphere with center c = (xc,yc,zc) and radius R
// p(t) = e + td
// (e+td − c)·(e+td − c) − R^2 =0
// (d·d) t^2 + 2d·(e−c) t+ (e−c)·(e−c)−R^2 =0
// a = d.d
// b = 2d.(e-c)
// c = (e−c)·(e−c)−R^2 

Triangle::Triangle(Point p1, Point p2, Point p3){
     a = p1;
     b = p2;
     c = p3;

}

Triangle::Triangle(Point p1, Point p2, Point p3, Matrix mat, BRDF col){
     a = p1;
     b = p2;
     c = p3;
     transform = mat;
     brdf = col;
}

float dot(Point p1, Point p2){
  return p1.x*p2.x+p1.y*p2.y+p1.z*p2.z;
}

float dot(Vector p1, Point p2){
  return p1.x*p2.x+p1.y*p2.y+p1.z*p2.z;
}

float dot(Vector p1, Vector p2){
  return p1.x*p2.x+p1.y*p2.y+p1.z*p2.z;
}



bool Triangle::intersect(Ray& ray, float* thit, Localgeo* local){
          float x1,x2,x3,y1,y2,y3,z1,z2,z3,B,A,V,T;
          
           x1 = this->a.x - this->b.x;
           x2 = this->a.y - this->b.y;
           x3 = this->a.z - this->b.z;
           y1 = this->a.x - this->c.x;
           y2 = this->a.y - this->c.y;
           y3 = this->a.z - this->c.z;
           z1 = ray.dir.x;
           z2 = ray.dir.y;
           z3 = ray.dir.z;

           A = x1*(y2*z3 - y3*z2) - y1 *(x2*z3-x3*z2) + z1*(x2*y3 - x3*y2);

          // solving for B
          


           x1 = this->a.x - ray.pos.x;
           x2 = this->a.y - ray.pos.y;
           x3 = this->a.z - ray.pos.z;
           y1 = this->a.x - this->c.x;
           y2 = this->a.y - this->c.y;
           y3 = this->a.z - this->c.z;
           z1 = ray.dir.x;
           z2 = ray.dir.y;
           z3 = ray.dir.z;
           
           B = (x1*(y2*z3 - y3*z2) - y1 *(x2*z3-x3*z2) + z1*(x2*y3 - x3*y2))/A;

           x1 = this->a.x - this->b.x;
           x2 = this->a.y - this->b.y;
           x3 = this->a.z - this->b.z;
           y1 = this->a.x - ray.pos.x;
           y2 = this->a.y - ray.pos.y;
           y3 = this->a.z - ray.pos.z;
           z1 = ray.dir.x;
           z2 = ray.dir.y;
           z3 = ray.dir.z;

           // solving for V
           
           V = (x1*(y2*z3 - y3*z2) - y1 *(x2*z3-x3*z2) + z1*(x2*y3 - x3*y2))/A;
           
           // solving for T
           x1 = this->a.x - this->b.x;
           x2 = this->a.y - this->b.y;
           x3 = this->a.z - this->b.z;
           y1 = this->a.x - this->c.x;
           y2 = this->a.y - this->c.y;
           y3 = this->a.z - this->c.z;
           z1 = this->a.x - ray.pos.x;
           z2 = this->a.y - ray.pos.y;
           z3 = this->a.z - ray.pos.z;
           
           T = (x1*(y2*z3 - y3*z2) - y1 *(x2*z3-x3*z2) + z1*(x2*y3 - x3*y2))/A;

           Point P = this->a + B*(this->b-this->a) + V*(this->c - this->a);
           *thit = T;
           Vector p1 = this->b-this->a;
           Vector p2 = this->c-this->a;
           vec3 cr = vec3(p1.x,p1.y,p1.z)^vec3(p2.x,p2.y,p2.z);
           local->normal = Normal(cr[0],cr[1],cr[2]);
           local->pos = P;

           if(T < ray.t_min || T > ray.t_max){
            return false;
          }
           if(V < 0 || V > 1){
            return false;
           }
           if(B< 0 || B > 1-V){
            return false;
           } 

           return true;


}

bool Triangle::intersectP(Ray& ray){
          float x1,x2,x3,y1,y2,y3,z1,z2,z3,B,A,V,T;
          
           x1 = this->a.x - this->b.x;
           x2 = this->a.y - this->b.y;
           x3 = this->a.z - this->b.z;
           y1 = this->a.x - this->c.x;
           y2 = this->a.y - this->c.y;
           y3 = this->a.z - this->c.z;
           z1 = ray.dir.x;
           z2 = ray.dir.y;
           z3 = ray.dir.z;

           A = x1*(y2*z3 - y3*z2) - y1 *(x2*z3-x3*z2) + z1*(x2*y3 - x3*y2);

          // solving for B
          


           x1 = this->a.x - ray.pos.x;
           x2 = this->a.y - ray.pos.y;
           x3 = this->a.z - ray.pos.z;
           y1 = this->a.x - this->c.x;
           y2 = this->a.y - this->c.y;
           y3 = this->a.z - this->c.z;
           z1 = ray.dir.x;
           z2 = ray.dir.y;
           z3 = ray.dir.z;
           
           B = (x1*(y2*z3 - y3*z2) - y1 *(x2*z3-x3*z2) + z1*(x2*y3 - x3*y2))/A;

           x1 = this->a.x - this->b.x;
           x2 = this->a.y - this->b.y;
           x3 = this->a.z - this->b.z;
           y1 = this->a.x - ray.pos.x;
           y2 = this->a.y - ray.pos.y;
           y3 = this->a.z - ray.pos.z;
           z1 = ray.dir.x;
           z2 = ray.dir.y;
           z3 = ray.dir.z;

           // solving for V
           
           V = (x1*(y2*z3 - y3*z2) - y1 *(x2*z3-x3*z2) + z1*(x2*y3 - x3*y2))/A;
           
           // solving for T
           x1 = this->a.x - this->b.x;
           x2 = this->a.y - this->b.y;
           x3 = this->a.z - this->b.z;
           y1 = this->a.x - this->c.x;
           y2 = this->a.y - this->c.y;
           y3 = this->a.z - this->c.z;
           z1 = this->a.x - ray.pos.x;
           z2 = this->a.y - ray.pos.y;
           z3 = this->a.z - ray.pos.z;
           
           T = (x1*(y2*z3 - y3*z2) - y1 *(x2*z3-x3*z2) + z1*(x2*y3 - x3*y2))/A;


           if(T < ray.t_min || T > ray.t_max){
            return false;
          }
           if(V < 0 || V > 1){
            return false;
           }
           if(B< 0 || B > 1-V){
            return false;
           }
           return true;
             
    
}


