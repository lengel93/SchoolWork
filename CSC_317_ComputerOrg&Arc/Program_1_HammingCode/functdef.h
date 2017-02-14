#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

/*************************************************************************//**
 * @file
 *
 * @author Lyndon Engel
 *
 *
 * @section program_section Program Information
 *
 * @details 
 * This file holds all the function definitions and my static arrays used
 * throughout the program.
 *
 *
 *
 *****************************************************************************/
void ham74main();
vector <int> encode(char data[]);
void parity(char data[]);
vector <int> decode(char data[]);

void ham15main();
vector <int> encode15(char data[]);
void parity15(char data[]);
vector <int> decode15(char data[]);

int ConvertToBinary(int n);
bool numerror(vector<int> data);
bool errorlength(vector<int> data, int ptype, string command);

/*!< Holds Hamming (7,4) encoding matrix */
static int G[7][4] = {
    1, 1, 0, 1,
    1, 0, 1, 1,
    1, 0, 0, 0,
    0, 1, 1, 1,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

/*!< Holds Hamming (7,4) parity matrix */
static int H[3][7] = {
    1, 0, 1, 0, 1, 0, 1,
    0, 1, 1, 0, 0, 1, 1,
    0, 0, 0, 1, 1, 1, 1
};

/*!< Holds Hamming (7,4) decoding matrix */
static int R[4][7] = {
    0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1
};

/*!< Holds Hamming (15,11) encoding matrix */
static int G1511[15][11] = {
    1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1,
    1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
};

/*!< Holds Hamming (15,11) parity matrix */
static int H1511[4][15] = {
    1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
    0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
    0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1
};


/*!< Holds Hamming (15,11) decoding matrix */
static int R1511[11][15] = {
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
};
