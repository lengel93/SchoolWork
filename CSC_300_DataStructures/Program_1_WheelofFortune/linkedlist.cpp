#include <iostream>
#include "linkedlist.h"
#include <stdlib.h>

using namespace std;


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:	Sets headptr to NULL
*****************************************************************************/
linklist::linklist()
{ // constructor sets headptr to nullptr
    headptr = nullptr;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:	Deconstructor
*****************************************************************************/
linklist::~linklist()
{ //deconstructor
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in the file that contains the category and answers. It 
* then runs through a while loop until it reaches the end of the file inserting
* a category and answer into a new node of a linked list. Then it inserts this
* node at the end of the linked list.
*
* @param[in]      fin	- takes in the file that holds category and answers
* @returns        true	- If its able to insert the node
* @returns		  false	- If it runs out of memory
*****************************************************************************/
bool linklist::insert(ifstream &fin)
{
	string catagory;
	string answer;

	//creates new node
	node *temp = new(nothrow)node;

	//checks if the node was successfully made
	if (temp == NULL)
	{
		cout << "ran out of memory" << endl;
		return false;
	}
	//reads in a category and answer from the file
	getline(fin, catagory);
	getline(fin, answer);

	//sets the category and answer in the node that was created
	temp->catagory = catagory;
	temp->answer = answer;
	temp->next = nullptr;

	//If the linked list is empty it sets the new node to the headptr
	if (headptr == NULL)
	{
		headptr = temp;
	}

	temp = headptr;

	//This loop continues to do what happened above for the whole linked list
	while (!fin.eof())
	{
		getline(fin, catagory);
		getline(fin, answer);

		//if the category doesn't start with a letter it exits the loop. 
		//Main reason for this is if there is an empty line at the end of the file
		if (isalpha(catagory[0]) == 0)
		{
			break;
		}

		temp->next = new(nothrow)node;

		if (temp->next == NULL)
		{
			cout << "ran out of memory";
			return false;
		}

		temp = temp->next;

		temp->catagory = catagory;
		temp->answer = answer;
		temp->next = nullptr;
	}

	return true;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Runs the linked list through a while loop printing each node.
*
*****************************************************************************/
void linklist::print()
{
	node *temp;

	temp = headptr;

	while (temp->next != nullptr)
	{
		cout << temp->catagory << endl;
		cout << temp->answer << endl;
		temp = temp->next;
	}
	cout << temp->catagory << endl;
	cout << temp->answer << endl;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in the name of a category and its answer. It then goes 
* through the linked list looking for the node that contains a matching category
* and answer. Once the node is found it is removed and true is returned. If the
* node isn't found false is returned. 
*
* @param[in]      cat	- Category name
* @param[in]      ans	- Answer name
* @returns        true	- If node is successfully removed
* @returns		  false	- If node isn't found
*****************************************************************************/
bool linklist::remove(string cat, string ans)
{
	node *temp;
	node *prev;

	//checks if the linked list is empty
	if (headptr == NULL)
	{
		return false;
	}
	//checks if the node were looking for is at the head pointer and 
	//if its the last node in the list
	if (headptr->catagory == cat && headptr->answer == ans && headptr->next != NULL)
	{
		temp = headptr;
		headptr = headptr->next;
		delete temp;
		return true;
	}
	//checks if the node were looking for is at the head pointer and 
	//if its the last node in the list
	if (headptr->catagory == cat && headptr->answer == ans && headptr->next == NULL)
	{
		temp = headptr;
		headptr = headptr->next;
		delete temp;
		return true;
	}

	temp = headptr;
	prev = headptr;

	//Loop that runs through the linked list looking for the matching node.
	//Once found it is removed
	while (temp->next != NULL)
	{
		temp = temp->next;
		
		if (temp->catagory == cat && temp->answer == ans)
		{
			prev->next = temp->next;
			delete temp;
			return true;
		}
		prev = prev->next;
	}
	return false;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Checks if the linked list is empty. If it is empty it returns true otherwise
* it returns false.
*
* @returns        true	- If the list is empty
* @returns		  false	- If the list isn't empty
*****************************************************************************/
bool linklist::is_empty()
{
	if (headptr == nullptr) // checks if the list is empty
	{
		return true; // returns true if empty
	}
	return false; //returns false if list has data
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Return the size of the linked list. 
*
* @returns        size - size of the list
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
	while (temp->next != nullptr)
	{
		temp = temp->next;
		size++;
	}

	size += 1;

	// returns the size of the list
	return size;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function randomly selects a random number based on the size of the
* linked list and then takes in the category and answer at that position in 
* the list. It then checks to make sure the answer isn't to long for the board.
* If it is, it deletes the node and then recalls the function.
*
* @param[out]      cat	- Takes in a category name
* @param[out]      ans	- Takes in a answer
* @param[in]       list	- Reads int he linked list
*****************************************************************************/
bool linklist::select(string &cat, string &ans, linklist &list)
{

	int number, i = 0;
	int size;
	node *temp;

	if(list.is_empty() == true)
	{
		return false;
	}

	temp = headptr;

	size = list.size();

	number = rand() % size + 1;

	for (i = 1; i < number; i++)
	{
		temp = temp->next;
	}

	cat = temp->catagory;
	ans = temp->answer;

	if(ans.size() > 52)
	{
		list.remove(cat,ans);
		list.select(cat,ans,list);
	}

	return true;
}


