/**************************************************************************
*File: functs1.cpp
*
*Authors: Wyatt Engel, Lyndon Engel
***************************************************************************/
#include "Header.h"
/******************************************************************************
* Author: Lyndon Engel, Wyatt Engel
*
* Description: This function handles input from user
*
* Param: argc - arguement count
* Param: *argv[] - array of arguments
*
* Return: greater than 0 - correct input
* Return: 0 - incorrect input
******************************************************************************/
int check_input(int argc, char *argv[])
{
	ifstream fin;
	string line;
	int num_lines = 0;


	if (argc != 2)
	{
		cout << "incorrect input" << endl;
		return 0;
	}
	else
	{
		fin.open(argv[1]);
		if (!fin)
		{
			cout << "incorrect input" << endl;
			return 0;
		}
		else
		{
			while (getline(fin, line))
			{
				num_lines++;
			}
			fin.close();
		}
	}

	return num_lines;
}

/******************************************************************************
* Author: Lyndon Engel, Wyatt Engel
*
* Description: parses the 32 bit code into its appropriate instruc fields.
*
* Param: - instruct - structure to fill and return by reference
* Param: - code - A 32-bit value to be processed. 
******************************************************************************/
void fill_instructions(instruct_info &instruc, uint32_t code)
{
	instruc.address = (code & 0x00FFF000) >> 12;
	instruc.column = (code & 0x00000C00) >> 10;
	instruc.row = (code & 0x000003C0) >> 6;
	instruc.add_mode = (code & 0x0000001F) >> 2;
}


/******************************************************************************
* Author: Lyndon Engel, Wyatt Engel
*
* Description: this function prints the solution. 
*
* Param: instruct - structure with information to print 
* Param: address - the address of the current instruction in memory
* Param: instruction - the instruction itself as a hex string
* Param: ostream - output stream
******************************************************************************/
void trace_line(instruct_info instruct, uint32_t current, uint32_t instruction)
{
	uint32_t instruct_num = (instruct.row) << 2;
	instruct_num += instruct.column;
	int location = 0;
	stringstream ss;

	// find the instructions location in the CODE ARRAY
	for (int i = 0; i < 22; i++)
	{
		if (instruct_val[i] == instruct_num)
		{
			location = i;
		}
	}

	cout << setw(4) << setfill('0') << hex << current << ":  ";
	cout << setw(7) << setfill('0') << hex << instruction << "  ";
	cout << instruct_name[location] << "  ";

	ss << hex << AC;

	string AC_format = ss.str();

	if (AC_format.length() > 6)
	{
		AC_format = AC_format.substr(AC_format.length() - 6);
	}
	else
	{
		AC_format.insert(0, 6 - AC_format.length(), '0');
	}

	// if hald print nothing
	if (instruct_num == HALT || instruct_num == NOP)
	{
		cout << "     ";
	}
	// immediate not valid
	else if ((instruct_num == J || instruct_num == ST || instruct_num == EM ||
		instruct_num == JZ || instruct_num == JP || instruct_num == JN)
		&& instruct.add_mode == 1)
	{
		cout << "???  ";
	}
	else // default situation 
	{
		if (instruct.add_mode == 0)
		{
			cout << setw(3) << setfill('0') << hex << instruct.address << "  ";
		}
		else if (instruct.add_mode == 1)
		{
			cout << "IMM  ";
		}
		else
		{
			cout << "???  ";
		}
	}

	cout << "AC[" << AC_format << "]  ";
	cout << "X0[" << setfill('0') << setw(4) << hex << X0 << "]  ";
	cout << "X1[" << setfill('0') << setw(4) << hex << X1 << "]  ";
	cout << "X2[" << setfill('0') << setw(4) << hex << X2 << "]  ";
	cout << "X3[" << setfill('0') << setw(4) << hex << X3 << "]" << endl;
}

