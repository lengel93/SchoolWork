#include "DrawFunctions.h"

/**************************************************************************//**
* @author Sam Patzer
*
* @par Description:
* This function takes in the name of a category and its answer. It then goes 
* through the linked list looking for the node that contains a matching category
* and answer. Once the node is found it is removed and true is returned. If the
* node isn't found false is returned. 
*
* @param[in]      filename - the name of the file for loading BMP's
* @returns        void
*****************************************************************************/
Graphics::Graphics(std::string filename)
{
	loadBMP(filename, imgRows, imgCols, image);
}

/**************************************************************************//**
* @author Sam Patzer
*
* @par Description:
* Uses Glut to draw the graphics at the x and y spots on the gameboard
*
* @param[in]      x - the x coordinate on the grid
* @param[in]	  y - the y coordinate on the grid
* @returns	  void
*****************************************************************************/
void Graphics::drawGraphic(int x, int y)
{
	glRasterPos2i(x, y);
	glDrawPixels(imgCols, imgRows, GL_RGB, GL_UNSIGNED_BYTE, image);
}
