/*************************************************************************//**
 * @file
 *
 * @author Lyndon Engel
 *
 *
 * @section program_section Program Information
 *
 * @details 
 * This file holds all my functions that are used to run the program.Pretty
 * much the guts of the whole thing. 
 *
 *
 *
 *****************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "functdef.h"

using namespace std;

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function handles everything to do with the hamming (7,4) opperations.
* If the user specifys H74 then it will come to this function where they can
* then designate whether they want to encode, parity check, or decode a message
* they enter.
*
*****************************************************************************/
void ham74main()
{
    string input;
    char datastring[100];
    vector <int> x; //holds encoded messsage
    vector <int> z; //holds decoded message
    vector <int> r; //holds parity bits
    int i = 0, newinput = 0; 
    int temp; //used comma printing

    //the usage statement
    cout << "Please enter a valid command. Commands include: \n";
    cout << "encode: for Hamming(7,4) encoding \n";
    cout << "parity: for Hamming(7,4) parity-check \n";
    cout << "decode: for Hamming(7,4) decoding \n";
    cout << "back: return to main selection screen \n \n";
    cout << "Enter command: ";

    while (cin >> input)
    {
        //handles encode operation 
        if (input == "encode") 
        {
            fgets(datastring, sizeof(datastring), stdin); //grabs the message
            x = encode(datastring); // runs encode function
            //prints out the encoded message
            cout << "x = <";
            for (i = 0; i < (int)x.size(); i++)
            {
                cout << x[i];
                if ((temp = i + 1) != (int)x.size())
                {
                    cout << ",";
                }
            }
            cout << ">" << endl;
        }
        else if (input == "parity")
        {
            //like above this grabs the user inputted message
            fgets(datastring, sizeof(datastring), stdin);
            parity(datastring);
        }
        else if (input == "decode")
        {
            //grabs user message
            fgets(datastring, sizeof(datastring), stdin);
            r = decode(datastring);
            //prints the decoded message
            cout << "r = <";
            for (i = 0; i < (int)r.size(); i++)
            {
                cout << r[i];
                if ((temp = i + 1) != (int)r.size())
                {
                    cout << ",";
                }
            }
            cout << ">" << endl;
        }
        else if (input == "back") //returns back to the main menu
        {
            return;
        }
        else //output statment if command is invalid
        {
            cout << "Command invalid. Valid commands are: encode, parity, decode, and back \n" << endl;
            cout << "Enter new command: ";
            newinput = 1;
        }
        if (newinput != 1)
        {
            cout << endl << endl << "Enter command: ";
        }
        else
            newinput = 0;
    }
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function encodes the users inputed message using hamming (7,4) and then
* returns a vector with the incoded messages. 
*
* @param[in]      data    - reads in charcter array holding users message
* @returns        x       - vector holding encoded message
*****************************************************************************/
vector <int> encode(char data[])
{
    vector<int> databits; //vector that holds user message as ints
    vector <int> x; //holds encoded message
    int sum = 0, i = 1; //varibles

    //converts the bits from charcters to ints 
    while (data[i + 1] != '\0')
    {
        databits.push_back(data[i] - '0');
        i++;
    }
    //error checks to see if the user input is valid
    if (errorlength(databits, 1, "encode") == false || numerror(databits) == false)
    {
        ham74main();
    }
    //preforms matrix multiplication to encode message
    for (i = 0; i < 7; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            sum += databits.at(j) * G[i][j];
        }
        sum = ConvertToBinary(sum);
        x.push_back(sum);
        sum = 0;
    }
    return x;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function parity checks the users already encoded message. If there isnt 
* and error in the message it outputs vector with all 0's however if there is
* and error the function then it flips the wrong bit to make it correct and then 
* will output the correct encoded message.
*
* @param[in]      data    - reads in charcter array holding users message
*****************************************************************************/
void parity(char data[])
{
    vector<int> databits; //holds user message
    vector <int> z; //holds parity bits
    bool error = false; //bool for error checking 
    int sum = 0, temp = 0, i = 1; //integers
    int fix = -1; //used to fix the wrong bit

    //converts user message from charcters to ints 
    while (data[i + 1] != '\0')
    {
        databits.push_back(data[i] - '0');
        i++;
    }
    //error checks the user message
    if (errorlength(databits, 1, "parity") == false || numerror(databits) == false)
    {
        ham74main();
    }
    //uses matrix multiplication to find parity bits
    for (i = 0; i < 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            sum += databits.at(j) * H[i][j];
        }
        sum = ConvertToBinary(sum);
        z.push_back(sum);
        if (sum == 1)
        {
            error = true;
        }
        sum = 0;
    }
    //outputs parity bits
    cout << "z = <";
    for (i = 0; i < (int)z.size(); i++)
    {
        cout << z[i];
        if ((temp = i + 1) != (int)z.size())
        {
            cout << ",";
        }
    }
    cout << ">" << endl;

    //If there is an error this calculates what bit is causing it
    if (error == true)
    {
        if (z.at(2) == 1)
        {
            fix += 4;
        }
        if (z.at(1) == 1)
        {
            fix += 2;
        }
        if (z.at(0) == 1)
        {
            fix += 1;
        }
        //flips the bit causing the error
        if (databits.at(fix) == 0)
        {
            databits.at(fix) = 1;
        }
        else
        {
            databits.at(fix) = 0;
        }
        //outputs the correct encoded message
        cout << "x = <";
        for (i = 0; i < (int)databits.size(); i++)
        {
            cout << databits.at(i);
            if ((temp = i + 1) != (int)databits.size())
            {
                cout << ",";
            }
        }
        cout << ">" << endl;
    }
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function decodes the users inputed message using hamming (7,4) and then
* returns a vector with the incoded messages. 
*
* @param[in]      data    - reads in charcter array holding users message
* @returns        r       - vector holding decoded message
*****************************************************************************/
vector <int> decode(char data[])
{
    vector<int> databits; //holds user encoded message
    vector <int> r; //holds decoded message
    int sum = 0, i = 1;
    
    //again like above, this turns the charcters into ints
    while (data[i + 1] != '\0')
    {
        databits.push_back(data[i] - '0');
        i++;
    }
    //error checks message
    if (errorlength(databits, 1, "decode") == false || numerror(databits) == false)
    {
        ham74main();
    }
    //uses matrix multiplication to decode the message
    for (i = 0; i < 4; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            sum += databits.at(j) * R[i][j];
        }
        sum = ConvertToBinary(sum);
        r.push_back(sum);
        sum = 0;
    }
    return r;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function handles everything to do with the hamming (15,11) opperations.
* If the user specifys H74 then it will come to this function where they can
* then designate whether they want to encode, parity check, or decode a message
* they enter.
*
*****************************************************************************/
void ham15main()
{
    string input;
    char datastring[100];
    vector <int> x;
    vector <int> z;
    vector <int> r;
    int i = 0, newinput = 0;
    int temp;

    cout << "Please enter a valid command. Commands include: \n";
    cout << "encode: for Hamming(15,11) encoding \n";
    cout << "parity: for Hamming(15,11) parity-check \n";
    cout << "decode: for Hamming(15,11) decoding \n";
    cout << "back: return to main selection screen \n \n";
    cout << "Enter command: ";

    while (cin >> input)
    {
        if (input == "encode")
        {
            fgets(datastring, sizeof(datastring), stdin);
            x = encode15(datastring);

            cout << "x = <";
            for (i = 0; i < (int)x.size(); i++)
            {
                cout << x[i];
                if ((temp = i + 1) != (int)x.size())
                {
                    cout << ",";
                }
            }
            cout << ">" << endl;
        }
        else if (input == "parity")
        {
            fgets(datastring, sizeof(datastring), stdin);
            parity15(datastring);
        }
        else if (input == "decode")
        {
            fgets(datastring, sizeof(datastring), stdin);
            r = decode15(datastring);

            cout << "r = <";
            for (i = 0; i < (int)r.size(); i++)
            {
                cout << r[i];
                if ((temp = i + 1) != (int)r.size())
                {
                    cout << ",";
                }
            }
            cout << ">" << endl;
        }
        else if (input == "back")
        {
            return;
        }
        else
        {
            cout << "Command invalid. Valid commands are: encode, parity, decode, and back \n" << endl;
            cout << "Enter new command: ";
            newinput = 1;
        }
        if (newinput != 1)
        {
            cout << endl << endl << "Enter command: ";
        }
        else
            newinput = 0;
    }
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function encodes the users inputed message using hamming (15,11) and then
* returns a vector with the incoded messages. 
*
* @param[in]      data    - reads in charcter array holding users message
* @returns        x       - vector holding encoded message
*****************************************************************************/
vector <int> encode15(char data[])
{
    vector<int> databits;
    vector <int> x;
    int sum = 0, i = 1;

    while (data[i + 1] != '\0')
    {
        databits.push_back(data[i] - '0');
        i++;
    }

    if (errorlength(databits, 2, "encode") == false || numerror(databits) == false)
    {
        ham15main();
    }

    for (i = 0; i < 15; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            sum += databits.at(j) * G1511[i][j];
        }
        sum = ConvertToBinary(sum);
        x.push_back(sum);
        sum = 0;
    }
    return x;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function parity checks the users already encoded (15,11) message. If 
* there isnt and error in the message it outputs vector with all 0's however if
* there is and error the function then it flips the wrong bit to make it correct
* and then will output the correct encoded message.
*
* @param[in]      data    - reads in charcter array holding users message
*****************************************************************************/
void parity15(char data[])
{
    vector<int> databits;
    vector <int> z;
    int sum = 0, temp = 0, fix = -1, i = 1;
    bool error = false;

    while (data[i + 1] != '\0')
    {
        databits.push_back(data[i] - '0');
        i++;
    }

    if (errorlength(databits, 2, "parity") == false || numerror(databits) == false)
    {
        ham15main();
    }

    for (i = 0; i < 4; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            sum += databits.at(j) * H1511[i][j];
        }
        sum = ConvertToBinary(sum);
        z.push_back(sum);
        if (sum == 1)
        {
            error = true;
        }
        sum = 0;
    }

    //outputs parity bits
    cout << "z = <";
    for (i = 0; i < (int)z.size(); i++)
    {
        cout << z[i];
        if ((temp = i + 1) != (int)z.size())
        {
            cout << ",";
        }
    }
    cout << ">" << endl;

    if (error == true)
    {
        if (z.at(3) == 1)
        {
            fix += 8;
        }
        if (z.at(2) == 1)
        {
            fix += 4;
        }
        if (z.at(1) == 1)
        {
            fix += 2;
        }
        if (z.at(0) == 1)
        {
            fix += 1;
        }

        if (databits.at(fix) == 0)
        {
            databits.at(fix) = 1;
        }
        else
        {
            databits.at(fix) = 0;
        }

        cout << "x = <";
        for (i = 0; i < (int)databits.size(); i++)
        {
            cout << databits.at(i);
            if ((temp = i + 1) != (int)databits.size())
            {
                cout << ",";
            }
        }
        cout << ">" << endl;
    }
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function decodes the users inputed message using hamming (15,11) and then
* returns a vector with the incoded messages. 
*
* @param[in]      data    - reads in charcter array holding users message
* @returns        r       - vector holding decoded message
*****************************************************************************/
vector <int> decode15(char data[])
{
    vector<int> databits;
    vector <int> r;
    int sum = 0, i = 1;

    while (data[i + 1] != '\0')
    {
        databits.push_back(data[i] - '0');
        i++;
    }

    if (errorlength(databits, 2, "decode") == false || numerror(databits) == false)
    {
        ham15main();
    }

    for (i = 0; i < 11; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            sum += databits.at(j) * R1511[i][j];
        }
        sum = ConvertToBinary(sum);
        r.push_back(sum);
        sum = 0;
    }
    return r;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in integers and makes sure they are 1's and 0's. It does
* this by modding the numbers by 2. 
*
* @param[in]      n       - the bit that needs to be turned into 1 or 0.
* @returns        i       - the new number
* @returns        0       - if error
*****************************************************************************/
int ConvertToBinary(int n)
{
    int i = n % 2;

    if (i == 0 || i == 1)
    {
        return i;
    }
    else
        ConvertToBinary(n / 2);

    return 0;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function makes sure the length of the users inputted message is correct 
* for the command they are useing. If it is correct it returns true otherwise
* it outputs and error message and returns false.
*
* @param[in]      data      - reads in vector holding users message
* @param[in]      ptype     - what type of hamming code will be done
* @param[in]      command  - what command the user wants to use
* @returns        false     - if the length is incorrect
* @returns        true      - if the length is correct
*****************************************************************************/
bool errorlength(vector <int> data, int ptype, string command)
{
    //pretty straight forward error checking
    if (command == "encode" && ptype == 1 && data.size() != 4)
    {
        cout << "Error: Bit length not correct. Length should be 4 \n \n";
        return false;
    }
    else if ((command == "decode" || command == "parity") && ptype == 1 && data.size() != 7)
    {
        cout << "Error: Bit length not correct. Length should be 7 \n \n";
        return false;
    }
    else if (command == "encode" && ptype == 2 && data.size() != 11)
    {
        cout << "Error: Bit length not correct. Length should be 11 \n \n";
        return false;
    }
    else if ((command == "decode" || command == "parity") && ptype == 2 && data.size() != 15)
    {
        cout << "Error: Bit length not correct. Length should be 15 \n \n";
        return false;
    }
    else
        return true;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function checks to make sure that all the numbers in the users message
* are 1's and 0's. If they arent the function returns false.
*
* @param[in]      data      - reads in vector holding users message
* @returns        false     - if the message is incorrect
* @returns        true      - if the message is correct
*****************************************************************************/
bool numerror(vector<int> data)
{
    //makes sure every int is either a 1 or 0
    for (int i = 0; i < (int)data.size(); i++)
    {
        if (data.at(i) != 0)
        {
            if (data.at(i) != 1)
            {
                cout << "Error: your bit string should only contain 1's and 0's \n \n";
                return false;
            }
        }
    }
    return true;
}
