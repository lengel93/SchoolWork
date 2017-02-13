
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#ifndef __LINKLIST_H_
#define __LINKLIST_H_

/*!
* @brief Holds information about a contact user
*/
struct contact
{
    char name[50];/*!< Holds name of contact */
    char address[50];/*!< Holds address of contact */
    char city[35];/*!< Holds city of contact */
    char state[5];/*!< Holds state of contact */
    int zipcode;/*!< Holds zipcode of contact */
    char email[50];/*!< Holds email of contact */
    char mobilePhone[16];/*!< Holds cellphone number of contact */
    char lanPhone[16];/*!< Holds phonenumber of contact */
    int birthdate;/*!< Holds birthday of contact */
};


/*!
* @brief Holds information about a contact name and file postion.
* Also all the linklist functions.
*/
class linklist
{
public:
    linklist(); /*!< Default constructor */
    ~linklist(); /*!< deconstructor */
    bool insert(string name, int filepos);/*!< Insert function for linklist */
    bool remove(string name);/*!< remove function for linklist */
    bool remove(int filepos);/*!< remove function for linklist */
    bool is_empty();/*!< checks if linklist is empty */
    int size();/*!< finds size of linklist */
    void print(ostream &out);/*!< prints out the linklist */
    bool find(string name);/*!< finds a name in the linklist */
    int retrieve(string name);/*!< finds the file postion of a name*/
private:
    struct node
    {
        string name; /*!< name of person */
        int fileIndex; /*!< postion in the file */
        node *next;/*!< points to next node in the linklist */
    };
    node *headptr; /*!< points to first node in the linklist */
};

#endif

int editmenu(contact &person);

void mainmenu(int size);

void createdef(contact &defper);

bool checkstate(char state[]);

void extractdate(int birthdate, int &month, int &day, int &year);

int compressdate(int month, int day, int year);

bool checkDate(int month, int day, int year);


//main menu functions
bool addcontact(fstream &fin, linklist list, contact con, int &maxpos);

bool display(contact con, linklist list, fstream &fin);

bool editcon(contact con, linklist list, fstream &fin);

bool consearch(linklist list);