/******************************************************************************
* Author: Lyndon Engel
*
* Description: execute_instruct takes in the values from the object file and then excutes it
* depending on the instruction and addressing mode. IT then returns the address
* of the next instruction making jumps easier to handle.
*
* Param: instruc - the instruction from the the object file
* Param: current - the location of the instruction in memory 
*                          thats being excuted
*
* Returns: uint32_t - next instruction
******************************************************************************/
uint32_t execute_instruct(instruct_info instruc, uint32_t current)
{
	uint32_t instruction_num = (instruc.row) << 2;
	instruction_num += instruc.column;
	uint32_t addressing_mode = instruc.add_mode;

	switch (instruction_num)
	{
		//Stops the excution of the program
	case HALT:
		trace_line(instruc, current, memory[current]);
		cout << "Machine Halted - HALT instruction executed" << endl;
		exit(0);
		//Does nothing
	case NOP:
		break;
		//Load the accumulator from memory. 
	case LD:
		AC = LD_funct(instruc, current, memory[instruc.address]);
		break;
		//Store the accumulator uint32_to memory. 
	case ST:
		memory[instruc.address] = ST_funct(instruc, current, addressing_mode);
		break;
		//Exchanges the accumulator with memory. 
	case EM:
		AC = EM_funct(instruc, current, addressing_mode);
		break;
		//Adds memory to the accumulator. 
	case ADD:
		AC = ADD_funct(instruc, current, addressing_mode, memory[instruc.address]);
		break;
		//Subtracts memory from the accumulator. 
	case SUB:
		AC = SUB_funct(instruc, current, addressing_mode, memory[instruc.address]);
		break;
		//Clears the accumulator. 
	case CLR:
		AC ^= AC;
		break;
		//Complements the accumulator
	case COM:
		AC = ~AC;
		break;
		//AND memory to the accumulator
	case AND:
		AC = AND_funct(instruc, current, addressing_mode, memory[instruc.address]);
		break;
		//OR memory to the accumulator. 
	case OR:
		AC = OR_funct(instruc, current, addressing_mode, memory[instruc.address]);
		break;
		//XOR memory to the accumulator. 
	case XOR:
		AC = XOR_funct(instruc, current, addressing_mode, memory[instruc.address]);
		break;
		//Jumps to the specified memory address. 
	case J:
		if (addressing_mode == 0)
		{
			return instruc.address;
		}
		else
		{
			J_funct(instruc, current, addressing_mode);
		}
		break;

		//if zero jump to memory address
	case JZ:
		if (addressing_mode == 0)
		{
			if (AC == 0)
			{
				return instruc.address;
			}
			else
			{
				break;
			}
		}
		else
		{
			JZ_funct(instruc, current, addressing_mode);
		}
		break;
		//if negative jump to memory address
	case JN:
		if (addressing_mode == 0)
		{
			if (AC < 0)
			{
				return instruc.address;
			}
			else
			{
				break;
			}
		}
		else
		{
			JN_funct(instruc, current, addressing_mode);
		}
		break;
		//if positive jump to memory address
	case JP:
		if (addressing_mode == 0)
		{
			if (AC > 0)
			{
				return instruc.address;
			}
			else
			{
				break;
			}
		}
		else
		{
			JP_funct(instruc, current, addressing_mode);
		}
		break;
	case LDX:  // NOT IMPLEMENTED IN THIS PROGRAM
	case ADDX:
	case STX:
	case SUBX:
	case EMX:
	case CLRX:
		trace_line(instruc, current, memory[current]);
		cout << "Machine Halted - unimplemented opcode" << endl;
		exit(1);
	default:
		trace_line(instruc, current, memory[current]);
		cout << "Machine Halted - undefined opcode" << endl;
		exit(1);
	}

	return ++current;
}

/******************************************************************************
* Author: Wyatt Engel
*
* Description: run_prog takes the first instruction, 
* and then runs the program from that instructions spot.
*
* Param: first_instruct - Address of first instruction
******************************************************************************/
void run_prog(uint32_t address_first)
{
	uint32_t current = address_first;
	uint32_t prev = 0;
	instruct_info instruc;

	while (true)
	{
		prev = current;

		fill_instructions(instruc, memory[current]);

		current = execute_instruct(instruc, current);

		trace_line(instruc, prev, memory[prev]);
	}
}

/******************************************************************************
* Author: Lyndon Engel, Wyatt Engel
*
* Description: This function handles reading in the instructions to memory
*
* Param: file: file with instructions
* Param: line_count: number of lines in file
******************************************************************************/
int load_prog(char* file, int line_count)
{
	ifstream fin;
	string instruction_address;
	string str_instruction;
	string str_num_instructions;
	int int_num_instruction = 0;

	fin.open(file);

	if (!fin)
		exit(1);

	for (int i = 0; i < line_count - 1; ++i)
	{
		fin >> instruction_address;
		fin >> str_num_instructions;

		int num_instructions = stoi(str_num_instructions);
		int add_val = (uint32_t)stoul(instruction_address, nullptr, 16);

		for (int i = 0; i < num_instructions; ++i)
		{
			fin >> str_instruction;
			int_num_instruction = (uint32_t)stoul(str_instruction, nullptr, 16);

			memory[add_val + i] = int_num_instruction;
		}
	}

	fin >> instruction_address;
	fin.close();

	return (uint32_t)stoul(instruction_address, nullptr, 16);
}
