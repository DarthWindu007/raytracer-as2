#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "FreeImage.h"
#include "vector.h"
//#include "shape.cpp"
#include "light.h"
#include "point.h"
#include "transformation.h"
#include "directionallight.h"
#include "pointlight.h"
#include "color.h"
#include "brdf.h"
#include "camera.cpp"
#include "raytracer.cpp"



int maxdepth = 5;
int pixelwidth, pixelheight;
std::string fname = "output.png";

std::vector<Shape> shapes;
std::vector<Light> lights;
std::vector<Triangle> triangles;

std::vector<Point> vertices;

std::vector<Matrix> trans;

Point lookfrom, lookat;
Vector up;
float fov;

Color currKa=Color();
Color currKd = Color();
Color currKs = Color();
Color currEm = Color();
Color currKr = Color();
float currSp = 1;

Color attenuation = Color();

void loadScene(std::string file) {

  //store variables and set stuff at the end


  std::ifstream inpfile(file.c_str());
  if(!inpfile.is_open()) {
    std::cout << "Unable to open file" << std::endl;
  } else {
    std::string line;
    //MatrixStack mst;

    while(inpfile.good()) {
      std::vector<std::string> splitline;
      std::string buf;

      std::getline(inpfile,line);
      std::stringstream ss(line);

      while (ss >> buf) {
        splitline.push_back(buf);
      }
      //Ignore blank lines
      if(splitline.size() == 0) {
        continue;
      }

      //Ignore comments
      if(splitline[0][0] == '#') {
        continue;
      }

      //Valid commands:
      //size width height
      //  must be first command of file, controls image size
      else if(!splitline[0].compare("size")) {
        pixelwidth = atoi(splitline[1].c_str());
        pixelheight = atoi(splitline[2].c_str());
      }
      //maxdepth depth
      //  max # of bounces for ray (default 5)
      else if(!splitline[0].compare("maxdepth")) {
        maxdepth=atoi(splitline[1].c_str());
      }
      //output filename
      //  output file to write image to 
      else if(!splitline[0].compare("output")) {
        fname = splitline[1];
      }

      //camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov
      //  speciï¬es the camera in the standard way, as in homework 2.
      else if(!splitline[0].compare("camera")) {
        // lookfrom:
        //    atof(splitline[1].c_str())
        //    atof(splitline[2].c_str())
        //    atof(splitline[3].c_str())
        lookfrom = Point(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
        // lookat:
        //    atof(splitline[4].c_str())
        //    atof(splitline[5].c_str())
        //    atof(splitline[6].c_str())
        lookat = Point(atof(splitline[4].c_str()),atof(splitline[5].c_str()),atof(splitline[6].c_str()));
        // up:
        //    atof(splitline[7].c_str())
        //    atof(splitline[8].c_str())
        //    atof(splitline[9].c_str())
        up = Vector(atof(splitline[7].c_str()),atof(splitline[8].c_str()),atof(splitline[9].c_str()));
        // fov: atof(splitline[10].c_str());
        fov = atof(splitline[10].c_str());





      }

      //sphere x y z radius
      //  Deï¬nes a sphere with a given position and radius.
      else if(!splitline[0].compare("sphere")) {
        // x: atof(splitline[1].c_str())
        // y: atof(splitline[1].c_str())
        // z: atof(splitline[1].c_str())
        // r: atof(splitline[4].c_str())
        // Create new sphere:
        //   Store 4 numbers
        //   Store current property values
        //   Store current top of matrix stack

      	float rad = atof(splitline[4].c_str());
      	Point cen = Point(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
      	Matrix newtrans = Matrix();
      	newtrans = newtrans.identityMat();
      	BRDF newcol = BRDF(currKa,currKd,currKs,currKr,currEm,currSp);
        if(trans.size()!=0)
          newtrans = trans.back();
      	Sphere newS = Sphere(rad,cen,newtrans,newcol);
      	shapes.push_back(newS);
      	shapes.back().radius = rad;
        shapes.back().center = cen;

        //cout << shapes.back().radius << endl;

        //cout << shapes.back().center << endl;

        //shapes.back().c = vertices[atof(splitline[3].c_str())];
      	//cout <<"isihgirthjgstrhgiu" << endl;
      }
      //maxverts number
      //  Deï¬nes a maximum number of vertices for later triangle speciï¬cations. 
      //  It must be set before vertices are deï¬ned.
      else if(!splitline[0].compare("maxverts")) {
        // Care if you want
        // Here, either declare array size
        // Or you can just use a STL vector, in which case you can ignore this
      }
      //maxvertnorms number
      //  Deï¬nes a maximum number of vertices with normals for later speciï¬cations.
      //  It must be set before vertices with normals are deï¬ned.
      else if(!splitline[0].compare("maxvertnorms")) {
        // Care if you want
      }
      //vertex x y z
      //  Deï¬nes a vertex at the given location.
      //  The vertex is put into a pile, starting to be numbered at 0.
      else if(!splitline[0].compare("vertex")) {
        // x: atof(splitline[1].c_str()),
        // y: atof(splitline[2].c_str()),
        // z: atof(splitline[3].c_str()));
        // Create a new vertex with these 3 values, store in some array
        Point newP = Point(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
      	vertices.push_back(newP);
      }
      //vertexnormal x y z nx ny nz
      //  Similar to the above, but deï¬ne a surface normal with each vertex.
      //  The vertex and vertexnormal set of vertices are completely independent
      //  (as are maxverts and maxvertnorms).
      else if(!splitline[0].compare("vertexnormal")) {
        // x: atof(splitline[1].c_str()),
        // y: atof(splitline[2].c_str()),
        // z: atof(splitline[3].c_str()));
        // nx: atof(splitline[4].c_str()),
        // ny: atof(splitline[5].c_str()),
        // nz: atof(splitline[6].c_str()));
        // Create a new vertex+normal with these 6 values, store in some array
      }
      //tri v1 v2 v3
      //  Create a triangle out of the vertices involved (which have previously been speciï¬ed with
      //  the vertex command). The vertices are assumed to be speciï¬ed in counter-clockwise order. Your code
      //  should internally compute a face normal for this triangle.
      else if(!splitline[0].compare("tri")) {
        // v1: atof(splitline[1].c_str())
        // v2: atof(splitline[2].c_str())
        // v3: atof(splitline[3].c_str())
        // Create new triangle:
        //   Store pointer to array of vertices
        //   Store 3 integers to index into array
        //   Store current property values
        //   Store current top of matrix stack
        Point p1,p2,p3;
        p1 = vertices[atof(splitline[1].c_str())];
        p2 = vertices[atof(splitline[2].c_str())];
        p3 = vertices[atof(splitline[3].c_str())];

              	Matrix newtrans = Matrix();
      	newtrans = newtrans.identityMat();
      	BRDF newcol = BRDF(currKa,currKd,currKs,currKr,currEm,currSp);
        if(trans.size()!=0)
          newtrans = trans.back();
        Triangle newTri = Triangle(p1,p2,p3,newtrans,newcol);
       //cout<<newTri.a<<endl;
        shapes.push_back(newTri);
        shapes.back().a = vertices[atof(splitline[1].c_str())];
        shapes.back().b = vertices[atof(splitline[2].c_str())];
        shapes.back().c = vertices[atof(splitline[3].c_str())];
        
        /*cout << shapes[0].a<< endl;
        cout << shapes[0].b<< endl;
        cout << shapes[0].c<< endl;
        cout << shapes[0].brdf.ka<< endl;
        cout << shapes[0].brdf.kd<< endl;
        cout << shapes[0].brdf.ks<< endl;
        cout << shapes[0].brdf.kr<< endl;
        cout << shapes[0].brdf.em<< endl;
        cout << shapes[0].brdf.sp<< endl;
        cout << shapes[0].transform<<endl;
        */

        

      }
      //trinormal v1 v2 v3
      //  Same as above but for vertices speciï¬ed with normals.
      //  In this case, each vertex has an associated normal, 
      //  and when doing shading, you should interpolate the normals 
      //  for intermediate points on the triangle.
      else if(!splitline[0].compare("trinormal")) {
        // v1: atof(splitline[1].c_str())
        // v2: atof(splitline[2].c_str())
        // v3: atof(splitline[3].c_str())
        // Create new triangle:
        //   Store pointer to array of vertices (Different array than above)
        //   Store 3 integers to index into array
        //   Store current property values
        //   Store current top of matrix stack
      }

      //translate x y z
      //  A translation 3-vector
      else if(!splitline[0].compare("translate")) {
        // x: atof(splitline[1].c_str())
        // y: atof(splitline[2].c_str())
        // z: atof(splitline[3].c_str())
        // Update top of matrix stack
        cout << "translate" << endl;
        Matrix mat = Matrix();
        Matrix id = mat.identityMat();
        Matrix transMat = mat.transMat(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
        if(trans.size()==0)
          trans.push_back(transMat);
        else{
          Matrix prev = trans.back();
          trans.pop_back();
          trans.push_back(prev*transMat);
        }
        cout << "translate exit" << endl;
      }
      //rotate x y z angle
      //  Rotate by angle (in degrees) about the given axis as in OpenGL.
      else if(!splitline[0].compare("rotate")) {
        // x: atof(splitline[1].c_str())
        // y: atof(splitline[2].c_str())
        // z: atof(splitline[3].c_str())
        // angle: atof(splitline[4].c_str())
        // Update top of matrix stack
        cout << "rotate" << endl;
                Matrix mat = Matrix();
        Matrix transMat = mat.axisRotMat(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()),atof(splitline[4].c_str()));
        if(trans.size()==0)
          trans.push_back(transMat);
        else{
          Matrix prev = trans.back();
          trans.pop_back();
          trans.push_back(prev*transMat);
        }
        cout << "rotate exit" << endl;
      }
      //scale x y z
      //  Scale by the corresponding amount in each axis (a non-uniform scaling).
      else if(!splitline[0].compare("scale")) {
        // x: atof(splitline[1].c_str())
        // y: atof(splitline[2].c_str())
        // z: atof(splitline[3].c_str())
        // Update top of matrix stack
        cout << "scale" << endl;
                Matrix mat = Matrix();
        Matrix transMat = mat.scaleMat(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
        if(trans.size()==0)
          trans.push_back(transMat);
        else{
          Matrix prev = trans.back();
          trans.pop_back();
          trans.push_back(prev*transMat);
        }
        cout << "scale exit" << endl;
      }
      //pushTransform
      //  Push the current modeling transform on the stack as in OpenGL. 
      //  You might want to do pushTransform immediately after setting 
      //   the camera to preserve the â€œidentityâ€ transformation.
      else if(!splitline[0].compare("pushTransform")) {
        //mst.push();
        cout << "push transform" << endl;
        Matrix m = Matrix();
        if(trans.size()!=0)
          m = trans.back();
        else
          m = m.identityMat();
        trans.push_back(m);
        cout << "exit push transform" << endl;
      }
      //popTransform
      //  Pop the current transform from the stack as in OpenGL. 
      //  The sequence of popTransform and pushTransform can be used if 
      //  desired before every primitive to reset the transformation 
      //  (assuming the initial camera transformation is on the stack as 
      //  discussed above).
      else if(!splitline[0].compare("popTransform")) {
        //mst.pop();
        cout << "popTransform" << endl;
        trans.pop_back();
        cout << "popTransform exit" << endl;
      }

      //directional x y z r g b
      //  The direction to the light source, and the color, as in OpenGL.
      else if(!splitline[0].compare("directional")) {
        // x: atof(splitline[1].c_str()),
        // y: atof(splitline[2].c_str()),
        // z: atof(splitline[3].c_str()));
        // r: atof(splitline[4].c_str()),
        // g: atof(splitline[5].c_str()),
        // b: atof(splitline[6].c_str()));
        // add light to scene...
        Vector vec = Vector(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
      	Color lcol = Color(atof(splitline[4].c_str()),atof(splitline[5].c_str()),atof(splitline[6].c_str()));

      	Directionallight dl = Directionallight(vec,lcol);

      	lights.push_back(dl);

      }
      //point x y z r g b
      //  The location of a point source and the color, as in OpenGL.
      else if(!splitline[0].compare("point")) {
        // x: atof(splitline[1].c_str()),
        // y: atof(splitline[2].c_str()),
        // z: atof(splitline[3].c_str()));
        // r: atof(splitline[4].c_str()),
        // g: atof(splitline[5].c_str()),
        // b: atof(splitline[6].c_str()));
        // add light to scene...
        Point vec = Point(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
      	Color lcol = Color(atof(splitline[4].c_str()),atof(splitline[5].c_str()),atof(splitline[6].c_str()));

      	Pointlight dl = Pointlight(vec,lcol,attenuation);

      	lights.push_back(dl);
      }
      //attenuation const linear quadratic
      //  Sets the constant, linear and quadratic attenuations 
      //  (default 1,0,0) as in OpenGL.
      else if(!splitline[0].compare("attenuation")) {
        // const: atof(splitline[1].c_str())
        // linear: atof(splitline[2].c_str())
        // quadratic: atof(splitline[3].c_str())
        attenuation = Color(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
        
      }
      //ambient r g b
      //  The global ambient color to be added for each object 
      //  (default is .2,.2,.2)
      else if(!splitline[0].compare("ambient")) {
        // r: atof(splitline[1].c_str())
        // g: atof(splitline[2].c_str())
        // b: atof(splitline[3].c_str())
        currKa = Color(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
      }

      //diï¬€use r g b
      //  speciï¬es the diï¬€use color of the surface.
      else if(!splitline[0].compare("diffuse")) {
        // r: atof(splitline[1].c_str())
        // g: atof(splitline[2].c_str())
        // b: atof(splitline[3].c_str())
        // Update current properties
        currKd = Color(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));;
      }
      //specular r g b 
      //  speciï¬es the specular color of the surface.
      else if(!splitline[0].compare("specular")) {
        // r: atof(splitline[1].c_str())
        // g: atof(splitline[2].c_str())
        // b: atof(splitline[3].c_str())
        // Update current properties
        currKs = Color(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
      }
      //shininess s
      //  speciï¬es the shininess of the surface.
      else if(!splitline[0].compare("shininess")) {
        // shininess: atof(splitline[1].c_str())
        // Update current properties
        currSp = atof(splitline[1].c_str());
      }
      //emission r g b
      //  gives the emissive color of the surface.
      else if(!splitline[0].compare("emission")) {
        // r: atof(splitline[1].c_str())
        // g: atof(splitline[2].c_str())
        // b: atof(splitline[3].c_str())
        // Update current properties
        currEm = Color(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));;
      } else {
        std::cerr << "Unknown command: " << splitline[0] << std::endl;
      }
    }

    inpfile.close();
  }

}


int main(int args, char* argv[]){
	char* filename = argv[1];
	
	loadScene(filename);
	//exit(1);
	Camera camera = Camera(lookfrom,lookat,up,fov,pixelwidth,pixelheight);

	Raytracer raytracer = Raytracer();

	FreeImage_Initialise();

	FIBITMAP *bitmap = FreeImage_Allocate(pixelwidth,pixelheight,24);
	RGBQUAD color;

	if(!bitmap)
		exit(1);

	for(int x = 0; x < pixelwidth; x++){
		for(int y = 0; y < pixelheight; y++){
			//cout << "going in for loop??????" << endl;
			Ray ray = camera.generateRay(x,y);

			Color getColor = raytracer.trace(ray,maxdepth);
      if(getColor.r > 1 || getColor.g > 1 || getColor.b > 1){
          cout<< getColor << "     at:   " << x << ", " << y<<endl;
      }
      if(getColor.r > 1)
        getColor.r=1;
      if(getColor.g > 1)
        getColor.g=1;
      if(getColor.b > 1)
        getColor.b=1;
      //cout<< getColor <<endl;
			
      color.rgbRed = getColor.r*255;
			color.rgbGreen = getColor.g*255;
			color.rgbBlue = getColor.b*255;

			if(color.rgbRed > 255)
				color.rgbBlue = 255;

			if(color.rgbGreen > 255)
				color.rgbGreen = 255;

			if(color.rgbBlue > 255)
				color.rgbRed = 255;

			FreeImage_SetPixelColor(bitmap,x,y,&color);
		}
	}

	if(FreeImage_Save(FIF_PNG,bitmap,fname.c_str(),0))
		cout<<"Image saved."<<endl;

	FreeImage_DeInitialise();

	return 0;

}