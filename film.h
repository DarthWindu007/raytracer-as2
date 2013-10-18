#ifndef FILM_H
#define FILM_H

#include "sample.h"
#include "color.h"
#include "FreeImage.h"
#include <iostream>


using namespace std;




class Film
{
public:
        FIBITMAP* bitmap;
        RGBQUAD filmColor;
        Film();
        Film(int,int,int);
        void commit(Sample&, Color&);
        void writeImage();
};

inline Film::Film(){
        FreeImage_Initialise();
        bitmap = FreeImage_Allocate(0, 0, 0);
}

inline Film::Film(int w, int h, int bpp){
        FreeImage_Initialise();
        bitmap = FreeImage_Allocate(w, h, bpp);
}

inline void Film::commit(Sample& s, Color& c){
        filmColor.rgbRed = min((c.r * 255.0f), 255.0f);
        filmColor.rgbGreen = min((c.g * 255.0f), 255.0f);
        filmColor.rgbBlue = min((c.b * 255.0f), 255.0f);
        FreeImage_SetPixelColor(bitmap, (unsigned int)s.x, (unsigned int)s.y, &filmColor);
}

inline void Film::writeImage(){
        
        if(FreeImage_Save(FIF_PNG, bitmap, "raytrace.png", 0))
                cout << "Image Saved Successfully!!" << endl;
        
}

#endif