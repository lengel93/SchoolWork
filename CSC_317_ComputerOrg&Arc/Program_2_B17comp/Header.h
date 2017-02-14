/**************************************************************************
*File: Header.h
*
*Authors: Wyatt Engel, Lyndon Engel
************************************************************************/


#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <stdint.h>

using namespace std;


/*Array used to simulate memory*/
static uint32_t memory[4095];


/* Global values used for registers, Buses and other logic*/
static uint32_t MAR = 0, IC = 0, ABUS = 0, MDR = 0, AC = 0, ALU = 0, IR = 0;
static uint32_t  DBUS = 0, X0 = 0, X1 = 0, X2 = 0, X3 = 0;

/* Instructions are given values so they can be found in the array */
const char HALT = 0, LD = 1, ADD = 2, J = 3, NOP = 4, ST = 5, SUB = 6, JZ = 7;
const char EM = 9, CLR = 10, JN = 11, COM = 14, JP = 15, AND = 18, OR = 22;
const char XOR = 26, LDX = 33, ADDX = 34, STX = 37, SUBX = 38, EMX = 41, CLRX = 42;


// Arrays that are used as look-up tables for the instructions
static const char instruct_val[22] =
{ 0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 14,
15, 18, 22, 26, 33, 34, 37, 38, 41, 42 };

static const string instruct_name[22] =
{ "HALT", "LD  ", "ADD ", "J   ", "NOP ", "ST  ", "SUB ", "JZ  ", "EM  ",
"CLR ", "JN  ", "COM ", "JP  ", "AND ", "OR  ", "XOR ", "LDX ", "ADDX",
"STX ", "SUBX", "EMX ", "CLRX" };

// bitmask used for clearing 12 and 24 bit registers
#define _REG_12_MAX 4095
#define _REG_24_MAX 16777215


/* structure that holds information about the instruction */
struct instruct_info
{
	uint32_t skip : 8; 
	uint32_t add_mode : 6; 
	uint32_t address : 12; 
	uint32_t column : 2;
	uint32_t row : 4;
};

/*Check input file*/
int check_input(int argc, char *argv[]);

/*Function Prototypes*/
void fill_instructions(instruct_info &instruct, uint32_t code);
uint32_t execute_instruct(instruct_info $instruct, uint32_t current);
int load_prog(char* file, int line_count);
void run_prog(uint32_t address_first);
void trace_line(instruct_info instruct, uint32_t current, uint32_t instruct_info);

/*Instruction Prototypes*/
uint32_t LD_funct(instruct_info &instruc, uint32_t &current_address, uint32_t add);
uint32_t ADD_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode, uint32_t add);
uint32_t ST_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode);
uint32_t SUB_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode, uint32_t add);
uint32_t EM_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode);

void J_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode);
void JN_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode);
void JP_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode);
void JZ_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode);

uint32_t AND_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode, uint32_t add);
uint32_t OR_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode, uint32_t add);
uint32_t XOR_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode, uint32_t add);
