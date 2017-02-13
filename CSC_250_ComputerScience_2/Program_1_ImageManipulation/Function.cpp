/*************************************************************************//**
* @file
*****************************************************************************/

#include "function.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function checks all the command line arguments making sure that they are
* vaild. Its makes sure that there werent too many entered and werent too little
* entered.
*
* @param[in]      argc  - Size of the command line array
* @param[in]      argv  - Inputs command line array
* @returns        true - if the function finds no errors in the command line.
* @returns        false - if the function finds an error in the command line.
*****************************************************************************/
bool cmdcheck(int argc, char *argv[])
{
	char * find;
	char * find2;
	int number;

	if (argc < 4)
	{
		cout << "Not enough commands were entered" << endl;
		return false;
	}
	else if (argc > 6)
	{
		cout << "Program failure, too many commands were entered." << endl;
		return false;
	}
	else if (argc == 4)
	{
		if (strcmp(argv[1], "-oa") == 0 || strcmp(argv[1], "-ob") == 0)
		{
			find = strchr(argv[2], '.');

			if (find == NULL)
			{
				find = strchr(argv[3], '.ppm');
				find2 = strchr(argv[3], '.pgm');

				if (find != NULL || find2 != NULL)
				{
					return true;
				}
				else
				{
					cout << "Invalid input file, please only use .ppm and .pgm files."<< endl;
					return false;
				}
			}
			else
			{
				cout << "Invalid output file name entered, dont include file extension" << endl;
				return false;
			}
		}
		else
		{
			cout << "Invalid output file type was entered, plese use -oa or -ob" << endl;
			return false;
		}
	}
	else if (argc == 5)
	{
		if (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "-p") == 0 ||

			strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "-g") == 0 ||

			strcmp(argv[1], "-c") == 0)
		{
			if (strcmp(argv[2], "-oa") == 0 || strcmp(argv[2], "-ob") == 0)
			{
				find = strchr(argv[3], '.');

				if (find == NULL)
				{
					find = strchr(argv[4], '.ppm');
					find2 = strchr(argv[4], '.pgm');

					if (find != NULL || find2 != NULL)
					{
						return true;
					}
					else
					{
						cout << "Invalid input file, please only use .ppm and .pgm files." << endl;
						return false;
					}
				}
				else
				{
					cout << "Invalid output file name entered,"<<
						" dont include file extension" << endl;
					return false;
				}
			}
			else
			{
				cout << "Invalid output file type was entered, plese use -oa or -ob" << endl;
				return false;
			}
		}
		else
		{
			cout << "Invalid function was entered, use -n, -b#, -p, -s, -g, -c" << endl;
			return false;
		}
	}
	else if (argc == 6)
	{
		number = strtol(argv[2], NULL, 10);

		if (strcmp(argv[1], "-b") == 0)
		{
			if (number != 0)
			{
				if (strcmp(argv[3], "-oa") == 0 || strcmp(argv[3], "-ob") == 0)
				{
					find = strchr(argv[4], '.');

					if (find == NULL)
					{
						find = strchr(argv[5], '.ppm');
						find2 = strchr(argv[5], '.pgm');

						if (find != NULL || find2 != NULL)
						{
							return true;
						}
						else
						{
							cout << "Invalid input file, please only use .ppm and .pgm files." << endl;
							return false;
						}
					}
					else
					{
						cout << "Invalid output file name entered,"<<
							" dont include file extension" << endl;
						return false;
					}
				}
				else
				{
					cout << "Invalid output file type was entered, plese use -oa or -ob" << endl;
					return false;
				}
			}
			else
			{
				cout << "Invalid specification, make sure after using -b "<< 
					" you enter a nonzero number" << endl;
				return false;
			}
		}
		else
		{
			cout << "Invalid function was entered, use  -b then a number" <<
				" otherwise use just -n, -p, -s, -g, -c" << endl;
			return false;
		}
	}
	return false;
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in a unsigned charcter and allocates it into a 2d array.
*
* @param[in,out]  arr  - The unsigned charcter you want allocated.
* @param[in]      img - reads int the rows and columns from the structure.
*****************************************************************************/
void AllocateArray(pixel **&arr, image &img)
{
	int i = 0;

	arr = new (nothrow) pixel*[img.rows];

	if (arr == nullptr)
	{
		cout << "array failed to allocate" << endl;

		abort();
	}

	for (i = 0; i < img.rows; ++i)
	{
		arr[i] = new (nothrow) pixel[img.cols];

		if (arr[i] == nullptr)
		{
			freearray(arr, img);

			cout << "array failed to allocate" << endl;

			abort();
		}
	}
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in the unsigned charcters from the structure and then passes
* them all through the allocate array function. As a result they all become 
* 2d arrays.
*
* @param[in,out]   img - reads in the unsigned charcters from the image structure
*                  and then allocates them into 2d arrays.
*****************************************************************************/
void allocateall(image &img)
{
	AllocateArray(img.redgray, img);
	AllocateArray(img.green, img);
	AllocateArray(img.blue, img);
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in a unsigned charcter array and frees it of its memory.
*
* @param[in,out]  arr - The unsgined charcter array you want freed. 
* @param[in]      img - reads int the rows and columns from the structure.
*****************************************************************************/
void freearray(pixel **arr, image img)
{
	int i = 0;

	for (i = 0; i < img.rows; ++i)
	{
		delete[] arr[i];
	}

	delete[]arr;
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in the unsigned charcter arrays from the structure and 
* then passes them all through the free array function. As a result they all their 
* memory is freed.
*
* @param[in,out]   img - reads in the unsigned charcter arrays and frees them.
* @param[in]       magicnumber - reads in the magic number to check if the image
*                                is grayscale or not.
*****************************************************************************/
void freeall(image &img,string magicnumber)
{
	if (magicnumber == "P2" || magicnumber == "P5")
	{
		freearray(img.redgray, img);
	}
	else
	{
		freearray(img.redgray, img);
		freearray(img.green, img);
		freearray(img.blue, img);
	}
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in the unsigned charcter arrays from the structure and 
* then passes them all through a double for loop to fill them with the information
* from the file that is designated by the user.
*
* @param[in,out]   img - reads in the unsigned charcter arrays so they can be 
*                        filled.
* @param[in]       magicnumber - reads in the magic number to check if the image
*                                is grayscale or not.
* @param[in]       fin - reads in the file with the data that will fill the arrays.
*****************************************************************************/
void fillarrays(image &img,fstream &fin,string &magicnumber)
{
	int numbers = 0;
	int i = 0, j = 0;

	if (magicnumber == "P2" || magicnumber == "P5")
	{
		AllocateArray(img.redgray, img);

		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				fin >> numbers;
				img.redgray[i][j] = (pixel)numbers;
			}
		}
	}
	else
	{
		allocateall(img);

		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				fin >> numbers;

				img.redgray[i][j] = numbers;

				fin >> numbers;
				img.green[i][j] = numbers;

				fin >> numbers;
				img.blue[i][j] = numbers;

			}
		}
	}
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in the open image file and extracts its header file. First
* it gets the magic number and then peeks in the file to see if there is a comment.
* If there is a comment it reads it in. It then gets the row size and column size 
* after that it grabs the max pixel size.
*
* @param[in]    img - reads in the row length and column length from the file.
* @param[out]    magicnumber - reads in the magic number from the file.
* @param[out]    comment - reads in the comment from the file.
* @param[out]    maxpix - reads in the max pixel size from the file.
* @param[in,out] fin - reads in the file with the data that will fill everything.
*****************************************************************************/
void getimginfo(image &img,string &magicnumber,string &comment,
	string &maxpix, fstream &fin)
{
	getline(fin, magicnumber);

	comment = fin.peek();

	if (comment == "#")
	{
		getline(fin, comment);
	}

	fin >> img.cols;
	fin >> img.rows;
	fin >> maxpix;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function inputs the record and the open file and then ouputs the filled 
* 2d arrays to the file.
*
* @param[in,out] img - reads in the record and outputs the arrays.
* @param[in]     magicnumber - reads in the magic number to see if its grayscale.
* @param[in,out] fout - outputs the arrays to the designated file
*****************************************************************************/
void output(image &img, ofstream &fout,string &magicnumber)
{
	int i = 0, j = 0;

	if (magicnumber == "P2" || magicnumber == "P5")
	{
		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				fout << (int)img.redgray[i][j] << "\n";
			}
		}
	}
	else
	{
		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{

				fout << (int)img.redgray[i][j] << "\n";

				fout << (int)img.green[i][j] << "\n";

				fout << (int)img.blue[i][j] << "\n";
			}
		}
	}
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function outputs the header information to the open file.
*
* @param[in]     img - reads in the row length and column length
* @param[in]     magicnumber - reads in the magic number
* @param[in]     comment - reads in the comment 
* @param[in]     maxpix - reads in the max pixel 
* @param[in,out] fout - reads in the file that all data will be stored in
*****************************************************************************/
void outinfo(image &img,string &magicnumber,string &comment,
	string &maxpix, ofstream &fout)
{
	fout << magicnumber << "\n";
	fout << comment << "\n";
	fout << img.cols << " " << img.rows << "\n";
	fout << maxpix << "\n";
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function reads in the open file and the unsigned charcter arrays from the 
* record. It then uses seekg find out what the size of the remaining file is. 
* From there it then reads in all the information into a vector where its is then
* outputed into the red, green, and blue arrays. 
*
* @param[in,out] img - reads in the record 
* @param[in]     magicnumber - reads in the magic number to see if its grayscale.
* @param[in,out] fin - reads in the open file
*****************************************************************************/
void binaryfill(image &img, fstream &fin, string &magicnumber)
{
	int i = 0, j = 0, h = 0;
	int current = 0, size = 0;
	vector<unsigned char> binaryarr;

	current = fin.tellg();

	current = current + 1;

	fin.seekg(fin.cur, fin.end);

	size = fin.tellg();

	fin.seekg(current);

	binaryarr.reserve(size);

	binaryarr.resize(size, 0);

	fin.read((char *)&binaryarr[0], size);

	if (magicnumber == "P2" || magicnumber == "P5")
	{
		AllocateArray(img.redgray, img);

		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++, h++)
			{
				img.redgray[i][j] = binaryarr[h];
			}
		}
	}
	else
	{
		allocateall(img);

		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				img.redgray[i][j] = binaryarr[h];
				h++;

				img.green[i][j] = binaryarr[h];
				h++;

				img.blue[i][j] = binaryarr[h];
				h++;
			}
		}
	}
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This Function outputs the arrays to the open file in binary.
*
* @param[in,out] img - reads in the record 
* @param[in]     magicnumber - reads in the magic number to see if its grayscale.
* @param[in,out] fout - reads in the open file
*****************************************************************************/
void outputbin(image &img, ofstream &fout, string &magicnumber)
{
	int i = 0, j = 0;

	if (magicnumber == "P2" || magicnumber == "P5")
	{
		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				fout.write(reinterpret_cast <const char*>
					(&img.redgray[i][j]), sizeof(img.redgray[i][j]));
			}
		}

	}
	else
	{
		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				fout.write(reinterpret_cast <const char*>
					(&img.redgray[i][j]), sizeof(img.redgray[i][j]));

				fout.write(reinterpret_cast <const char*>
					(&img.green[i][j]), sizeof(img.green[i][j]));

				fout.write(reinterpret_cast <const char*>
					(&img.blue[i][j]), sizeof(img.blue[i][j]));
			}
		}
	}
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function is used when the user wants the data to be outputed in ascii.
* The function will check what type of file was inputed by using the magic number.
* It will then open the file in the corrrect way and extract all the information 
* and fill the arrays. If the file was binary it will change its magic number
* depending on if it was grayscale or color.
*
* @param[in]     img - reads in the row length and column length from the file.
* @param[in]     magicnumber - reads in the magic number from the file.
* @param[in]     comment - reads in the comment from the file.
* @param[in]     maxpix - reads in the max pixel size from the file.
* @param[in]     filetype - reads in the magicnumber 
* @param[in,out] fin - reads in the file with the data that will fill everything.
* @param[in]	 argc - reads in Size of the command line array
* @param[in]	 argv - reads in command line array
*****************************************************************************/
void ifoa(image &img, string &magicnumber, string &comment,
	string &maxpix, string filetype, fstream &fin, int argc, char *argv[])
{
	if (filetype == "P3")
	{
		fin.open(argv[argc - 1]);

		if (!fin)
		{
			cout << "file failed to open" << endl;
			abort();
		}

		getimginfo(img, magicnumber, comment, maxpix, fin);

		fillarrays(img, fin, magicnumber);

		fin.close();
	}

	if (filetype == "P6")
	{
		fin.open(argv[argc - 1], ios::in | ios::out | ios::binary);

		if (!fin)
		{
			cout << "file failed to open" << endl;
			abort();
		}

		getimginfo(img, magicnumber, comment, maxpix, fin);

		magicnumber = "P3";

		binaryfill(img, fin, magicnumber);

		fin.close();
	}

	if (filetype == "P2")
	{
		fin.open(argv[argc - 1]);

		if (!fin)
		{
			cout << "file failed to open" << endl;
			abort();
		}

		getimginfo(img, magicnumber, comment, maxpix, fin);

		fillarrays(img, fin, magicnumber);

		fin.close();
	}

	if (filetype == "P5")
	{
		fin.open(argv[argc - 1], ios::in | ios::out | ios::binary);

		if (!fin)
		{
			cout << "file failed to open" << endl;
			abort();
		}

		getimginfo(img, magicnumber, comment, maxpix, fin);

		magicnumber = "P2";

		binaryfill(img, fin, magicnumber);

		fin.close();
	}
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function is used when the user wants the data to be outputed in binary.
* The function will check what type of file was inputed by using the magic number.
* It will then open the file in the corrrect way and extract all the information 
* and fill the arrays. If the file was ascii it will change its magic number
* depending on if it was grayscale or color.
*
* @param[in]     img - reads in the row length and column length from the file.
* @param[in]     magicnumber - reads in the magic number from the file.
* @param[in]     comment - reads in the comment from the file.
* @param[in]     maxpix - reads in the max pixel size from the file.
* @param[in]     filetype - reads in the magicnumber 
* @param[in,out] fin - reads in the file with the data that will fill everything.
* @param[in]	 argc - reads in Size of the command line array
* @param[in]	 argv - reads in command line array
*****************************************************************************/
void ifob(image &img, string &magicnumber, string &comment,
	string &maxpix, string filetype, fstream &fin, int argc, char *argv[])
{
	if (filetype == "P3")
	{
		fin.open(argv[argc - 1]);

		if (!fin)
		{
			cout << "file failed to open" << endl;
			abort();
		}

		getimginfo(img, magicnumber, comment, maxpix, fin);

		magicnumber = "P6";

		fillarrays(img, fin, magicnumber);

		fin.close();
	}

	if (filetype == "P6")
	{
		fin.open(argv[argc - 1], ios::in | ios::out | ios::binary);

		if (!fin)
		{
			cout << "file failed to open" << endl;
			abort();
		}

		getimginfo(img, magicnumber, comment, maxpix, fin);

		binaryfill(img, fin, magicnumber);

		fin.close();
	}

	if (filetype == "P2")
	{
		fin.open(argv[argc - 1]);

		if (!fin)
		{
			cout << "file failed to open" << endl;
			abort();
		}

		getimginfo(img, magicnumber, comment, maxpix, fin);

		magicnumber = "P5";

		fillarrays(img, fin, magicnumber);

		fin.close();
	}

	if (filetype == "P5")
	{
		fin.open(argv[argc - 1], ios::in | ios::out | ios::binary);

		if (!fin)
		{
			cout << "file failed to open" << endl;
			abort();
		}

		getimginfo(img, magicnumber, comment, maxpix, fin);

		binaryfill(img, fin, magicnumber);

		fin.close();
	}
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function negates the image file by subtracting the current number from 
* 255. It will then check to make sure that the new number is between 0 and 255.
*
* @param[in,out]   img - reads in record
* @param[in]       magicnumber - reads in the magic number to check if the image
*                                is grayscale or not.
*****************************************************************************/
void negate(image &img, string magicnumber)
{
    int numbers = 0;
    int i = 0, j = 0;

    if (magicnumber == "P2" || magicnumber == "P5")
    {
        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                numbers = (int)img.redgray[i][j];

                numbers = 255 - numbers;

				boundcheck(numbers);

                img.redgray[i][j] = (pixel)numbers;
            }
        }
    }
    else
    {
        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                numbers = (int)img.redgray[i][j];

                numbers = 255 - numbers;

				boundcheck(numbers);

                img.redgray[i][j] = (pixel)numbers;

                numbers = (int)img.green[i][j];

                numbers = 255 - numbers;

				boundcheck(numbers);

                img.green[i][j] = numbers;

                numbers = (int)img.blue[i][j];

                numbers = 255 - numbers;

				boundcheck(numbers);

                img.blue[i][j] = (pixel)numbers;
            }
        }
    }
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function controls the brightness of the image, by adding the the inputed
* value to the current value in the array. It will then check if the number is 
* within the bounds of 0 to 255.
*
* @param[in,out]   img - reads in record
* @param[in]       magicnumber - reads in the magic number to check if the image
*                                is grayscale or not.
* @param[in]       argv - reads in the argument line array.
*****************************************************************************/
void brighten(image &img, string magicnumber, char *argv[])
{
    int value = 0;
    int numbers = 0;
    int i = 0, j = 0;
	
	value = strtol(argv[2], NULL, 10);

    if (magicnumber == "P2" || magicnumber == "P5")
    {
        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                numbers = (int)img.redgray[i][j];

                numbers = numbers + value;

				boundcheck(numbers);

                img.redgray[i][j] = (pixel)numbers;
            }
        }
    }
    else
    {
        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                numbers = (int)img.redgray[i][j];

                numbers = numbers + value;

				boundcheck(numbers);

				img.redgray[i][j] = (pixel)numbers;

                numbers = (int)img.green[i][j];

                numbers = numbers + value;

				boundcheck(numbers);

				img.green[i][j] = (pixel)numbers;

                numbers = (int)img.blue[i][j];

                numbers = numbers + value;

				boundcheck(numbers);

				img.blue[i][j] = (pixel)numbers;
            }
        }
    }

}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function turns a color image into grayscale by multipling red byy .3, 
* green by .6, and blue by .1. It then adds these numbers up checks if they 
* fit inbetween the bound of 0 to 255 and the outputs them into a single array.
*
* @param[in,out]   img - reads in record
* @param[in]       magicnumber - reads in the magic number to check if the image
*                                is grayscale or not.
*****************************************************************************/
void grayscale(image &img, string magicnumber)
{
    int i = 0, j = 0, count = 0;
	double numbers;
    
    if (magicnumber == "P2" || magicnumber == "P5")
    {
        return;
    }
    else
    {
        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
				numbers = ((.3 * (double)img.redgray[i][j]) + 
					(.6 * (double)img.green[i][j]) + (.1 * (double)img.blue[i][j]));

				numbers = round(numbers);

                if (numbers < 0)
                {
                    numbers = 0;
                }
                if (numbers > 255)
                {
                    numbers = 255;
                }

                if ( count == 0)
                {
                    img.min = numbers;
                    img.max = numbers;
                    count++;
                }
                else
                {
                    if (numbers < img.min)
                    {
                        img.min = numbers;
                    }
                    if (numbers > img.max)
                    {
                        img.max = numbers;
                    }
                }

                img.redgray[i][j] = (pixel)numbers;
            }
        }
    }
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function contrast the image by first turning the image into grascale and 
* then finding the scale of the image. After which the image is then subtracted
* by its minimum value and divied by 255. 
*
* @param[in,out]   img - reads in record
* @param[in]       magicnumber - reads in the magic number to check if the image
*                                is grayscale or not.
*****************************************************************************/
void contrast(image &img, string magicnumber)
{
    int i = 0, j = 0;
    double scale = 0, numbers = 0;

    grayscale(img, magicnumber);

    scale = (255.0 / (img.max - img.min));

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
			numbers = (scale * ((double)img.redgray[i][j] - img.min));

            if (numbers < 0)
            {
                numbers = 0;
            }
            if (numbers > 255)
            {
                numbers = 255;
            }

            img.redgray[i][j] = (pixel)numbers;
        }
    }
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function checks that the given values in the arrays are within the 
* bounds of 0 and 255.
*
* @param[in]   number - inputs the number in the array 
*****************************************************************************/
void boundcheck(int &number)
{
	if (number < 0)
	{
		number = 0;
	}
	if (number > 255)
	{
		number = 255;
	}
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function allocates new arrays and the passes them to its sister function 
* that sharpens the image by multiplying the given position in the array by 5 
* and the subtracting that by the surrounding position in the array it then 
* outputs this number into a the new arrays. From there it passes these new 
* numbers into the old arrays and the dealocates the new ones. 
*
* @param[in,out]   img - reads in record
* @param[in]       magicnumber - reads in the magic number to check if the image
*                                is grayscale or not.
*****************************************************************************/
void sharpen(image &img, string magicnumber)
{
	int i = 0, j = 0;
	pixel **newred;
	pixel **newblue;
	pixel **newgreen;

	AllocateArray(newred, img);

	if (magicnumber == "P2" || magicnumber == "P5")
	{
		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				sharpencheck(img.redgray, img, newred, i, j);
			}
		}
		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				img.redgray[i][j] = newred[i][j];
			}
		}
	}
	else
	{
		AllocateArray(newblue, img);
		AllocateArray(newgreen, img);

		for (i = 0; i < img.rows - 1; i++)
		{
			for (j = 0; j < img.cols - 1; j++)
			{
				sharpencheck(img.redgray, img, newred, i, j);

				sharpencheck(img.green, img, newgreen, i, j);

				sharpencheck(img.blue, img, newblue, i, j);
			}
		}
		for (i = 0; i < img.rows - 1; i++)
		{
			for (j = 0; j < img.cols - 1; j++)
			{
				img.redgray[i][j] = newred[i][j];
				img.green[i][j] = newgreen[i][j];
				img.blue[i][j] = newblue[i][j];
			}
		}
		freearray(newblue, img);
		freearray(newgreen, img);
	}

	freearray(newred, img);
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in the old array and sharpens the image by multiplying the 
* number at the given position in the array by 5 and the subtracting that by the 
* surrounding position it then outputs this number into the new array.
*
* @param[in]   i - row position in array
* @param[in]   j - column position in array
* @param[in]   arr - the array that is being changed
* @param[in,out] newarr- the new array that is being filled
* @param[in]   img - reads in the row length and column length from the file.
*****************************************************************************/
void sharpencheck(pixel **&arr, image &img, pixel **&newarr, int i, int j)
{
    int temp;
	
	if ((j == 0 || i == 0) || (i == img.rows - 1 || j == img.cols - 1))
	{
		temp = (int)arr[i][j];

		boundcheck(temp);

		newarr[i][j] = (pixel)temp;
	}
	else
	{
		temp = 5 * (int)arr[i][j] - (int)arr[i - 1][j] - (int)arr[i][j - 1] - 
			(int)arr[i + 1][j] - (int)arr[i][j + 1];

		boundcheck(temp);

        newarr[i][j] = (pixel)temp;
	}
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function allocates new arrays and the passes them to its sister function 
* that smooths the image by adding the surrounding position of the array and then
* dividing them by 9 it then outputs this number into a the new arrays. From there
* it passes these new numbers into the old arrays and the dealocates the new ones. 
*
* @param[in,out]   img - reads in record
* @param[in]       magicnumber - reads in the magic number to check if the image
*                                is grayscale or not.
*****************************************************************************/
void smooth(image &img, string magicnumber)
{
	int i = 0, j = 0;
	pixel **newred;
	pixel **newblue;
	pixel **newgreen;

	AllocateArray(newred, img);

	if (magicnumber == "P2" || magicnumber == "P5")
	{
		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				smoothcheck(img.redgray, img, newred, i, j);
			}
		}
		for (i = 0; i < img.rows; i++)
		{
			for (j = 0; j < img.cols; j++)
			{
				img.redgray[i][j] = newred[i][j];
			}
		}
	}
	else
	{
		AllocateArray(newblue, img);
		AllocateArray(newgreen, img);

		for (i = 0; i < img.rows - 1; i++)
		{
			for (j = 0; j < img.cols - 1; j++)
			{
				smoothcheck(img.redgray, img, newred, i, j);

				smoothcheck(img.green, img, newgreen, i, j);

				smoothcheck(img.blue, img, newblue, i, j);
			}
		}
		for (i = 0; i < img.rows - 1; i++)
		{
			for (j = 0; j < img.cols - 1; j++)
			{
				img.redgray[i][j] = newred[i][j];

				img.green[i][j] = newgreen[i][j];

				img.blue[i][j] = newblue[i][j];
			}
		}

		freearray(newblue, img);
		freearray(newgreen, img);
	}

	freearray(newred, img);
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in the old array and smooths the image by adding the numbers
* surrounding the givin postion and then calculates the average of them. It then
* inputs this average into the new arrays.
*
* @param[in]   i - row position in array
* @param[in]   j - column position in array
* @param[in]   arr - the array that is being changed
* @param[in,out] newarr- the new array that is being filled
* @param[in]   img - reads in the row length and column length from the file.
*****************************************************************************/
void smoothcheck(pixel **&arr, image &img, pixel **&newarr, int i, int j)
{ 
	int temp;
	
	if ((j == 0 || i == 0) || (i == img.rows - 1 || j == img.cols - 1))
	{
		temp = (int)arr[i][j];

		boundcheck(temp);

		newarr[i][j] = (pixel)temp;
	}
	else
	{
		temp = round(((unsigned long)arr[i - 1][j - 1] +
            (unsigned long)arr[i - 1][j] + (unsigned long)arr[i - 1][j + 1] +
            (unsigned long)arr[i][j - 1] + (unsigned long)arr[i][j] +
            (unsigned long)arr[i][j + 1] + (unsigned long)arr[i + 1][j - 1] +
            (unsigned long)arr[i + 1][j] + (unsigned long)arr[i + 1][j + 1]) / 9.0);

		boundcheck(temp);

		newarr[i][j] = (pixel)temp;
	}
}



