/********************************************************
*File: b17.cpp
*
*Authors: Wyatt Engel, Lyndon Engel
*
*Program: b17 emulator 
*
*Professor: Dr. Karlsson 
*
*Due: 12/5/2016
*
***************Implementation Description******************
* This program simulates a b17 computer. The program will read
* an object file, line by line, storing each instruction
* in RAM, then executing each instruction after. a trace line
* of each instruction will be outputted as a result. The hardware
* is implemented as follows:
*
*Main Memory: Integer array of size 4096
*Registers: Mar, IC X0-3, ABUS, MDR, AC, ALU, IR, DBUS
*           implemented as uint32_t (ignore top 8 bits)
*Addressing modes: Direct, Immediate, Indexed, Indirect
*                  and other are implemented as uin32_t constants
*Instruction Set: Const Chars, string array, character array.
*
*
*******************Testing Description*********************
* We tested a variety of instructions, including an empty 
* object file. All object files are included.
* empty.obj - empty object file
* test1.obj - object file 1 from program description
* test2.obj - object file 2 from program description
* test3.obj - object file 3 from program description
* test4.obj - object file 4 from program description 
* 
*****************Compile and Usage*************************
*
*Compile: >make
*Usage: >./b17 <testfile.obj>
*
***********************************************************/

#include "Header.h"

/******************************************************************************
* Author: Lyndon Engel, Wyatt Engel 
*
* Description: main executes input checking, loading the program and 
*              running the program.
*
* @param[in] argc - number of arguments
* @param[in] *argv[] - array of arguments 
******************************************************************************/
int main(int argc, char *argv[])
{
	int start_prog;
	int num_lines;

	num_lines = check_input(argc, argv);

	if (0 != num_lines)
	{
		start_prog = load_prog(argv[1], num_lines);
		run_prog(start_prog);
	}

	return 0;
}
