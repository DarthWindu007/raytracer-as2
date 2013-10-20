#include "color.h"
//#include "shape.cpp"
#include "localgeo.h"
#include <vector>
#include "ray.h"
#include "light.h"
//#include "shape.cpp"
#include "point.h"
#include "normal.h"
#include "brdf.h"
#include "matrix.h"


class Shape{
public:
	string type;
	float radius;
	Point center;
	Point a,b,c;
	Normal normal;
	Matrix transform;
	BRDF brdf;

	Shape(){}

	Shape(string s,Matrix trans,BRDF col){
		type = s;
		transform = trans;
		brdf = col;
	}

	//Vector getNormal(Point p){	}
};

class Triangle : public Shape{
public:
	Point a,b,c;
	Triangle(Point p1, Point p2, Point p3){
	    this-> a = p1;
	     this->b = p2;
	     this->c = p3;
	     type = "triangle";

	}

	Triangle(Point p1, Point p2, Point p3, Matrix mat, BRDF col){
	     this->a = p1;
	    this-> b = p2;
	     this->c = p3;
	     this->transform = mat;
	     this->brdf = col;
	    this->type = "triangle";
	}
};

class Sphere : public Shape{
public:
	float radius;
	Point center;
	//Point(float,Point);

	Sphere(float r, Point c){ //, Color coloring){
	     radius = r;
	     center = c;
	     //Color scolor = coloring;
	     type = "sphere";

	}

	Sphere(float r, Point c, Matrix mat, BRDF col){
	  radius = r;
	  center = c;
	  transform = mat;
	  brdf = col;
	  type="sphere";
	}
};



class NearShape{
public:
	Localgeo local;
	Shape shape;
};

extern std::vector<Shape> shapes;
extern std::vector<Light> lights;
	/**/


class Raytracer
{
public:

	Raytracer(){}

	Localgeo getIntersection(Ray ray, Shape shape){
		Point p = ray.pos;
		Vector d = ray.dir;
		//cout<<"stuff" << endl;

		
		float discriminant, t, root1,root2;
		bool ifTrue = false;
        //cout<<"ajdfkg"<<endl;

		if(shape.type == "sphere"){
			//cout<<"helooooooooooo"<<endl;

			Point sphere_center = shape.center;
			float sphere_radius = shape.radius;

			//cout << "sphere_center:   " << sphere_center << endl;
			//cout << "sphere_radius:   " << sphere_radius << endl;
		    
			Normal normal;
			Point point_at_intersection;
			float bsquared = pow(d*(p-sphere_center),2);
			float part2 = ((p-sphere_center)*(p-sphere_center)-pow(sphere_radius,2));
			discriminant =  bsquared - (d*d)*part2;

			//cout << "discriminant:      " << discriminant << endl<<endl;
			if(discriminant == 0.0){
				//cout<<"hit1"<<endl;
				t = -(d*(p-sphere_center))/(d*d);

				ifTrue = t>0;
			} else {

				root1 = (-(d*(p-sphere_center))+(sqrt(discriminant)))/(d*d);
				root2 = (-(d*(p-sphere_center))-(sqrt(discriminant)))/(d*d);

				if(root1 < 0)
					ifTrue=false;
				else if(root2 < 0)
				{
					ifTrue = true;
					t = root1;
				}
				else
				{
					ifTrue = true;
					t = root2;
				}
			}
		
			if(ifTrue){
				//cout<<"hit2"<<endl;

				Point temp = p+d*t;
				normal = Normal((temp-sphere_center)/sphere_radius);
				point_at_intersection = temp;

				return Localgeo(point_at_intersection,normal);
			}
		}


        



		else if(shape.type=="triangle")
		{   //cout<<"adkjfnskjdf"<<endl;
			Point a,b,c;
			a = shape.a;
			b = shape.b;
			c = shape.c;
           // cout<<shape.a<<endl;
           // cout<<shape.b<<endl;
           // cout<<shape.c<<endl;
			Vector triangle_normal = (b-a)^(c-a);
			bool check_parallel = (triangle_normal*d)!=0.0;

			//cout<<triangle_normal<<endl;
			if(check_parallel)
			{
				float time_intersection = -(triangle_normal*p+(triangle_normal*a*-1))/(triangle_normal*d);
                //cout << time_intersection <<endl;
				if(time_intersection>0)
				{
					Point point_at_intersection = p+time_intersection*d;
					Vector crossVal = (b-a)^(point_at_intersection-a);
					bool check1 = triangle_normal*crossVal>=0;

					if(check1)
					{
						crossVal = (c-b)^(point_at_intersection-b);
						bool check2 = triangle_normal*crossVal>=0;
						if(check2)
						{
							crossVal = (a-c)^(point_at_intersection-c);
							bool check3 = triangle_normal*crossVal>=0;
							if(check3)
							{   //cout<<triangle_normal<<endl;
								return Localgeo(point_at_intersection,triangle_normal);
							}
						}
					}


				}
			}

		}

		return Localgeo();
	}

