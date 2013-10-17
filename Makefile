CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Iglut-3.7.6-bin
	LDFLAGS = -lglut -lGL -lGLU
endif
	
RM = /bin/rm -f 
all: main 
main:  point.o vector.o normal.o ray.o sampler.o intersection.o directionallight.o pointlight.o material.o color.o geometricprimitive.o brdf.o localgeo.o sample.o matrix.o transformation.o sphere.o triangle.o camera.o testing.o
	$(CC) $(CFLAGS) -o as2 testing.o camera.o sampler.o intersection.o directionallight.o pointlight.o material.o geometricprimitive.o sphere.o triangle.o vector.o normal.o point.o ray.o color.o brdf.o localgeo.o sample.o matrix.o transformation.o $(LDFLAGS) 
vector.o: vector.cpp
	$(CC) $(CFLAGS) -c vector.cpp -o vector.o
normal.o: normal.cpp
	$(CC) $(CFLAGS) -c normal.cpp -o normal.o
point.o: point.cpp
	$(CC) $(CFLAGS) -c point.cpp -o point.o
ray.o: ray.cpp
	$(CC) $(CFLAGS) -c ray.cpp -o ray.o
color.o: color.cpp
	$(CC) $(CFLAGS) -c color.cpp -o color.o
brdf.o: brdf.cpp
	$(CC) $(CFLAGS) -c brdf.cpp -o brdf.o
localgeo.o: localgeo.cpp
	$(CC) $(CFLAGS) -c localgeo.cpp -o localgeo.o
sample.o: sample.cpp
	$(CC) $(CFLAGS) -c sample.cpp -o sample.o
matrix.o: matrix.cpp
	$(CC) $(CFLAGS) -c matrix.cpp -o matrix.o
material.o: material.cpp
	$(CC) -c $(CFLAGS) material.cpp -o material.o
transformation.o: transformation.cpp
	$(CC) $(CFLAGS) -c transformation.cpp -o transformation.o
sphere.o: sphere.cpp
	$(CC) $(CFLAGS) -c sphere.cpp -o sphere.o
triangle.o: triangle.cpp
	$(CC) $(CFLAGS) -c triangle.cpp -o triangle.o
intersection.o: intersection.cpp
	$(CC) $(CFLAGS) -c intersection.cpp -o intersection.o
geometricprimitive.o: geometricprimitive.cpp
	$(CC) -c $(CFLAGS) geometricprimitive.cpp -o geometricprimitive.o
pointlight.o: pointlight.cpp
	$(CC) $(CFLAGS) -c pointlight.cpp -o pointlight.o
directionallight.o: directionallight.cpp
	$(CC) $(CFLAGS) -c directionallight.cpp -o directionallight.o
sampler.o: sampler.cpp
	$(CC) $(CFLAGS) -c sampler.cpp -o sampler.o
#scene.o: scene.cpp
#	$(CC) $(CFLAGS) -c scene.cpp -o scene.o
camera.o: camera.cpp
	$(CC) -c $(CFLAGS) camera.cpp -o camera.o
testing.o: testing.cpp
	$(CC) -c $(CFLAGS) testing.cpp -o testing.o
clean: 
	$(RM) *.o as2
 


