#include "algebra3.h"
#include "vector.h"
#include "point.h"
#include "ray.h"
#include "sample.h"
#include "raytracer.h"
#include <math.h>
#include "globaldef.cpp"
#define _USE_MATH_DEFINES
using namespace std;

// Raytracer default constructor sets the threshold == 5.
// And has a camera_pos taken from lookfrom
Raytracer::Raytracer() 
{ 
  this->threshold = 5; 
  this->camera_pos = lookfrom; // global variable
}
Raytracer::Raytracer(int t, Point p) 
{ this->threshold = t;
  this->camera_pos = p;
}

void Raytracer::trace(Ray& ray, int depth, Color* color){
  if(depth > this->threshold){
    *color = Color(); // black
  }else{
        float thit;
        LocalGeo intersection , closestInter;
        LocalGeo closest;
        float minDistance = 99999; // I guess we have to set an abituary value for min distance
        Primitive* closest = 0;
        //transorms
        bool transformed = false;
        vector<Transform> transforms;
        //loop through all primitives GLOBAL
        for(vector<Primitive*>::iterator iter = prims.begin(); iter != prims.end(); ++iter){
                Primitive* s = *iter;
                //if intersection
                if((*s).intersect(ray, &thit, &intersection)){
                        //keep track of the closest intersection to the camera, since that is what we will draw
                        //float dist = (intersection.pos - eyePos).magnitude();
                        if(thit < minDistance){
                                minDistance = thit;
                                //closest = s;
                                closestInter = intersection;

                                //get transforms of new closest object
                        /*        if((*s).isTransformed() == true) {
                                        transformed = true;
                                        transforms = (*s).getTrans();
                                } else {
                                        transformed = false;
                                }
                          */      
                        }
                }
        }
        //compute shading
        if(minDistance != 99999){

              /*  
              if(transformed == true){ ///////
                        for (int i = 0 ; i < transforms.size(); i++)
                        {
                                //for each matrix
                                for (int j = 0; j < transforms.at(i).transforms.size(); j++)
                                {
                                        Matrix m = transforms.at(i).transforms.at(j);
                                        Matrix n = transforms.at(i).nTransforms.at(j);
                                        if (m.mat[0][0] == 1 && m.mat[1][1] == 1 && m.mat[2][2] == 1) //translate
                                        {
                                                ray.pos = m*ray.pos;

                                                //closestInter.pos = n*(closestInter.pos);

                                                //ray.dir = m*ray.dir;
                                                //m.transpose();
                                                //closestInter.norm = n*(closestInter.norm);
                                                //m.transpose();
                                        }
                                        else //scale
                                        {
                                                ray.pos = m*ray.pos;
                                                ray.dir = m*ray.dir;

                                                //closestInter.pos = n*(closestInter.pos);

                                                //m.transpose();
                                                //closestInter.norm = n*(closestInter.norm);
                                                //intersection.norm.normalize();
                                                //m.transpose();

                                        }
                                }
                        }
                }////////
                */

                Ray lray = Ray();
                Ray tlray = Ray();
                Color lcolor = Color();
                BRDF brdf = BRDF();
                (*closest)->getBRDF(closest, &brdf);
                *color = brdf->ka;

                //Reflection info. Need r vector like in specular. Find way to send this to shading?
                Vector rDir = ray->dir - (closest->normal * (2 * closest->normal * ray->dir ));
                rDir = rDir->norm();
                Ray r = Ray(closestInter->pos, rDir, 0.0, ray->t_max);
                /////////////////////////////////////////////////////////////////////////////////


                for(vector<Light*>::iterator lIter = lights.begin(); lIter != lights.end(); ++ lIter){
                        Light* l = *lIter;
                        (*l).generateLightRay(closest, &lray, &lcolor);
                        //tlray = lray;

                        //check for intersection with primitives for shadows
                        bool isShadow = false;
                        for(vector<Primitive*>::iterator iter = prims.begin(); iter != prims.end(); ++iter){
                                Primitive* s = *iter;
                                if((*s).intersectP(lray)){
                                        isShadow = true;
                                        break;
                                }
                        }
/*
                        if(transformed == true){
                                for (int i = 0 ; i < transforms.size(); i++)
                                {
                                        //for each matrix
                                        for (int j = 0; j < transforms.at(i).transforms.size(); j++)
                                        {
                                                Matrix m = transforms.at(i).transforms.at(j);
                                                Matrix n = transforms.at(i).nTransforms.at(j);
                                                if (m.mat[0][0] == 1 && m.mat[1][1] == 1 && m.mat[2][2] == 1) //translate
                                                {
                                                        //lray.pos = m*lray.pos;
                                                        //closestInter.pos = n*(closestInter.pos);

                                                        //ray.dir = m*ray.dir;
                                                        //m.transpose();
                                                        //closestInter.norm = n*(closestInter.norm);
                                                        //m.transpose();
                                                }
                                                else //scale
                                                {
                                                        //lray.pos = m*lray.pos;
                                                        //lray.dir = m*lray.dir;
                                                        //closestInter.pos = n*(closestInter.pos);

                                                        //m.transpose();
                                                        //closestInter.norm = n*(closestInter.norm);
                                                        //intersection.norm.normalize();
                                                        //m.transpose();

                                                }
                                        }
                                }
                        }

*/
                        if(!isShadow){
                                Color refColor = Color();

                                //make recursive call if there is any reflectivity
                                if(brdf->kr->r != 0 && brdf->kr->g != 0 && brdf->kr->b != 0){

                                        trace(r, depth+1, &refColor);
                                }
                                //calculate Phong stuff
                                *color = *color + shading(closest, brdf, ray, lray, lcolor) + brdf->kr*refColor;
                                //*color = Color(1,0,0);
                        }
                }
              }
            }
          }
                


Color RayTracer::shading(Localgeo& point, BRDF brdf, Ray& origRay, Ray& lray, Color lcolor){
        //diffuse component
        //dot product between normal and light vectors
        float diff = point->normal * (lray->dir);

        //specular component
        Vector v = origRay->pos - point->pos; //for reflections, eye needs to be point of where first ray came from
        v = v->normalize();
        Vector r = (lray->dir * -1) + (point->norm * (2 * diff));
        r = r->normalize();
        float spec = r * v;

        return (lcolor * brdf->kd) * max(diff,0.0f) + (lcolor * brdf.ks) * pow(max(spec,0.0f),brdf->sp);
}