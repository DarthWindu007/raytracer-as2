#include "brdf.h"
#include "localgeo.h"
#include "material.h"
#include <iostream>
#include <typeinfo>
using namespace std;

Material::Material(){
	//this->constantBRDF = NULL;
}

void Material::getBRDF(Localgeo &local, BRDF* brdf){
	this->constantBRDF = *brdf;
}
