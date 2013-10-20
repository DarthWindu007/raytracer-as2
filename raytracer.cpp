#include "color.h"
//#include "shape.cpp"
#include "localgeo.h"
#include <vector>
#include "ray.h"
#include "light.h"
#include "shape.cpp"
#include "point.h"
#include "normal.h"





struct NearShape{
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

		
		float discriminant, t, root1,root2;
		bool ifTrue = false;

		if(shape.type == "sphere"){
			Point sphere_center = shape.center;
			float sphere_radius = ((Sphere*)&shape)->radius;
			Normal normal;
			Point point_at_intersection;
			discriminant = pow(d*(p-sphere_center),2)-(d*d)+((p-sphere_center)*(p-sphere_center)-pow(sphere_radius,2));

			if(discriminant == 0.0){
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
				Point temp = p+d*t;
				normal = Normal((temp-sphere_center)/sphere_radius);
				point_at_intersection = temp;

				return Localgeo(point_at_intersection,normal);
			}
		}



		else if(shape.type=="triangle")
		{
			Point a,b,c;
			a = shape.a;
			b = shape.b;
			c = shape.c;

			Vector triangle_normal = (b-a)^(c-a);
			bool check_parallel = (triangle_normal*d)==0.0;
			if(!check_parallel)
			{
				float time_intersection = -(triangle_normal*p+(triangle_normal*a*-1))/(triangle_normal*d);

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
							{
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
		for(int i = 0; i <s.size();i++ ){
			Point ray_point = s[i].transform.inverse() * ray.pos;
			Vector ray_direction = (s[i].transform.inverse() * ray.dir).norm();
			Ray getRay = Ray(ray_point, ray_direction);
			Localgeo local_intersect = getIntersection(getRay,s[i]);

	        if(!local_intersect.isDefined){
	        	Point local_point = local_intersect.pos;
	        	Normal local_normal = local_intersect.normal;
	        	tem_point = s[i].transform * local_point;
	        	tem_normal = (s[i].transform.inverse().transpose() * local_normal).norm();
	        	t = ray.rayGetT(tem_point);
	        	if(t > 0 && t < referrence){
	        		ifTrue = true;
	                return_shape.shape =  s[i];
	                return_point = tem_point;
	                return_normal = tem_normal;
	                referrence = t;

	      

	        	}

	        }

		}

		if(ifTrue){
			return_shape.local = Localgeo(return_point,return_normal);
			return return_shape;

		}
		NearShape temp_return;
		temp_return.local = Localgeo();
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

	   Normal interNormal = (local.normal).norm();

	   for(int i=0; i < lights.size(); i++)
	   {
	   		Light first = lights[i];
	   		if(first.type =="point")
	   		{
	   			Vector lightDir = (first.pos - local.pos).norm();
	   			
	   			shadowRay = Ray(local.pos + local.normal*0.001f,lightDir);

	   			shadow_hit = getFirst(shadowRay,shapes);

	   			if(!shadow_hit.local.isDefined||shadowRay.rayGetT(first.pos)<shadowRay.rayGetT(shadow_hit.local.pos))
	   			{
	   				float dot = max(lightDir*interNormal,0.0f);
	   				Color diff = (kd*first.color)*dot;

	   				Vector r = lightDir*-1.0f + interNormal*(2.0f*(lightDir*interNormal));
	   				float dot2 = max(r*vec,0.0f);
	   				Color spec = (ks*first.color)*pow(dot2,sp);

	   				return_color= return_color+diff+spec;
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

	   }

	   return return_color+ka+em;
	}
	Color trace(Ray ray, int depth){
		Color result = Color();
		if(depth < 0)
			return result;

		NearShape ns = getFirst(ray,shapes);


		if(!ns.local.isDefined)
			return Color();

		Localgeo local = ns.local;
		Shape shape = ns.shape;

		Color ks = shape.brdf.ks;

		Normal norm = local.normal;
		Point point = local.pos;

		//Vector reflect = getReflection(ray,norm);
		//reflect=reflect.norm();

		//Ray rayReflect = Ray(point+0.001*norm,reflect);

		Vector currDir = ray.pos - point;
		currDir = currDir.norm();

		Color shade = doPhong(currDir,ns);

		result=result+shade;

		//result+=ks*trace(rayReflect,depth-1);
		return result;
	}
};

