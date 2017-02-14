/**************************************************************************//**
* @file
*****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

/** @brief Linklist Class that contains the file of words*/
class linklist
{
public:
	linklist(); /*!< Default constructor */
	~linklist(); /*!< deconstructor */
	bool insert(ifstream &fin);/*!< Insert function for linklist */
	void print();
	bool remove(string cat, string ans);/*!< remove function for linklist */
	bool is_empty();/*!< checks if linklist is empty */
	int size();/*!< finds size of linklist */
	bool select(string &cat, string &ans, linklist &list);/*!< randomly selects a node */
protected:
	/** @brief Node that contains cateagory and word*/
	struct node
	{
		string catagory; /*!< name of person */
		string answer; /*!< postion in the file */
		node *next;/*!< points to next node in the linklist */
	};
	node *headptr; /*!< points to first node in the linklist */
};