	NearShape getFirst(Ray ray, std::vector<Shape> s){
		float t;
		float referrence= 9999999;
		bool ifTrue = false;
		Point return_point; 
		Normal return_normal;
		Point tem_point;
		Normal tem_normal;
		NearShape return_shape;
		//cout << s.size() << endl;
		//exit(1);
		//cout << "stuff" << endl;
		//cout << ray.pos << endl;
		//cout << ray.dir << endl;
		//exit(1);
		for(int i = 0; i <s.size();i++ ){
			Point ray_point = s[i].transform.inverse() * ray.pos;
			Vector ray_direction = (s[i].transform.inverse() * ray.dir).norm();
			Ray getRay = Ray(ray_point, ray_direction);
			//cout << "ray_point:   " << ray_point << "   i=   " << i <<endl;
			//cout << "ray_direction:    " << ray_direction << "     i=    "<< i << endl<<endl;
			// cout<<"in"<<endl;
			//cout<<s[i].a<<endl;
			Localgeo local_intersect = getIntersection(getRay,s[i]);
			//cout<<local_intersect.normal<<endl;
			//cout<<"out"<<endl;
			//cout << local_intersect.isDefined << endl;
	        if(local_intersect.isDefined){
	        	Point local_point = local_intersect.pos;
	        	Normal local_normal = local_intersect.normal;
	        	tem_point = s[i].transform * local_point;
	        	tem_normal = (s[i].transform.inverse().transpose() * local_normal).norm();// error division by zero
	        	//cout << "local_point = " << local_point << endl;
	        	//cout << "local_normal = " << local_normal << endl<<endl<<endl;
	        	t = ray.rayGetT(tem_point);
	        	//cout << "t values = " << t << endl<<endl<<endl;
	        	if(t > 0 && t < referrence){
	        		ifTrue = true;
	                return_shape.shape =  s[i];
	                return_point = tem_point;
	                return_normal = tem_normal;
	                referrence = t;

	      

	        	}

	        }

		}
		//cout << ifTrue << endl;
		//cout << ifTrue << endl;
		if(ifTrue){
			//cout<<"ally"<<endl;
			return_shape.local = Localgeo(return_point,return_normal);
			//cout<<return_normal<<endl;
			return return_shape;
        
		}
        //cout<<"i orie"<<endl;
		NearShape temp_return;
		temp_return.local = Localgeo();
		//cout<<temp_return.local.normal<<endl;
		return temp_return;
	}

	Color doPhong(Vector vec, NearShape ns){	//} Normal norm, Point pt, Shape shape){
	   Color return_color,ka,kd,ks,em;
	   return_color = Color();
	   Ray shadow;

	   Localgeo local = ns.local;
	   Shape shape = ns.shape;

	   ka = shape.brdf.ka;
	   kd = shape.brdf.kd;
	   ks = shape.brdf.ks;
	   em = shape.brdf.em;
	   float sp = shape.brdf.sp;

	   Ray shadowRay;
	   NearShape shadow_hit;
       //cout<<local.normal<<endl;
	   Normal interNormal = (local.normal).norm();
        
	   for(int i=0; i < lights.size(); i++)
	   {
	   		Light first = lights[i];
	   		if(first.type =="point")
	   		{
	   			Vector lightDir = (first.pos - local.pos).norm();
	   			
	   			shadowRay = Ray(local.pos + local.normal*0.001f,lightDir);

	   			shadow_hit = getFirst(shadowRay,shapes);
                //bool u = shadow_hit.shape.type == "";
                //cout<<shadow_hit.shape.type<<endl;
	   			if(!shadow_hit.local.isDefined||shadowRay.rayGetT(first.pos)<shadowRay.rayGetT(shadow_hit.local.pos))
	   			{  // cout<< interNormal<<endl;
	   				//cout<< lightDir<<endl;
	   				float dot = max(lightDir*interNormal,0.0f);
	   				//cout<<dot<<endl;
	   				Color diff = (kd*first.color)*dot;
                    //cout<<diff<<endl;
	   				Vector r = lightDir*-1.0f + interNormal*(2.0f*(lightDir*interNormal));
	   				float dot2 = max(r*vec,0.0f);
	   				Color spec = (ks*first.color)*pow(dot2,sp);
                    
	   				return_color= return_color+diff+spec;
	   				//cout<<return_color<<endl;
	   				//cout << "uiuiuiuuiiui" << endl;
	   			}

	   		}
	   		else if(first.type == "directional")
	   		{
	   			Vector lightDir = (first.dir).norm();

	   			shadowRay = Ray(local.pos + local.normal*0.001f,lightDir);

	   			shadow_hit = getFirst(shadowRay,shapes);	

	   			if(!shadow_hit.local.isDefined)
	   			{
	   				float dot = max(lightDir*interNormal,0.0f);
	   				Color diff = (kd*first.color)*dot;

	   				Vector r = lightDir*-1.0f + interNormal*(2.0f*(lightDir*interNormal));
	   				float dot2 = max(r*vec,0.0f);
	   				Color spec = (ks*first.color)*pow(dot2,sp);

	   				return_color=return_color+diff+spec;

	   			}
	   		}

	   	//cout << return_color << endl;
	   }

	   return return_color+ka+em;
	}
	Color trace(Ray ray, int depth){
		Color result = Color();
		//cout << "wtf???????" << endl;
		if(depth < 0)
			return result;

		NearShape ns = getFirst(ray,shapes);

		

		//cout << "wtf???????" << endl;
		//cout << ns.local.isDefined <<endl;
		if(!ns.local.isDefined)
			return Color();

		//cout << "what is going on" << endl;
		Localgeo local = ns.local;
		Shape shape = ns.shape;
		//if(shape.type=="sphere"){
			
			//cout << shape.center << endl;
		//}
		//cout << lights[0].color << endl;
		Color ks = shape.brdf.ks;

		Normal norm = local.normal;
		Point point = local.pos;

		//cout << local.normal << endl;

		//Vector reflect = ray.getReflection(norm);
		//reflect=reflect.norm();

		//Ray rayReflect = Ray(point+0.001*norm,reflect);

		Vector currDir = ray.pos - point;
		currDir = currDir.norm();

		Color shade = doPhong(currDir,ns);

		result=result+shade;
		//cout << result << endl;
		//result+=ks*trace(rayReflect,depth-1);
		return result;
	}
};

