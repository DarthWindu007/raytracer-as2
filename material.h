#ifndef MATERIAL_H
#define MATERIAL_H
#include "algebra3.h"
#include "brdf.h"
#include "localgeo.h"
#include <iostream>
#include <typeinfo>
using namespace std;

class Material {
public:
    BRDF constantBRDF;
    Material();
    void getBRDF(Localgeo&, BRDF*);
};

std::ostream& operator<<(std::ostream&, const Localgeo&);

#endif