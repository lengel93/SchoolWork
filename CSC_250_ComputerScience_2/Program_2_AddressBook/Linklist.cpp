#pragma pack(1) 
#include "LinkList.h"

using namespace std;

//Linklist functions
/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * Constructs the list
 *  
 *****************************************************************************/
linklist::linklist()
{ // constructor sets headptr to nullptr
    headptr = nullptr;
}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * Destructs the list
 * 
 *****************************************************************************/
linklist::~linklist()
{ //deconstructor
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in the name and file postion of a contact in the address
* book file. From there it then inserts the name into the linklist in alphebetical
* order. If the name is unable to be entered into the list the function returns 
* false, otherwise it returns true.
*
* @param[in]      name    - reads in name of contact
* @param[in,out]  filepos - reads in file postion of contact
*
* @returns        true    - if the new contact is inserted
* @returns        false   - if the function isn't able to insert the new contact
*
*****************************************************************************/
bool linklist::insert(string name, int filepos)
{
    node *temp = new(nothrow)node;
    node *prev;
    node *current;

    temp->name = name;
    temp->fileIndex = filepos;
    temp->next = nullptr;

    if (temp == nullptr)
    {
        return false;
    }

    if (filepos == 0)
    {
        headptr = nullptr;
    }

    if (headptr == nullptr)
    {
        headptr = temp;
        return true;
    }
    if (temp->name <= headptr->name)
    {
        temp->next = headptr;
        headptr = temp;
        return true;
    }

    current = headptr;
    prev = headptr;

    while (current != NULL && current->name <= temp->name)
    {
        prev = current;
        current = current->next;
    }

    prev->next = temp;
    temp->next = current;
    return true;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function reads in the file postion of a contact and then removes it from 
* the linklist. If the file is empty the function returns false, if the function
* cant find the file postion it also returns false. Otherwise it returns true.
*
* @param[in,out]  filepos - reads in file postion of contact
*
* @returns        true    - if the new contact is inserted
* @returns        false   - if the function isn't able to insert the new contact
*
*****************************************************************************/
bool linklist::remove(int filepos)
{
    node *temp = new(nothrow)node;
    node *current = new(nothrow)node;

    if (headptr == NULL)
    {
        return false;
    }

    if (headptr->fileIndex == filepos && headptr->next != NULL)
    {
        temp = headptr;
        headptr = headptr->next;
        temp = NULL;
        return true;
    }
    if (headptr->fileIndex == filepos && headptr->next == NULL)
    {
        headptr = NULL;
        return true;
    }

    temp = headptr;
    current = headptr;

    while (temp->next != NULL)
    {
        current = temp->next;

        if (temp->fileIndex == filepos)
        {
            temp = NULL;
            headptr = current;
            return true;
        }
        if (current->fileIndex == filepos)
        {
            temp->next = current->next;
            current = NULL;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function reads in the name of a contact and then removes it from 
* the linklist. If the file is empty the function returns false, if the function
* cant find the name it also returns false. Otherwise it returns true.
*
* @param[in,out]  name    - reads in name of contact
*
* @returns        true    - if the new contact is inserted
* @returns        false   - if the function isn't able to insert the new 
*
*****************************************************************************/
bool linklist::remove(string name)
{
    node *temp = new(nothrow)node;
    node *current = new(nothrow)node;

    if (headptr == NULL)
    {
        return false;
    }

    if (headptr->name == name && headptr->next != NULL)
    {
        temp = headptr;
        headptr = headptr->next;
        temp = NULL;
        return true;
    }
    if (headptr->name == name && headptr->next == NULL)
    {
        headptr = NULL;
        return true;
    }

    temp = headptr;
    current = headptr;

    while (temp->next != NULL)
    {
        current = temp->next;

        if (temp->name == name)
        {
            temp = NULL;
            headptr = current;
            return true;
        }
        if (current->name == name)
        {
            temp->next = current->next;
            current = NULL;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * Checks if the list is empty
 * 
 * @returns true	returns true if the list is empty
 * @returns false	returns false if the list has contacts
 * 
 *****************************************************************************/
bool linklist::is_empty()
{
    if (headptr == nullptr) // checks if the list is empty
    {
        return true; // returns true if empty
    }
    return false; //reutrns false if list has data
}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * The size function counts how many contacts are in the link list
 * 
 * @returns size	the function first checks if the list is empty and returns
 * 0 if it is, else the function loops through until it reaches the end of the list 
 * and returns the size when it is done.
 * 
 *****************************************************************************/
int linklist::size()
{
    int size = 0; // Size of the List
    node *temp; // Temp file to walk through the List
    temp = headptr; // Setting temp to beginning of list

    //Accounts for if list is empty
    if (temp == nullptr)
    {
        return size; //returns 0
    }

    // Walks through counting everything in the List
    for (size = 0; temp != nullptr; size++)
    {
        temp = temp->next;
    }

    // returns the size of the list
    return size;

}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * The find function does a partial compare with the name that the user gave 
 * to the name in the record. The name only has to have the part that the 
 * user gave.
 * 
 * @param[in]      name  -  A string that holds the name the user typed.
 * 
 * @returns true       -        When a match is found
 * @returns false      -        When list is empty or no match was found
 * 
 *****************************************************************************/
bool linklist::find(string name)
{
    node *temp; // temporary pointer
    temp = headptr; // set it to null
    int match = 0; // variable to set when name is found

    if (is_empty()) // check if empty
        return false;

    while (temp != nullptr) // loop till end of list
    {
        // checks if name in linklist contains the name the user gives
        if (temp->name.find(name) != string::npos)
        {
            cout << temp->name << endl; // print to screen
            match = 1; // set variable to return true
        }
        temp = temp->next; // increment pointer to next node

    }

    if (match == 1) // if name was found return true
        return true;
    else
        return false;

}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * The retrieve function searches through the file for an exact match of the 
 * name the user gave and returns the position where it was found
 * 
 * @param[in]      name - this variable holds the name the user typed in
 * 
 * @returns -1     returns a negative 1 if the list is empty or if it did not
 * find the name.
 * @returns temp->fileIndex  this returns where the name is found it is an integer
 * 
 *****************************************************************************/
int linklist::retrieve(string name)
{
    node *temp; // temporary pointer
    temp = headptr; // set it to headptr

    if (is_empty()) // check is list is empty
    {
        return -1;
    }

    while (temp != nullptr) // loop while not at the end of list
    {
        if (temp->name == name) // check if names match
        {
            return temp->fileIndex; // if they do return file postion
        }
        temp = temp->next; // if not increment temp pointer
    }

    return -1;
}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * The print function outputs all the contacts to the screen
 * 
 * @param[in]      &out - the ostream so the function and output all the contacts
 * to the screen
 * 
 * @returns none   returns nothing
 * 
 *****************************************************************************/
void linklist::print(ostream &out)
{
    node *temp;

    temp = headptr;

    while (temp != nullptr)
    {
        cout << temp->name << endl;
        temp = temp->next;

    }

}


//menu
/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * This function handles printing the number of contacts in the file and the main 
 * menu options each time the loop is executed.
 * 
 * @param[in]      size - this variable is the number of contacts that are in the 
 * linked list
 *
 * 
 *****************************************************************************/
void mainmenu(int size)
{
    //printing the main menu options
    cout << endl << "Number of Records: " << size << endl;
    cout << "  1) Add a Contact" << endl;
    cout << "  2) Display a contact" << endl;
    cout << "  3) Edit a contact" << endl;
    cout << "  4) Search for contacts" << endl;
    cout << "  5) Print all Contacts" << endl;
    cout << "  6) Exit the Program" << endl;
}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * This function prints out the menu to edit a contact, and handles the input 
 * given to choose which part of the contact the user wants to edit. After the 
 * user is finished they have the option to discard the changes, or to save them.
 * 
 * @param[in]  person - this is a contact structure that either contains the 
 * contact to be edited
 * 
 * @returns 0 the user chose to discard changes to the contact
 * @returns 1 the user chose to save the contact changes 
 * 
 *****************************************************************************/
int editmenu(contact  &person)
{
    char choice;
    char state[5];
    int month = 10;
    int day = 10;
    int year = 2015;
    int loop = 0;
    int start = 0;
    int end;
    int place;
    int zip;
	int namecheck = 0;
    bool check = false;
    string temp;
    string birthdate;

    //calls the extract date function to extract the birthdate to 3 separate ints
    extractdate(person.birthdate, month, day, year);

    while (loop == 0)
    {
		if (namecheck == 0)
		{
            //outputs the contact to be edited
			cout << "Name:               " << person.name << endl;
			cout << "Address:            " << person.address << endl;
            cout << "City, State, Zip:   " << person.city << ", "; 
            cout << person.state << " " << person.zipcode << endl;
			cout << "email:              " << person.email << endl;
			cout << "Mobile Phone:       " << person.mobilePhone << endl;
			cout << "Lan Phone:          " << person.lanPhone << endl;
            cout << "Birthdate:          " << month << '/' << day << '/';
            cout << year << endl << endl << endl;

            //outputs the options that the user can choose
			cout << "(N)ame" << endl;
			cout << "(A)ddress" << endl;
			cout << "(C)ity, (S)tate (Z)ip code" << endl;
			cout << "(E)mail" << endl;
			cout << "(M)obile Phone" << endl;
			cout << "(L)an Phone" << endl;
			cout << "(B)irthday" << endl << endl;
			cout << "(W)rite Write changes and return to the main menu" << endl;
			cout << "(R)evert Return to main menu" << endl;
			cout << "Choice: ";

            if (cin.fail()) 
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }

            //gets the user's choice and assigns it to a variable
			cin >> choice;
			choice = tolower(choice);
		}
		else
		{
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
			choice = 'n';
			loop = 1;
		}

        switch (choice)
        {
        case 'n':
            cin.ignore(1);

            //gets the new name for the contact from the console and stores it
            cout << "Enter Name: ";
            cin.getline(person.name, 50);
            cout << endl << endl;
            break;

        case 'a':
            cin.ignore(1);

            //gets the new address from the console and stores it
            cout << "Enter Address: ";
            cin.getline(person.address, 50);
            cout << endl << endl;
            break;

        case 'c':
            cin.ignore(1);

            //gets the new city from the console and stores it
            cout << "Enter City: ";
            cin.getline(person.city, 35);
            cout << endl << endl;
            break;

        case 's':
            cin.ignore(1);

            //gets the new state from the console and stores it in a char array
            cout << "Enter state: ";
            cin.getline(state, 5);

            //checks if the state abbrev is valid
			while (checkstate(state) == false)
            {
                cout << "Invalid state." << endl;
				cout << "Enter state: ";
                if (cin.fail()) 
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                }
                cin.getline(state, 5);
            }

            //copies the state from the character array to the contact
            strcpy(person.state, state);
			cout << endl << endl;
            break;

        case 'z':
            cin.ignore(1);

            //gets the new zipcode from the console
            cout << "Enter zipcode: ";
            cin >> zip;

            //checks if the zipcode is in the accepted range
            while (zip < 10000 || zip > 99999)
            {
                cout << "Invalid Zip Code" << endl;
                cout << "Enter zipcode: ";
                if (cin.fail()) 
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                }
                cin >> zip;
            }

            //stores the valid zipcode to the contact
            person.zipcode = zip;
			cout << endl << endl;
            break;

        case 'e':
            cin.ignore(1);

            //gets the new email from the console and stores it the contact
            cout << "Enter email: ";
            cin.getline(person.email, 50);
            cout << endl << endl;
            break;

        case 'm':
            cin.ignore(1);

            //gets the new mobile phone number from the console and stores it
            cout << "Enter Mobile phone: ";
            cin.getline(person.mobilePhone, 16);
            cout << endl << endl;
            break;

        case 'l':
            cin.ignore(1);

            //gets the new lan phone number from the console and stores it
            cout << "Enter LAN Phone: ";
            cin.getline(person.lanPhone, 16);
            cout << endl << endl;
            break;

        case 'b':
            cin.ignore(1);

            //gets the birthdate from the user and stores it in a string
            cout << "Enter Birthdate (MM/DD/YYYY): ";
            cin >> birthdate;

            //extracts the month value to an integer
            start = 0;
            place = birthdate.find_first_of('/');
            end = place - start;
            temp = birthdate.substr(start, end);
            month = stoi(temp);

            //extracts the day value to an integet
            start = place + 1;
            place = birthdate.find_first_of('/', start);
            end = place - start;
            temp = birthdate.substr(start, end);
            day = stoi(temp);
            
            //extracts the year value to an integer
            start = place + 1;
            place = birthdate.length();
            end = place - start;
            temp = birthdate.substr(start, end);
            year = stoi(temp);

            //takes the date value and verifies that it represents a valid date
			while (checkDate(month, day, year) == false)
            {
                cout << "Invalid Date." << endl;
				cout << "Enter Birthdate (MM/DD/YYYY): ";
                if (cin.fail()) 
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                }
				cin >> birthdate;

                //if not the user must enter a new date
				start = 0;
				place = birthdate.find_first_of('/');
				end = place - start;
				temp = birthdate.substr(start, end);
				month = stoi(temp);

				start = place + 1;
				place = birthdate.find_first_of('/', start);
				end = place - start;
				temp = birthdate.substr(start, end);
				day = stoi(temp);

				start = place + 1;
				place = birthdate.length();
				end = place - start;
				temp = birthdate.substr(start, end);
				year = stoi(temp);
            }

            //compresses the month, day, and year value into an integer and saves it
            person.birthdate = compressdate(month, day, year);
			cout << endl << endl;

            break;

        case 'w':

            //checks if the name is valid and then exits the loop
			if(strcmp(person.name,"Lastname, Firstname") == 0)
			{
				cout << "You must enter a new name." << endl;
				namecheck = 1;
				break;
			}
            loop = 1;
            break;

        case 'r':
            //exits the loop and returns 0 to not save the contact changes
            return 0;
            break;

        default:
            //if the choice is invalid, a message is displayed and it returns
            cout << "Invalid choice." << endl;
            break;
        }
    }
    return 1;
}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * This function simply initializes a contact with the default data, which is used 
 * in creating a new contact.
 * 
 * @param[in,out]       con - contact to be initialized with the default information
 * 
 * 
 *****************************************************************************/
void createdef(contact &con)
{
    //default contact values
    string defname = "Lastname, Firstname";
    string defadd = "501 E St Joseph";
    string defcity = "Rapid City";
    string defstate = "SD";
    string defemail = "Firstname.Lastname@gmail.com";
    string defphone = "(000) 000-0000";

    //initializes the cstrings in the contact with the default data
    strcpy(con.name, defname.c_str());
    strcpy(con.address, defadd.c_str());
    strcpy(con.city, defcity.c_str());
    strcpy(con.state, defstate.c_str());
    con.zipcode = 57701;
    strcpy(con.email, defemail.c_str());
    strcpy(con.mobilePhone, defphone.c_str());
    strcpy(con.lanPhone, defphone.c_str());
    con.birthdate = 2064010;
}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * This function takes an integer that contains the month, day and year and 
 * extracts them to three separate integers, named month, day, and year.
 * 
 * @param[in]         birthdate - integer containing the month, day and year
 * @param[in,out]     month - integer containing the extracted month value
 * @param[in,out]     day - integer containing the extracted day value
 * @param[in,out]     year - integer containing the extracted year value
 * 
 * 
 *****************************************************************************/
void extractdate(int birthdate, int &month, int &day, int &year)
{
	int temp;

    //sets the date integer to a temp variable
	temp = birthdate;

    //extracts the first 6 bits
	day = temp & 63;

    //shifts right 6 bits
	temp = temp >> 6;

    //extracts the next 4 bits
	month = temp & 15;

    //shifts right 4 bits
	temp = temp >> 4;

    //extracts the next 12 bits
	year = temp & 4095;
}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * This function takes the date in three separate integers, month, day, and year. 
 * It then uses the bitwise or to place them inside a single integer.
 * 
 * @param[in]     month - the month input by the user
 * @param[in]     day - the day input by the user
 * @param[in]     year - the year input by the user
 * 
 * @returns       No returns
 * 
 *****************************************************************************/
int compressdate(int month, int day, int year)
{
	int birthdate;

    //integer to hold the date
	birthdate = 0;

    //sets the first 12 bits
	birthdate = birthdate | year;

    //shifts left 4 bits
	birthdate = birthdate << 4;

    //sets the next 4 bits
	birthdate = birthdate | month;

    //shifts left 6 bits
	birthdate = birthdate << 6;

    //sets the last 6 bits and returns the final resulting integer
	birthdate = birthdate | day;

	return birthdate;

}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * This function takes the date in three separate integers, month, day, and year. 
 * It then checks to see if the day specified is within the range of the specified 
 * month.
 * 
 * @param[in]     month - the month input by the user
 * @param[in]     day - the day input by the user
 * @param[in]     year - the year input by the user
 * 
 * @returns true  the date was correct
 * @returns false the date was invalid 
 * 
 *****************************************************************************/
bool checkDate(int month, int day, int year)
{
    //checks the if the year is in the accepted range
	if ((year < 1900) || (year > 2016))
	{

		return false;
	}

    //checks if the month value is in the accepted range
	if ((month < 1) || (month > 12))
	{
		return false;
	}

	if (year == 2016)
	{
		if (day > 1 || month > 1)
		{
			return false;
		}

		return true;
	}

    //checks the month value to see if the day is valid for the corresponding month
	if (month == 2)
	{
		if (day > 29)
		{
			return false;
		}
	}
	
	if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
	{
		if (day > 30)
		{
			return false;
		}
		return true;
	}

	else
	{
		if (day > 31)
		{
			return false;
		}
		return true;
	}
}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * This function takes in a string that contains the state entered by the user, and 
 * verifies that the state entered is a valid state abbreviation..
 * 
 * @param[in]     state - an array of characters which contains the state
 * 
 * @returns true  the state was correct
 * @returns false the state was invalid 
 * 
 *****************************************************************************/
bool checkstate(char state[])
{ 
	int i = 0, j = 0;
	int count = 0;

    //initializes a character array with all the valid state abbreviations
	char allstates[50][3] = {
		{ 'A', 'L' }, { 'A', 'K' }, { 'A', 'Z' }, { 'A', 'R' }, { 'C', 'A' },
		{ 'C', 'O' }, { 'C', 'T' }, { 'D', 'E' }, { 'F', 'L' }, { 'G', 'A' },
		{ 'H', 'I' }, { 'I', 'D' }, { 'I', 'L' }, { 'I', 'N' }, { 'I', 'A' },
		{ 'K', 'S' }, { 'K', 'Y' }, { 'L', 'A' }, { 'M', 'E' }, { 'M', 'D' },
		{ 'M', 'A' }, { 'M', 'I' }, { 'M', 'N' }, { 'M', 'S' }, { 'M', 'O' },
		{ 'M', 'T' }, { 'N', 'E' }, { 'N', 'V' }, { 'N', 'H' }, { 'N', 'J' },
		{ 'N', 'M' }, { 'N', 'Y' }, { 'N', 'C' }, { 'N', 'D' }, { 'O', 'H' },
		{ 'O', 'K' }, { 'O', 'R' }, { 'P', 'A' }, { 'R', 'I' }, { 'S', 'C' },
		{ 'S', 'D' }, { 'T', 'N' }, { 'T', 'X' }, { 'U', 'T' }, { 'V', 'T' },
		{ 'V', 'A' }, { 'W', 'A' }, { 'W', 'V' }, { 'W', 'I' }, { 'W', 'Y' } };

    //if the state abbrev is longer than 2 characters it is invalid
	if (strlen(state) > 2)
	{
		return false;
	}


	state[0] = toupper(state[0]);
	state[1] = toupper(state[1]);

    //goes through the allstates array, checking if the state is valid
	for (i = 0; i < 50; i++)
	{
		for (j = 0; j < 2; j++)
		{
			if (allstates[i][j] == state[j])
			{
				count++;
			}
			if (count == 2)
			{
				return true;
			}
		}
		count = 0;
	}
	return false;
}




//Mainmenu functions
/**************************************************************************//**
* @author Lyndon Engel, Lyndon Engel
*
* @par Description:
* This function creates a defult contact using the createdef function, and 
* then runs the edit menu to create a new contact. Once the user is done in 
* the edit menu the program then comes back to this function and inputs the 
* the new name and file position into the linklist. If its unable to do this
* the function returns false otherwise it then outputs this new contact into 
* the addressbook file and returns true.
*
* @param[in]      fin     - reads in input file
* @param[in,out]  list    - reads in linklist class and outputs using insert.
* @param[in,out]  con     - reads in contact struct and outputs to struct
* @param[in,out]  maxpos  - reads in the max postion in the file
*
* @returns        true    - if the function is able to insert the new contact.
* @returns        false   - if the function isn't able to insert the new contact
*
*****************************************************************************/
bool addcontact(fstream &fin, linklist list, contact con, int &maxpos)
{
	createdef(con);

	if (editmenu(con) == 1)
	{
		if (list.insert(con.name, maxpos) == false)
		{
			cout << "Unable to insert new data.";
			return false;
		}
		fin.seekp(maxpos * 230, ios::beg);
		fin.clear();
		fin.write((char *)&con, sizeof(contact));
		fin.clear();
		maxpos++;
	}
	return true;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in the users inputed name and the searches for it in the 
* the linklist using the retrieve function. If the name isn't found the function
* the function returns false. Otherwise the function then takes the file position
* given by the retrieve function and goes to that contact in the addressbook file.
* once it reaches the contact it then inputs it into the contact struct and outputs
* the struct to the screen.
*
* @param[in]      fin     - reads in input file
* @param[in,out]  list    - reads in linklist class and outputs using insert.
* @param[in,out]  con     - reads in contact struct and outputs to struct
*
* @returns        true    - if the function is able to insert the new contact.
* @returns        false   - if the function isn't able to insert the new contact.
*
*****************************************************************************/
bool display(contact con, linklist list, fstream &fin)
{
	string search;
	char temp[100];
	int pos = 1;
	int month = 10, day = 10, year = 2015;

	cin.ignore(1);

    //gets the new name from the console
	cout << "Enter Name: ";
	cin.getline(temp, 100);

	cout << endl;

	search = temp;

    //calls the linklist retrieve function to check if the name is in the file
	pos = list.retrieve(search);

    //if not a message is displayed and false is returned
	if (pos <= -1)
	{
		cout << "Unable to find person." << endl;
		return false;
	}

    //if it is found the contact is read from the file
	pos = pos * 230;
	fin.seekg(pos, ios::beg);
	fin.read((char*)&con, sizeof(contact));
	fin.clear();

    //the birthdate is extracted
	extractdate(con.birthdate, month, day, year);

    //the contact info is displayed
	cout << "Name:               " << con.name << endl;
	cout << "Address:            " << con.address << endl;
    cout << "City, State, Zip:   " << con.city << ", ";  
    cout << con.state << " " << con.zipcode << endl;
	cout << "email:              " << con.email << endl;
	cout << "Mobile Phone:       " << con.mobilePhone << endl;
	cout << "Lan Phone:          " << con.lanPhone << endl;
    cout << "Birthdate:          " << month << '/' << day << '/'; 
    cout << year << endl << endl;

	return true;
}

/**************************************************************************//**
* @author Lyndon Engel, Lyndon Engel
*
* @par Description:
* This function combines the capabilities of the addcontact function and the 
* display function. In which it asks the user for a name and then locates it
* in the linklist with the retrieve function. If its not found it returns false.
* Other wise it will then extract the contact from the file and input into the 
* contact struct. From there it will output the contact and then the edit menu. 
* Once the user is done in the edit menu the program then outputs this newly edited
* contact back into it original space in the address book file. If the name was
* changed for the contact it is also replaced in the linklist aswell.
*
* @param[in]      fin     - reads in input file
* @param[in,out]  list    - reads in linklist class and outputs using insert
* @param[in,out]  con     - reads in contact struct and outputs to struct
*
* @returns        true    - if the function is able to insert the new contact
* @returns        false   - if the function isn't able to insert the new contact
*
*****************************************************************************/
bool editcon(contact con, linklist list, fstream &fin)
{
	string search;
	char temp[100];
	int pos = 1;

	cin.ignore(1);

    //gets the contact name to be edited from the console and stores it
	cout << "Enter Name: ";
	cin.getline(temp, 100);
	search = temp;

    //checks if the name is in the file
	pos = list.retrieve(search);

    //if not a message is displayed and false is returned
	if (pos <= -1)
	{
		cout << "Unable to find person." << endl;
		return false;
	}

    //if it is found the contact is read from the file
	fin.seekg(pos * 230, ios::beg);
	fin.read((char*)&con, sizeof(contact));

    //the edit menu function is called to handle editing the contact
	if (editmenu(con) == 1)
	{
        //attempts to remove the previous information
		if (list.remove(pos) == false)
		{
			cout << "Unable to remove previous data." << endl;
			return false;
		}

        //inserts the new contact information into the linklist
		if (list.insert(search, pos) == false)
		{
			cout << "Unable to insert new data." << endl;
			return false;
		}

        //writes the contact information back into its file position
		fin.seekp(pos * 230, ios::beg);
		fin.write((char*)&con, sizeof(contact));
		fin.clear();
	}

	return true;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in a partial name and then uses the linklist find function
* to locate any name that contains what was entered. If it doesnt find any it
* returns false otherwise it returns true.
*
* @param[in,out]  list    - reads in linklist class and outputs using insert
*
*****************************************************************************/
bool consearch(linklist list)
{
	string search;
	char temp[100];

	cin.ignore(1);

    //gets the name to search from the console
	cout << "Enter a name: ";
	cin.getline(temp, 100);
	search = temp;

	cout << endl;

    //calls the linklist find function to check display all contacts with that name
	if (list.find(search) == false)
	{
        //if none are found a message is displayed and false is returned
		cout << "No matches were found." << endl;
		return false;
	}
	return true;
}
