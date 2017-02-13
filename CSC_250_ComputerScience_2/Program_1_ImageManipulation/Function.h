#include <iostream> 
#include <fstream> 
#include <vector>

using namespace std;

#ifndef  __FUNCTION__H__ 
#define __FUNCTION__H__ 

typedef unsigned char pixel;

/*!
* @brief Holds information about a HAM radio user
*/
struct image
{
    int rows;/*!< Holds row size for the arrays */
    int cols;/*!< Holds columns for the arrays */
    double max;/*!< Holds max value for contrast function */
    double min;/*!< Holds min value for contrast function */
    pixel **redgray; /*!< The array that holds the red color values */
    pixel **green; /*!< The array that holds the green color values */
    pixel **blue; /*!< The array that holds the blue color values */
};

//checks command line arguments
bool cmdcheck(int argc, char *argv[]);

//deal with allocating and freeing arrays
void AllocateArray(pixel **&arr, image &img);

void allocateall(image &img);

void freearray(pixel **arr, image img);

void freeall(image &img,string magicnumber);


//gets the header information from files
void getimginfo(image &img, string &magicnumber, string &comment,
	string &maxpix, fstream &fin);

//deal with filling the arrays and outputting the information
void output(image &img, ofstream &fout, string &magicnumber);

void outinfo(image &img, string &magicnumber, string &comment,
	string &maxpix, ofstream &fout);

void outputbin(image &img, ofstream &fout, string &magicnumber);

void binaryfill(image &img, fstream &fin,string &magicnumber);

void fillarrays(image &img, fstream &fin, string &magicnumber);



// Deal with sorting out what to do with the file
void ifoa(image &img, string &magicnumber, string &comment,
	string &maxpix, string filetype, fstream &fin, int argc, char *argv[]);

void ifob(image &img, string &magicnumber, string &comment,
	string &maxpix, string filetype, fstream &fin, int argc, char *argv[]);

//Image manipulation functions
void brighten(image &img, string magicnumber, char *argv[]);

void negate(image &img, string magicnumber);

void sharpen(image &img, string magicnumber);

void grayscale(image &img, string magicnumber);

void contrast(image &img, string magicnumber);

void boundcheck(int &number);

void sharpencheck(pixel **&arr, image &img, pixel **&newarr, int i, int j);

void smooth(image &img, string magicnumber);

void smoothcheck(pixel **&arr, image &img, pixel **&newarr, int i, int j);

#endif 