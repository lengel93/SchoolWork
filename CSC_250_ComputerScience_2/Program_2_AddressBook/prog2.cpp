/*************************************************************************//**
 * @file 
 *
 * @mainpage Program 2 - Address Book
 * 
 * @section course_section Course Information 
 *
 * @author Engle, Lyndon
 * 
 * @date October 30, 2015
 * 
 * @par Professor: 
 *         Schrader, Roger
 * 
 * @par Course: 
 *         CSC 250 - Section M003 -  3:00 pm
 * 
 * @par Location: 
 *         McLaury - Room 306
 *
 * @section program_section Program Information 
 * 
 * @details This program builds a link list based off all the information from
 * the old address book. It stores the names and the file position in the binary
 * file so the user can retrieve the full record. It will then read in from a 
 * binary file that has records it then puts those records into a structure and 
 * create the link list. The link list will allow the user to add, display, edit,
 * search, and print all contacts.
 * 
 * The address book is a binary file of records one after the other, this allows
 * the entire record to be read in with one read statement. The program will run 
 * from the command line and will require two arguments; the executable, and the
 * binary file with records. If the user enters the wrong number of arguments the
 * program with show the user a usage statement.
 *
 * When the user picks the option to edit a contact a second menu will be presented.
 * The things the user can edit are: Name, Address, City, State, Zip code, Email, 
 * Mobile phone, Lan phone, and birthday. Also, when the user is done editing the 
 * contact they can choose to save the changes and write it to the file or revert
 * all the changes that they made. 
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      No special compiling
 * 
 * @par Usage: 
   @verbatim  
   c:\> prog2a.exe <filename>.bin
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * 
 * @todo debugging
 * @todo stl
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  -------------------------------------------------------------- 
   10/16         check command line options, read records and output names from 
                 binary file with the constructor.
  
   10/17         insert into linked list and print all the nodes in
                 the linked list, print function written, insert

   10/18         remove based on name or file position.
   10/20		 
   10/24         all functions written, not tested
   10/25         1st menu written, doxygen
   10/26         main and second menu done, doxygen
   10/27         doxygen, debugging main, cleaning up main.
   10/29         Started and finishing up part b STL
   10/30         Finish STL, final testing, doxygen. 

   @endverbatim

 *****************************************************************************/

#include "Linklist.h"

using namespace std;

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description:
 * This function reads in contact information from a binary file and creates a
 * linked list with each person’s name and position in the file. Users are able 
 * to add, view, edit, and search for contacts. After a contact is created or 
 * modified, the user then can choose to discard the contact changes or write 
 * them to the file.
 * 
 * @param[in]      argc - This is an integer that contains the number of 
 * arguements from the command line
 * @param[in]     argv - a description of variable two
 * 
 * @returns 0 program ran successful.
 * 
 *****************************************************************************/
int main(int argc, char * argv[])
{
    fstream fin;
    contact con;
    linklist list;
	string search;
    int pos = 0, maxpos = 0;
    int exit = 0;
    int mainchoice = 0;
	char temp[100] = {};

    //Checks the number of command line arguements
    if (argc != 2)
    {
        //outputs a usage statement if number is incorrect
        cout << "Program Usage: prog2.exe <input file>.bin" << endl; 
        return 0;
    }

    // attempts to open the file
    fin.open(argv[1], ios::in | ios::binary | ios::out | ios::ate);

    //checks if the file opened successfully
    if (!fin)
    {
        //if not, a message is displayed and the program exits
        cout << "Unable to open input file." << endl;
        return 0;
    }

    //seeks back to the beginning and begins reading the contact structures
	fin.seekg(0, ios::beg);

    while (fin.read((char*)&con, sizeof(contact)))
    {
        //checks if the contact was added successfully
        if (list.insert(con.name, pos) == false)
        {
            //if not a message displays and the program exits.
            cout << "Unable to insert new data.";
            fin.close();
            return 0;
        }
        //counter variable that keeps track of how many contacts were read in
        pos++;
    }
    
    maxpos = pos;
    
    fin.clear();

    while (exit == 0)
    {
        //calls the mainmenu function to output the number of contacts, and the menu
        mainmenu(maxpos);

        //gets the user's choice and puts it in a variable
        cout << "Choice: ";
        cin >> mainchoice;

        cout << endl;

        switch (mainchoice)
        {

        case 1:

            //choice 1 calls the addcontact function to create a new contact
            if (addcontact(fin, list, con, maxpos) == false)
            {
                break;
            }
  
            break;

        case 2:

            //choice 2 calls the display function to find and display the contact
			if (display(con, list, fin) == false)
			{
				break;
			}
            break;

        case 3:

            //choice 3 calls the editcon function to edit the chosen contact
			if (editcon(con, list, fin) == false)
			{
				break;
			}
            break;

        case 4:
            //choice 3 calls the consearch function to search for the input name
			if (consearch(list) == false)
			{
				break;
			}
            break;

        case 5:

            //choice 5 calls the linklist print member function to output all names
            list.print(cout);
            break;

        case 6:
            //choice 6 outputs a message then exits the loop and exits the program
            cout << "Exiting program." << endl;
            exit = 1;
            break;

        default:
            //The default outputs a message and returns to the beginning of the loop
            cout << "Invalid choice." << endl;
            break;

        }

    }
    fin.close();
    return 0;
}


