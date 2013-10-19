#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "point.h"
#include "vector.h"
#include "sphere.h"
#include "triangle.h"

#include "scene.h"
//#include ""
//#include ""

extern Point lookfrom, lookat;
extern Vector up;
extern int P_height,P_width;
extern float fov;
extern int maxdepth;



extern Raytracer raytracer;
extern Camera camera;
extern Sampler sampler;
extern Sample sample;
extern Ray ray;
extern Color color;



void Scene::loadScene(std::string file) {

  //store variables and set stuff at the end
  int width, height;
  std::string fname = "output.bmp";
  vector<Transformation> all_trans;
  vector<Point> list_vertices;

  Color currKA,currKD,currKS,currKR;
  currKA=currKD=currKS=currKR=Color();
  float currSP = 30.0f;

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
        width = atoi(splitline[1].c_str());
        height = atoi(splitline[2].c_str());
        P_height = height;
        P_width = width;
      }
      //maxdepth depth
      //  max # of bounces for ray (default 5)
      else if(!splitline[0].compare("maxdepth")) {
        maxdepth =atoi(splitline[1].c_str());
      }
      //output filename
      //  output file to write image to 
      else if(!splitline[0].compare("output")) {
        fname = splitline[1];
      }

      //camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov
      //  speciﬁes the camera in the standard way, as in homework 2.
      else if(!splitline[0].compare("camera")) {
        // lookfrom:
        //    atof(splitline[1].c_str())
        //    atof(splitline[2].c_str())
        //    atof(splitline[3].c_str())
        float lfx,lfy,lfz;
        lfx=atof(splitline[1].c_str());
        lfy=atof(splitline[2].c_str());
        lfz=atof(splitline[3].c_str());
        lookfrom = Point(lfx,lfy,lfz);
        // lookat:
        //    atof(splitline[4].c_str())
        //    atof(splitline[5].c_str())
        //    atof(splitline[6].c_str())
        float lax,lay,laz;
        lax=atof(splitline[4].c_str());
        lay=atof(splitline[5].c_str());
        laz=atof(splitline[6].c_str());
        lookat = Point(lax,lay,laz);
        // up:
        //    atof(splitline[7].c_str())
        //    atof(splitline[8].c_str())
        //    atof(splitline[9].c_str())
        float upx,upy,upz;
        upx=atof(splitline[7].c_str());
        upy=atof(splitline[8].c_str());
        upz=atof(splitline[9].c_str());
        up = Vector(upx,upy,upz);
        // fov: atof(splitline[10].c_str());
        fov = atof(splitline[10].c_str());
        color = Color();
        ray = Ray();
        camera = Camera();
        maxdepth = 1;
        raytracer = Raytracer(maxdepth,lookfrom);
        cout << "maxdepth" << maxdepth << endl;
        film = Film(P_width,P_height,24);
      }

      //sphere x y z radius
      //  Deﬁnes a sphere with a given position and radius.
      else if(!splitline[0].compare("sphere")) {
        // x: atof(splitline[1].c_str())
        // y: atof(splitline[1].c_str())
        // z: atof(splitline[1].c_str())
        // r: atof(splitline[4].c_str())
        // Create new sphere:
        //   Store 4 numbers
        //   Store current property values
        //   Store current top of matrix stack
        float sx,sy,sz,sr;
        sx=atof(splitline[1].c_str());
        sy=atof(splitline[2].c_str());
        sz=atof(splitline[3].c_str());
        sr=atof(splitline[4].c_str());
        BRDF tempBRDF = BRDF(currKA,currKD,currKS,currKR,currSP,0);

        Sphere* sphereTemp = new Sphere(sr,Point(sx,sy,sz),&tempBRDF,&all_trans);
        raytracer.prims.push_back(sphereTemp);
        //Sphere sphereTemp = Sphere(sr,Point(sx,sy,sz));

        //shapes.push_back(sphereTemp);
      }
      //maxverts number
      //  Deﬁnes a maximum number of vertices for later triangle speciﬁcations. 
      //  It must be set before vertices are deﬁned.
      else if(!splitline[0].compare("maxverts")) {
        // Care if you want
        // Here, either declare array size
        // Or you can just use a STL vector, in which case you can ignore this
      }
      //maxvertnorms number
      //  Deﬁnes a maximum number of vertices with normals for later speciﬁcations.
      //  It must be set before vertices with normals are deﬁned.
      else if(!splitline[0].compare("maxvertnorms")) {
        // Care if you want
      }
      //vertex x y z
      //  Deﬁnes a vertex at the given location.
      //  The vertex is put into a pile, starting to be numbered at 0.
      else if(!splitline[0].compare("vertex")) {
        // x: atof(splitline[1].c_str()),
        // y: atof(splitline[2].c_str()),
        // z: atof(splitline[3].c_str()));
        // Create a new vertex with these 3 values, store in some array
        Point vtemp = Point(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
        list_vertices.push_back(vtemp);
      }
      //vertexnormal x y z nx ny nz
      //  Similar to the above, but deﬁne a surface normal with each vertex.
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
      //  Create a triangle out of the vertices involved (which have previously been speciﬁed with
      //  the vertex command). The vertices are assumed to be speciﬁed in counter-clockwise order. Your code
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
        float p1,p2,p3;
        p1=atof(splitline[1].c_str());
        p2=atof(splitline[2].c_str());
        p3=atof(splitline[3].c_str());
        BRDF tempBRDF = BRDF(currKA,currKD,currKS,currKR,currSP,1);
        Triangle triTemp = Triangle(list_vertices[p1],list_vertices[p2],list_vertices[p3],&tempBRDF,&all_trans);

        raytracer.prims.push_back(&triTemp);
        //shapes.push_back(&triTemp);
      }
      //trinormal v1 v2 v3
      //  Same as above but for vertices speciﬁed with normals.
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
      }
      //rotate x y z angle
      //  Rotate by angle (in degrees) about the given axis as in OpenGL.
      else if(!splitline[0].compare("rotate")) {
        // x: atof(splitline[1].c_str())
        // y: atof(splitline[2].c_str())
        // z: atof(splitline[3].c_str())
        // angle: atof(splitline[4].c_str())
        // Update top of matrix stack
      }
      //scale x y z
      //  Scale by the corresponding amount in each axis (a non-uniform scaling).
      else if(!splitline[0].compare("scale")) {
        // x: atof(splitline[1].c_str())
        // y: atof(splitline[2].c_str())
        // z: atof(splitline[3].c_str())
        // Update top of matrix stack
      }
      //pushTransform
      //  Push the current modeling transform on the stack as in OpenGL. 
      //  You might want to do pushTransform immediately after setting 
      //   the camera to preserve the “identity” transformation.
      else if(!splitline[0].compare("pushTransform")) {
        //mst.push();
      }
      //popTransform
      //  Pop the current transform from the stack as in OpenGL. 
      //  The sequence of popTransform and pushTransform can be used if 
      //  desired before every primitive to reset the transformation 
      //  (assuming the initial camera transformation is on the stack as 
      //  discussed above).
      else if(!splitline[0].compare("popTransform")) {
        //mst.pop();
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
        float dx,dy,dz,dr,dg,db;
        dx=atof(splitline[1].c_str());
        dy=atof(splitline[2].c_str());
        dz=atof(splitline[3].c_str());
        dr=atof(splitline[4].c_str());
        dg=atof(splitline[5].c_str());
        db=atof(splitline[6].c_str());
        Vector tempdir = Vector(dx,dy,dz);
        Color tempcol = Color(dr,dg,db);
        Directionallight* lg = new Directionallight(tempdir,tempcol);
        raytracer.lights.push_back(lg);
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
        float dx,dy,dz,dr,dg,db;
        dx=atof(splitline[1].c_str());
        dy=atof(splitline[2].c_str());
        dz=atof(splitline[3].c_str());
        dr=atof(splitline[4].c_str());
        dg=atof(splitline[5].c_str());
        db=atof(splitline[6].c_str());
        Point tempdir = Point(dx,dy,dz);
        Color tempcol = Color(dr,dg,db);
        Pointlight* lg = new Pointlight(tempdir,tempcol);
        raytracer.lights.push_back(lg);
      }
      //attenuation const linear quadratic
      //  Sets the constant, linear and quadratic attenuations 
      //  (default 1,0,0) as in OpenGL.
      else if(!splitline[0].compare("attenuation")) {
        // const: atof(splitline[1].c_str())
        // linear: atof(splitline[2].c_str())
        // quadratic: atof(splitline[3].c_str())
      }
      //ambient r g b
      //  The global ambient color to be added for each object 
      //  (default is .2,.2,.2)
      else if(!splitline[0].compare("ambient")) {
        // r: atof(splitline[1].c_str())
        // g: atof(splitline[2].c_str())
        // b: atof(splitline[3].c_str())
        float ar,ag,ab;
        ar=atof(splitline[1].c_str());
        ag=atof(splitline[2].c_str());
        ab=atof(splitline[3].c_str());
        currKA = Color(ar,ag,ab);
      }

      //diﬀuse r g b
      //  speciﬁes the diﬀuse color of the surface.
      else if(!splitline[0].compare("diffuse")) {
        // r: atof(splitline[1].c_str())
        // g: atof(splitline[2].c_str())
        // b: atof(splitline[3].c_str())
        // Update current properties
        float ar,ag,ab;
        ar=atof(splitline[1].c_str());
        ag=atof(splitline[2].c_str());
        ab=atof(splitline[3].c_str());
        currKD = Color(ar,ag,ab);
      }
      //specular r g b 
      //  speciﬁes the specular color of the surface.
      else if(!splitline[0].compare("specular")) {
        // r: atof(splitline[1].c_str())
        // g: atof(splitline[2].c_str())
        // b: atof(splitline[3].c_str())
        // Update current properties
        float ar,ag,ab;
        ar=atof(splitline[1].c_str());
        ag=atof(splitline[2].c_str());
        ab=atof(splitline[3].c_str());
        currKS = Color(ar,ag,ab);
      }
      //shininess s
      //  speciﬁes the shininess of the surface.
      else if(!splitline[0].compare("shininess")) {
        // shininess: atof(splitline[1].c_str())
        // Update current properties
        currSP = atof(splitline[1].c_str());
      }
      //emission r g b
      //  gives the emissive color of the surface.
      else if(!splitline[0].compare("emission")) {
        // r: atof(splitline[1].c_str())
        // g: atof(splitline[2].c_str())
        // b: atof(splitline[3].c_str())
        // Update current properties
      } else {
        std::cerr << "Unknown command: " << splitline[0] << std::endl;
      }
    }

    inpfile.close();
  }

}

