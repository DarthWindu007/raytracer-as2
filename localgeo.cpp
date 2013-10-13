#include "localgeo.h"
#include "normal.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
using namespace std;


Localgeo::Localgeo(Point p, Normal nom){
   pos = p;
   normal = nom; 
}


