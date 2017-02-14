/**************************************************************************//**
* @file
*****************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#ifdef __APPLE__
  #include <GLUT/glut.h>
  #include <OpenGL/OpenGL.h>
#else
  #include <GL/glut.h>
#endif

#include "loadBMP.h"

/** @brief Graphics Class that contains the code to draw an image*/
class Graphics
{
private:
	unsigned char* image;
public:
	int imgRows; /*!< image's pixels in a row */
	int imgCols; /*!< image's pixels in a col */
	Graphics(std::string);
	~Graphics(){}
	void drawGraphic(int, int);
};