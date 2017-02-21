# Makefile for Exam1
# Author: Lyndon Engel

###### Compiler #####
Link = g++

###### Object Files #####
OBJ_FILES = Shape3D.cpp Cube.cpp Rect.cpp Sphere.cpp gtests.cpp -I/home/classes/csc470/www/Resources/include -L/home/classes/csc470/www/Resources/lib -lgtestCentOS -lpthread


all: run_tests

run_tests: 
	 ${Link} -o run_tests $(OBJ_FILES)

clean: 
	rm -f *.o *~ run_tests

