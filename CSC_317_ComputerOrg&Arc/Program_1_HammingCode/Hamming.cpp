/*************************************************************************//**
 * @file
 *
 * @mainpage Homework #1 Hamming Code 
 *
 * @section Section M001
 *
 * @author Lyndon Engel
 *
 * @date 10/2/2016
 *
 * @par Professor:
 *         Christer H. Karlsson
 *
 * @par Course:
 *         CSC 317
 *
 * @par Location:
 *         McLaury -  Room 304
 *
 * @section program_section Program Information
 *
 * @details 
 * This program can create, parity-check, error correct and decode a message using
 * Hamming(7,4) or Hamming(15,11). It does this by using three Hamming matrices 
 * (G, H and R) for Hamming(7,4) and three different hamming matrices 
 * (G1511, H1511, and R1511) for Hamming(15,11). The program will first ask the user
 * what Hamming code to be used (or if the user wants to exit). The next question it
 * will ask is whether the user wants to create, parity check (with error correction)
 * or decode a message. The user will then provide either the data or the message, 
 * the program will calculate either the message or the data. All messages and data
 * will be entered as a vector of binary digits. Example, four bit data 1011, is a
 * seven. Fifteen bit message, will have eleven data bits and four parity bits and look
 * something like 100100111011110.
 *
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 * Typing Hamming will start the program. After which a prompt will appear telling
 * you the first basic instructions.Those being H74 to do hamming (7,4) functions or
 * H1511 to do hamming (15,11) functions. There will also be an option to exit.
 *
 *
 * @par Usage:
   @verbatim

   >>./Hamming
   . . .
   >>encode 1011
   x = <0, 1, 1, 0, 0, 1, 1>
   . . .
   >>parity 0100011
   z = <0, 0, 0>
   . . .
   >>parity 0100111
   z = <1, 0, 1>
   x = <0, 1, 1, 0, 0, 1, 1>
   . . .
   >>decode 0110011
   r = <1, 0, 1, 1>

   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug 
 * - No known bugs 
 *
 * @todo none
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date           Modification
   -------------  -------------------------------------------------------------
   Sep  23, 2016  General usability
   Sep  25, 2016  Hamming (7,4) encode, parity
   Sep	28, 2016   Hamming (7,4) decode, and parity error handling 
   Sep  30, 2016  Hamming (15,11) encode, parity
   Oct  1,  2016  finishing up Hamming (15,11)
   Oct  3, 2016   error handling
   Oct  5, 2016   Documentation

   @endverbatim
 *
 *****************************************************************************/
#include "functdef.h"

using namespace std;

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function handles the main menu of the program. Its basically
* the selection screen between Hamming (7,4) opperations or Hamming (15,11)
* opperations. 
*
* @returns        x       - when the user wants to exit
*****************************************************************************/
int main()
{
    string input;
    int temp = 0;

    cout << " \n \n Please enter a valid command. Commands include: \n";
    cout << "H74: for Hamming(7,4) encoding, parity-check and decoding \n";
    cout << "H1511: for Hamming(15,11) encoding, parity-check and decoding \n";
    cout << "exit: to exit the progam \n \n";
    cout << "Enter command: ";

    while (getline(cin, input))
    {
        if (input == "H74")
        {
            ham74main();
            temp = 1;
        }
        else if (input == "H1511")
        {
            ham15main();
            temp = 1;
        }
        else if (input == "exit")
        {
            break;
        }
        else
        {
            if (temp == 0)
            {
                cout << "Command invalid. Valid commands are: H74, H1511, and exit" << endl;
            }
            else
            cout << "\n \n Please enter a valid command. Commands include: \n";
            cout << "H74: for Hamming(7,4) encoding, parity-check and decoding \n";
            cout << "H1511: for Hamming(15,11) encoding, parity-check and decoding \n";
            cout << "exit: to exit the progam \n \n";
            cout << "Enter command: ";
            temp = 0;
        }
    }
    return 0;
}
