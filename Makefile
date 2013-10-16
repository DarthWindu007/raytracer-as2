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
main:  point.o vector.o normal.o ray.o color.o brdf.o localgeo.o sample.o matrix.o transformation.o sphere.o triangle.o testing.o
	$(CC) $(CFLAGS) -o as2 testing.o sphere.o triangle.o vector.o normal.o point.o ray.o color.o brdf.o localgeo.o sample.o matrix.o transformation.o $(LDFLAGS) 
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
transformation.o: transformation.cpp
	$(CC) $(CFLAGS) -c transformation.cpp -o transformation.o
sphere.o: sphere.cpp
	$(CC) $(CFLAGS) -c sphere.cpp -o sphere.o
triangle.o: triangle.cpp
	$(CC) $(CFLAGS) -c triangle.cpp -o triangle.o
testing.o: testing.cpp
	$(CC) -c $(CFLAGS) testing.cpp -o testing.o
clean: 
	$(RM) *.o as2
 


