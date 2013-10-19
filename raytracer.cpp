#include "algebra3.h"
#include "vector.h"
#include "point.h"

#include "light.h"
#include "ray.h"
#include "sample.h"
#include "raytracer.h"
#include "triangle.h"
#include <math.h>
#include <typeinfo>
#include "globaldef.cpp"
#define _USE_MATH_DEFINES
using namespace std;

// Raytracer default constructor sets the threshold == 5.
// And has a camera_pos taken from lookfrom
Vector operator-(Vector v, Normal v2){
    return Vector(v.x-v2.x,v.y-v2.y,v.z-v2.z);
}
Vector operator+(Vector v, Normal v2){
    return Vector(v.x+v2.x,v.y+v2.y,v.z+v2.z);
}
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
  cout<<"??????????????????????????????????????????" << endl;
  if(depth > this->threshold){
    *color = Color(); // black
    cout<<"----------------------------------------------------" << endl;
    return;
  }else{
    float thit;
    Localgeo intersection,closestInter;//,closest;
    //Localgeo first_intersection;
    float minDistance = 99999; // I guess we have to set an abituary value for min distance
    Primitive* closest = 0;
    //transorms
    bool transformed = false;
    vector<Transformation> transforms;
    //loop through all primitives GLOBAL
    cout << "size of prims:  " << prims.size() << endl;
    cout << prims[0] << endl;

    //for(int ind_i = 0; ind_i < prims.size();ind_i++){
    for(vector<Primitive*>::iterator iter = prims.begin(); iter != prims.end(); ++iter){
        Primitive* s = *iter;
        //cout << "wat?0" << endl;
        //Primitive** iter = &prims[ind_i];
        //cout << "wat?0" << endl;
        //Primitive* s = *iter;
        //cout << "wat?0" << endl;
        //if intersection
        cout << "does intersect?: " << endl;

        vector<Transformation>* v;

        Triangle temptri = Triangle(Point(0,0,0),Point(0,1,0),Point(1,0,0),new BRDF(),v);
        //temptri.intersect(ray,&thit,&intersection);
        //(*s).intersect(ray, &thit, &intersection);
        //cout << "goes past intersect" << endl;
        cout << typeid(*(prims.front()) ).name() << endl;
        temptri.printstuff();
        cout << "goes past intersect" << endl;
        if((*s).intersect(ray, &thit, &intersection)){
            cout << "thit:   " << thit << endl;
            //keep track of the closest intersection to the camera, since that is what we will draw
            //float dist = (intersection.pos - eyePos).magnitude();
            if(thit < minDistance){
                minDistance = thit;
                closest = s;
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
                (*closest).getBRDF(closestInter, &brdf);
                *color = brdf.ka;

                //Reflection info. Need r vector like in specular. Find way to send this to shading?
                Vector rDir = ray.dir - (closestInter.normal * ((closestInter.normal*ray.dir)*2));
                rDir = rDir.norm();
                Ray r = Ray(closestInter.pos, rDir, 0.0, ray.t_max);
                /////////////////////////////////////////////////////////////////////////////////


                for(vector<Light*>::iterator lIter = lights.begin(); lIter != lights.end(); ++ lIter){
                        Light* l = *lIter;
                        (*l).generateLightRay(closestInter, &lray, &lcolor);
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

*/                      cout << "shadow?:" << isShadow << endl;
                        if(!isShadow){
                                Color refColor = Color();

                                //make recursive call if there is any reflectivity
                                if(brdf.kr.r != 0 && brdf.kr.g != 0 && brdf.kr.b != 0){

                                        trace(r, depth+1, &refColor);
                                }
                                //calculate Phong stuff
                                *color = *color + shading(closestInter, brdf, ray, lray, lcolor) + refColor*brdf.kr;
                                cout << "shadow and color:" << *color << endl;
                                //*color = Color(1,0,0);
                        }
                }
              }
            }
          }
                


Color Raytracer::shading(Localgeo& point, BRDF brdf, Ray& origRay, Ray& lray, Color lcolor){
        //diffuse component
        //dot product between normal and light vectors
        float diff = point.normal * (lray.dir);

        //specular component
        Vector v = origRay.pos - point.pos; //for reflections, eye needs to be point of where first ray came from
        v = v.norm();
        Vector r = (lray.dir * -1) + (point.normal * (2 * diff));
        r = r.norm();
        float spec = r * v;

        return (lcolor * brdf.kd) * max(diff,0.0f) + (lcolor * brdf.ks) * pow(max(spec,0.0f),brdf.p);
}