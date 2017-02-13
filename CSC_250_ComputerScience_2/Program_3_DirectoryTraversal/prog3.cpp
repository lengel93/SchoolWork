/*************************************************************************//**
* @file
*
* @mainpage Program 3
*
* @section Section M001
*
* @author Lyndon Engel
*
* @date 4/14/2015
*
* @par Professor:
*         Roger Schrader
*
* @par Course:
*         CSC 250
*
* @par Location:
*         Classroom Building, Room 204W
*
* @section program_section Program Information
*
* @details 
* This program will take in a user’s given directory and then traverse
* through it. First looking for other directories within the given directory
* and then looking for files with in those directories. Depending on what
* arguments the users inputs the program can output the directory and then the
* files in that directory with the user inputted ending, examples are
* *.cpp and *.*. If the user states they want the created date and modified
* date the program will then output those next to the files. This will all be
* outputted into an XML file. 
* 
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      In order for the program to compile you must enter between 3 to 5
* arguments on the command line. This is including "prog3.exe". The other
* valid arguments are -B (outputs both created and modified time),
* -C (outputs created time), -M(outputs modified time), the directory you
* to go through is also included in the command line, and the last valid 
* argument is the ending to the files you want outputted a few examples are 
* *.cpp,*.*, and *.h
* \n The following are some examples of vaild commandlines:
* Prog3.exe  Source  *.cpp \n
* Prog3.exe  SourceDirectory  p*.h \n
* Prog3.exe –M  –C Source  *.h* \n 
* Prog3.exe –C  –M  Source  *.cpp \n
* Prog3.exe –M project *.cpp \n
* Prog3.exe –C startups * \n
*
* @par Usage:
@verbatim
prog3.exe source file_ending
prog3.exe modify created source file_ending
prog3.exe modify/create source file_ending
@endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @bug Get a ctime warning and asked to replace with ctime_s. When I
* tried this the program stopped working altogether. From what I can
* tell ctime doesnt seem to effect the program and it works fine.
*
* @todo 
*
* @par Modifications and Development Timeline:
@verbatim
Date           Modification
-------------  -------------------------------------------------------------
Apr  1, 2015  Got program to start outputting directory names.
Apr  2, 2015  Program now out puts file names under directory.
Apr  4, 2015  Program can now output modified and created time.
Apr  5, 2015  Removed endl from ctime.
Apr  9, 2015  Started adding conditions for the program.
Apr  10, 2015 Doxygen
@endverbatim
*
*****************************************************************************/
#include <iostream>
#include <direct.h>
#include <io.h>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

