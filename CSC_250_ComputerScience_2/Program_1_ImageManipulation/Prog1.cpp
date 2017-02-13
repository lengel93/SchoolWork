
/*************************************************************************//**
 * @file
 *
 * @mainpage Program 1 
 *
 * @section Section M002
 *
 * @author Lyndon Engel
 *
 * @date 10/9/2015
 *
 * @par Professor:
 *         Roger Schrader
 *
 * @par Course:
 *         CSC 250
 *
 * @par Location:
 *         McLaury -  Room 306
 *
 * @section program_section Program Information
 *
 * @details 
 * This program does image manipulation to .ppm and .pgm files depending on what is
 * specified in the command line. The options for image manipulation are negate 
 * which inverses the color of the image, brighten which can either increase or
 * decrease the brightness of the image, sharpen which enhances the detail of the
 * image, Smooth which makes the image blurry, grayscale which will turn a color
 * image black and white, and contrast which will contrast a grayscale image. 
 *
 * On top of the image manipulation the program can also read in binary text files
 * and normal text files depending on the image file you choose to have altered. 
 * After which you can choose to have that file put back into its original format 
 * whether that be binary or plan text. It can also change the image file from 
 * binary to normal text or vice versa.
 *
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 * In order for the program to run you must first declare what image manipulation
 * you want done to your image. If you want to brighten the image you must then 
 * enter the increment in which you would like to brighten the image ie 15 or -15.
 * Then choose whether you want the new to output in binary or ascii by using –oa 
 * for ascii or –ob for binary. After this you will then type in name you want for
 * the new file. Finally you will type in the image file you want manipulated. 
 *
 *       Option Code      Option Name 
 *          -n               Negate 
 *          -b #            Brighten 
 *          -p               Sharpen 
 *          -s               Smooth
 *          -g              Grayscale  
 *          -c              Contrast
 *
 *
 * @par Usage:
   @verbatim

    Function.cpp
	function.cpp(457): warning C4244: '=' : conversion from 'std::streamoff' to 'int', possible loss of data
	function.cpp(463): warning C4244: '=' : conversion from 'std::streamoff' to 'int', possible loss of data
	function.cpp(1225): warning C4244: '=' : conversion from 'double' to 'int', possible loss of data
	Program 1.vcxproj -> F:\prog1\Debug\prog1.exe

   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug 
 * - Grayscale and Contrast seem to come out a little lighter than test 
 *   samples 
 *
 * @todo none
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date           Modification
   -------------  -------------------------------------------------------------
   Sep  23, 2015  Started reading in info from ascii file and header file
   Sep  25, 2015  Started reading in info from binary file
   Sep	28, 2015  Output from binary to ascii
   Sep  30, 2015  Output from ascii to binary
   Oct  1,  2015  All output works
   Oct  3, 2015   Negate and Brighten functions
   Oct  5, 2015   Grayscale and Contrast functions
   Oct  6, 2015   Smooth Function
   Oct  7, 2015   Sharpen Function
   Oct  8, 2015   Doxygen

   @endverbatim
 *
 *****************************************************************************/
#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Main first checks the command line arguments to make sure all of them are correct.
* Once done with that it then extracts the magic number from the file to see whether
* it is binary or ascii. It then takes in file name that user would like to use for
* the output file. After all this is done main then checks for whether the user
* wants their new file to be in ascii or binary. Depending on which one they choose
* main will then run them through the designated if statement. Inside these if
* statements main checks whether the magic number needs to be changed and also what
* type of image manipulation the user wants done. It will then run them through the
* correct function and then output this information into the filetype of the users
* choice. 
*
* @param[in]      argc  - Size of the command line array
* @param[in]      argv  - Inputs command line array
* @returns        0 -     when done with program or error occurs 
*****************************************************************************/
int main(int argc, char *argv[])
{
    image img; 
	fstream fin;
	ofstream fout;
	string magicnumber,comment,maxpix,filename;
	string filetype;

	//checks the command line arguments
	if (cmdcheck(argc,argv) == false)
	{
		return 0;
	};

	fin.open(argv[argc - 1]);

	if (!fin)
	{
		cout << "File didn't open" << endl;
		return 0;
	}

	getline(fin, filetype);

	fin.close();

    filename = argv[argc - 2];

	/*  if the file is outtputted to ascii it runs through this if statement
	checking for what image manipulation was requested and then runs through
	the appropriate function.
	*/
	if (strcmp(argv[argc - 3], "-oa") == 0)
	{

		ifoa(img, magicnumber, comment, maxpix, filetype, fin, argc, argv);
			
		if (strcmp(argv[1], "-n") == 0)
		{
			negate(img, magicnumber);
		}
        if (strcmp(argv[1], "-b") == 0)
        {
            brighten(img, magicnumber, argv);
        }
		if (strcmp(argv[1], "-p") == 0)
		{
			sharpen(img, magicnumber);
		}
		if (strcmp(argv[1], "-s") == 0)
		{
			smooth(img, magicnumber);
		}
        if (strcmp(argv[1], "-g") == 0)
        {
            grayscale(img, magicnumber);
            magicnumber = "P2";
        }
        if (strcmp(argv[1], "-c") == 0)
        {
            contrast(img, magicnumber);
            magicnumber = "P2";
        }
		
        if (magicnumber == "P2")
        {
            filename.append(".pgm");
        }
        else
        {
            filename.append(".ppm");
        }

		fout.open(filename);

		if (!fout)
		{
			cout << "file didnt open" << endl;
			return 0;
		}

		outinfo(img, magicnumber, comment, maxpix, fout);

		output(img, fout, magicnumber);

		fout.close();
	}

	/*  if the file is outtputted to binary it runs through this if statement
		checking for what image manipulation was requested and then runs through
		the appropriate function.
	*/

	if (strcmp(argv[argc - 3], "-ob") == 0)
	{
		ifob(img, magicnumber, comment, maxpix, filetype, fin, argc, argv);
		
		if (strcmp(argv[1], "-n") == 0)
		{
			negate(img,magicnumber);
		}

        if (strcmp(argv[1], "-b") == 0)
        {
            brighten(img, magicnumber, argv);
        }

		if (strcmp(argv[1], "-p") == 0)
		{
			sharpen(img, magicnumber);
		}

		if (strcmp(argv[1], "-s") == 0)
		{
			smooth(img, magicnumber);
		}

        if (strcmp(argv[1], "-g") == 0)
        {
            grayscale(img, magicnumber);
            magicnumber = "P5";
        }

        if (strcmp(argv[1], "-c") == 0)
        {
            contrast(img, magicnumber);
            magicnumber = "P5";
        }

        if (magicnumber == "P5")
        {
            filename.append(".pgm");
        }

        else
        {
            filename.append(".ppm");
        }

		fout.open(filename,ios::binary);
		if (!fout)
		{
			cout << "file failed to open" << endl;
			return 0;
		}

		outinfo(img, magicnumber, comment, maxpix, fout);

		outputbin(img, fout, magicnumber);

		fout.close();
	}

	freeall(img,magicnumber);

    return 0;
}
