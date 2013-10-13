#include "brdf.h"
#include "vector.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;
BRDF::BRDF(){
	kd=Color();
	ks=Color();
	ka=Color();
	kr=Color();
}
BRDF::BRDF(Color a,Color b, Color c,Color d){
    kd = a;
    ks = b;
    ka = c;
    kr = d; 
}