void findfile(char dirpath[_MAX_PATH], char ending[_MAX_PATH], char created[3],
    char modified[3], int argc, ofstream &fout);

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Checks if the command line arguments meet the requirments before passing
* them into the function. 
*
*
* @param[in]      argc - How many arguments are in the command line.
* @param[in]      argv - Position of arguments.
*****************************************************************************/
int main(int argc, char *argv[])
{
    char *initial; //inital path
	char dirpath[_MAX_PATH] = { " " }; //directory path
	char ending[_MAX_PATH] = { " " }; //file ending 
	char created[3], modified[3]; //createdtime and modifiedtime
	ofstream fout;
    _finddata_t a_file;
    intptr_t dirpaths;

	fout.open("dir.xml");

	fout << "<?xml version= \"1.0\"?>" << endl;

	if (argc < 3 || argc > 5)
	{
		cout << "Invalid number of arguments entered." << endl;
		return 0;
	}
	if (argc == 3)
	{
		strcpy_s(dirpath,argv[1]);
		strcpy_s(ending, argv[2]);
	}
	if (argc == 4)
	{
		if (strcmp(argv[1], "-M") == 0)
		{
			strcpy_s(created, argv[1]);
			strcpy_s(dirpath, argv[2]);
			strcpy_s(ending, argv[3]);
		}
        else if (strcmp(argv[1], "-C") == 0)
        {
            strcpy_s(created, argv[1]);
            strcpy_s(dirpath, argv[2]);
            strcpy_s(ending, argv[3]);
        }
		else if (strcmp(argv[1], "-B") == 0)
		{
			strcpy_s(created, argv[1]);
			strcpy_s(dirpath, argv[2]);
			strcpy_s(ending, argv[3]);
		}
		else
		{
			cout << "Invalid option entered." << endl;
			return 0;
		}
	}
	if (argc == 5)
	{
        if (strcmp(argv[1], "-M") == 0 && strcmp(argv[2], "-C") == 0)
		{
			strcpy_s(created, argv[1]);
			strcpy_s(modified, argv[2]);
			strcpy_s(dirpath, argv[3]);
			strcpy_s(ending, argv[4]);
		}
        else if (strcmp(argv[1], "-C") == 0 && strcmp(argv[2], "-M") == 0)
		{
			strcpy_s(created, argv[1]);
			strcpy_s(modified, argv[2]);
			strcpy_s(dirpath, argv[3]);
			strcpy_s(ending, argv[4]);
		}
		else
		{
			cout << "Invalid option entered." << endl;
			return 0;
		}
	}

	//_chdir(dirpath);
    dirpaths = _findfirst(dirpath, &a_file);

	initial = _getcwd(NULL, 0); 

	fout << "<folder name=\"" << initial << "\">" << endl;
	
	if (_chdir(dirpath) == 0)
	{
		cout << "Program changed directories successfully" <<endl<<endl;
	}
	else
	{
		cout << "Unable to change to the directory " << dirpath << endl;
		return 0;
	}
		
	findfile(dirpath,ending,created,modified,argc,fout);

	fout.close();

	return 0;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function will take in a user’s given directory and then traverse
* through it. First looking for other directories within the given directory
* and then looking for files with in those directories. Depending on what 
* file ending the user specified in the argument statement the function will
* only out put those file types. This is also true for whether the user
* specified if they wanted the modify and create date. If not the function
* wont out put either. In the end the function should output the dirctory
* name and then the files within that dirctory under it. If specified it
* will include the created and modify date with the file name.
*
*
* @param[in]      dirpath - The directory path you want to look through.
* @param[in]      ending - The ending of the files you want to output.
* @param[in]      created - Do you want the created time.
* @param[in]      modified - Do you want the modified time.
* @param[in]      argc - Passes in argc so you know the number of arguments.
* @param[in]      &fout - Passes in the folder to fout too and also outputs to 
*                         that folder.
*****************************************************************************/
void findfile(char dirpath[_MAX_PATH], char ending[_MAX_PATH], char created[3],
	char modified[3], int argc,ofstream &fout)
{
	time_t createtime; //created time
	time_t modtime; //modified time
	string create; // created time without endl
	string mod; // modified time without endl
	char *path;
	_finddata_t a_file;     
	intptr_t  dir_handle;
	
	dir_handle = _findfirst("*.*", &a_file);   

	if (dir_handle == -1)
	{
		return;
	}
	do
	{
		if (strcmp(a_file.name, ".") != 0 && strcmp(a_file.name, "..") != 0)
		{
			if (a_file.attrib & _A_SUBDIR)
			{
				_chdir(a_file.name);

				path = _getcwd(NULL, 0);

				fout <<"<folder name=\""<< path << "\">"<<endl;

				findfile(dirpath, ending,created,modified,argc,fout);

				_chdir("..");
			}
		}

	} while (_findnext(dir_handle, &a_file) == 0);

	_findclose(dir_handle);

	dir_handle = _findfirst(ending, &a_file);

	do
	{
		modtime = a_file.time_write;
		mod = ctime(&modtime);
		mod.erase(mod.end() - 1);

		createtime = a_file.time_create;
		create = ctime(&createtime);
		create.erase(create.end() - 1);
		
		if (strcmp(a_file.name, ".") != 0 && strcmp(a_file.name, "..") != 0)
		{
			if (dir_handle == -1)
			{
				return;
			}
			if (a_file.attrib != _A_SUBDIR)
			{
				if (argc == 3)
				{
					fout << "<file name=\"" << a_file.name << "\"/>" << endl;
				}
				if (argc == 4)
				{
					if (strcmp(created, "-M") == 0)
					{
						fout << "<file name=\"" << a_file.name << "\"";
						fout << " DateModified=\"" << mod << "\"";
						fout << "/>" << endl;
					} 
					else if (strcmp(created, "-C") == 0)
					{
						fout << "<file name=\"" << a_file.name << "\"";
						fout << " DateCreated=\"" << create << "\"";
						fout << "/>" << endl;
					}
					else if (strcmp(created, "-B") == 0)
					{
						createtime = a_file.time_create;
						modtime = a_file.time_write;

						fout << "<file name=\"" << a_file.name << "\"";
						fout << " DateCreated=\"" << create << "\"";
						fout << " DateModified=\"" << mod << "\"";
						fout << "/>" << endl;
					}
				}
				if (argc == 5)
				{
					if (strcmp(created, "-M") == 0 && strcmp(modified, "-C") == 0)
					{
						fout << "<file name=\"" << a_file.name << "\"";
						fout << " DateModified=\"" << mod << "\"";
						fout << " DateCreated=\"" << create << "\"";
						fout << "/>" << endl;
					}
					else 
					{
					    fout << "<file name=\"" << a_file.name << "\"";
						fout << " DateCreated=\"" << create << "\"";
						fout << " DateModified=\"" << mod << "\"";
						fout << "/>" << endl;
					}
				}
			}
		}
	} while (_findnext(dir_handle, &a_file) == 0);

	fout << "</folder>" <<endl;

	_findclose(dir_handle);
}
 