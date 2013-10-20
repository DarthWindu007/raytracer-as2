#include "point.h"
#include "vector.h"
#include "normal.h"
#include "ray.h"

#include <math.h>

#define _USE_MATH_DEFINES



class  Camera
{
public:
	Point lookfrom, lookat;
	Vector up;
	float fov, ratio;
	int pixelwidth,pixelheight;
	Vector cameraDir,cameraUP,cameraR;
	float right,left,top,bot;

	Camera(){
		lookfrom = Point();
		lookat = Point();
		up = Vector();
		fov = 0;
		pixelwidth = 640;
		pixelheight = 480;
		ratio = (1.0f*pixelwidth)/pixelheight;
	}
	Camera(Point lf,Point la,Vector u,float f,int pw,int ph){
		lookfrom = lf;
		lookat = la;
		up = u;
		fov = f;
		pixelwidth = pw;
		pixelheight = ph;
		ratio = (1.0f*pixelwidth)/pixelheight;
		cameraDir = (lookat-lookfrom).norm(); // camera __looking direction 
		cameraR = (cameraDir^up).norm();
		up = (cameraR^cameraDir).norm();
		right = ratio*tan(M_PI*fov/360.0f);
		left = -right;
		top = tan(M_PI*fov/360.0f);
		bot = -top;

        cout << cameraDir<< endl;
        cout << cameraR<< endl;
        cout << up<< endl;
        cout << f<< endl;
        cout << pw<< endl;
        cout << ph<< endl;
        cout<<M_PI<<endl;
		
	}

	Ray generateRay(int x, int y){
		float u = left + (right - left)*(x+0.5)/pixelwidth;
		float v = bot + (top - bot)*(y+0.5)/pixelheight;

		Vector dir = (cameraDir + u*cameraR + v*up).norm(); // warning: check vector operators #######################

		return Ray(lookfrom,dir);

	}
};