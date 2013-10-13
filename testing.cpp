#include "vector.h"
#include "point.h"
#include <iostream>
#include <typeinfo>
#include "math.h"
#include "color.h"
#include "normal.h"
#include "ray.h"
#include "math.h"
#include "matrix.h"
#include "transformation.h"
#include "brdf.h"
#include "sample.h"
#include "localgeo.h"
#include "algebra3.h"


using namespace std;


int main(){
	Vector a = Vector(1,2,3);
	Vector b = Vector(2,2,2);
	Vector c = b-a;

	cout << c << endl;
	cout << b-1 << endl;
	cout << 1-b << endl;
	cout << 3*b << endl;

	Color col = Color(0.6,0.5,0.2);
	cout<<col<<endl;

	Vector s = Vector(1,1,1);
	Normal n = Normal(1,1,1);
	cout<<s.norm()<<endl;
	cout<<n<<endl;
	Matrix m1 = Matrix();

	float stuff[16] = {8,4,4,4,	9,5,9,5,	6,5,4,6,	5,4,4,5};
	Matrix m2 = Matrix(stuff);

	cout<<m1<<endl;
	cout<<m1-m2<<endl;

}