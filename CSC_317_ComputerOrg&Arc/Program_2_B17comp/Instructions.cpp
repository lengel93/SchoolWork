/**************************************************************************
*File: Instructions.cpp
*
*Authors: Wyatt Engel, Lyndon Engel
************************************************************************/

#include "Header.h"

/**************************************************************************
 * @author Lyndon Engel
 * 
 * @par Description: 
 * This function depending on the addressing add_mode will load the accumulator(AC) 
 * from memeory using the instruction address. If the mode is 0 it will do and 
 * immediate address pulling the AC from the memory array. If the addressing 
 * mode is 1it will use a direct address. 
 *
 * @param[in]  instruc - the instruction from the the object file
 * @param[in]  current_address - the location of he instruction in memory 
 *             thats being excuted
 * @param[in]  add - holds the AC from the memory array 
 *
 * @returns AC the accumulator
 * 
 *****************************************************************************/
uint32_t LD_funct(instruct_info &instruc, uint32_t &current_address, uint32_t add)
{

	if (instruc.add_mode == 0)
	{
		AC = add;
	}
	else if (instruc.add_mode == 1)
	{
		AC = instruc.address;
	}
	else if (instruc.add_mode == 2 || instruc.add_mode == 4 || instruc.add_mode == 6)
	{
		cout << "Machine Halted - unimplemented addressing mode" << endl;
		trace_line(instruc, current_address, memory[current_address]);
		exit(0);
	}
	else
	{
		cout << "Machine Halted - illegal addressing mode" << endl;
		trace_line(instruc, current_address, memory[current_address]);
		exit(0);
	}

	return AC;
}

/**************************************************************************//** 
 * @author Lyndon Engel, Wyatt Engel
 * 
 * @par Description: 
 * This function adds memeory to the accumulator depending on the addressing
 * mode.
 *
 * @param[in]  instruc - the instruction from the the object file
 * @param[in]  current_address - the location of he instruction in memory 
 *             thats being excuted
 * @param[in]  addressing_mode - holds desired addressing mode
 * @param[in]  add - holds the AC from the memory array 
 *
 * @returns AC the accumulator
 * 
 *****************************************************************************/
uint32_t ADD_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode, uint32_t add)
{

	if (0 == addressing_mode)
	{
		AC += add;
	}
	else if (1 == addressing_mode)
	{
		return AC;
	}
	else if (2 == addressing_mode || 4 == addressing_mode || 6 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - unimplemented addressing mode" << endl;
		exit(0);
	}
	else
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}

	return AC;
}

/**************************************************************************//** 
 * @author Lyndon Engel, Wyatt Engel
 * 
 * @par Description: 
 * This function stores the accumulator into memeory if the addressing mode is
 * direct. 
 *
 * @param[in]  instruc - the instruction from the the object file
 * @param[in]  current_address - the location of he instruction in memory 
 *             thats being excuted
 * @param[in]  addressing_mode - holds desired addressing mode
 *
 * @returns AC the accumulator
 * 
 *****************************************************************************/
uint32_t ST_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode)
{

	if (0 == addressing_mode)
	{
		return AC;
	}
	else if (1 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
	else if (2 == addressing_mode || 4 == addressing_mode || 6 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - unimplemented addressing mode" << endl;
		exit(0);
	}
	else
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
}

/**************************************************************************//** 
 * @author Lyndon Engel, Wyatt Engel
 * 
 * @par Description: 
 * This function removes memeory from teh accumulator depending on the addressing
 * mode.
 *
 * @param[in]  instruc - the instruction from the the object file
 * @param[in]  current_address - the location of he instruction in memory 
 *             thats being excuted
 * @param[in]  addressing_mode - holds desired addressing mode
 * @param[in]  add - holds the AC from the memory array 
 *
 * @returns AC the accumulator
 * 
 *****************************************************************************/
uint32_t SUB_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode, uint32_t add)
{

	if (0 == addressing_mode)
	{
		AC -= add;
	}
	else if (1 == addressing_mode)
	{
		AC -= instruc.address;
	}
	else if (2 == addressing_mode || 4 == addressing_mode || 6 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - unimplemented addressing mode" << endl;
		exit(0);
	}
	else
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}

	return AC;
}

/**************************************************************************//** 
 * @author Lyndon Engel, Wyatt Engel
 * 
 * @par Description: 
 * This function exchanges the accumulator with memory if the addressing mode 
 * is direct.
 *
 * @param[in]  instruc - the instruction from the the object file
 * @param[in]  current_address - the location of he instruction in memory 
 *             thats being excuted
 * @param[in]  addressing_mode - holds desired addressing mode
 *
 * @returns AC the accumulator
 * 
 *****************************************************************************/
uint32_t EM_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode)
{
	uint32_t temp;

	if (0 == addressing_mode)
	{
		temp = AC;
		AC = instruc.address;
		instruc.address = temp;
	}
	else if (1 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
	else if (2 == addressing_mode || 4 == addressing_mode || 6 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - unimplemented addressing mode" << endl;
		exit(0);
	}
	else
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
	return AC;
}

/**************************************************************************//** 
 * @author Lyndon Engel, Wyatt Engel
 * 
 * @par Description: 
 * This function checks for all the possible errors in the jump instruction.
 *
 * @param[in]  instruc - the instruction from the the object file
 * @param[in]  current_address - the location of he instruction in memory 
 *			   thats being excuted
 * @param[in]  addressing_mode - holds desired addressing mode
 *
 *****************************************************************************/
void J_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode)
{

	if (1 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
	else if (2 == addressing_mode || 4 == addressing_mode || 6 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - unimplemented addressing mode" << endl;
		exit(0);
	}
	else
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * This function checks for all the possible errors in the JN instruction.
 *
 * @param[in]  instruc - the instruction from the the object file
 * @param[in]  current_address - the location of he instruction in memory 
 *			   thats being excuted
 * @param[in]  addressing_mode - holds desired addressing mode
 * *
 *****************************************************************************/
void JN_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode)
{
	if (1 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
	else if (2 == addressing_mode || 4 == addressing_mode || 6 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - unimplemented addressing mode" << endl;
		exit(0);
	}
	else
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * This function checks for all the possible errors in the JP instruction.
 *
 * @param[in]  instruc - the instruction from the the object file
 * @param[in]  current_address - the location of he instruction in memory 
 *			   thats being excuted
 * @param[in]  addressing_mode - holds desired addressing mode
 * 
 *****************************************************************************/
void JP_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode)
{

	if (1 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
	else if (2 == addressing_mode || 4 == addressing_mode || 6 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - unimplemented addressing mode" << endl;
		exit(0);
	}
	else
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
}

/**************************************************************************//** 
 * @author Lyndon Engel
 * 
 * @par Description: 
 * This function checks for all the possible errors in the JP instruction.
 *
 * @param[in]  instruc - the instruction from the the object file
 * @param[in]  current_address - the location of he instruction in memory 
 *			   thats being excuted
 * @param[in]  addressing_mode - holds desired addressing mode
 * 
 *****************************************************************************/
void JZ_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode)
{
	if (1 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
	else if (2 == addressing_mode || 4 == addressing_mode || 6 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - unimplemented addressing mode" << endl;
		exit(0);
	}
	else
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
}

/**************************************************************************//** 
 * @author Lyndon Engel, Wyatt Engel
 * 
 * @par Description: 
 * This function AND's memory to the accumulator
 *
 * @param[in]  instruc - the instruction from the the object file
 * @param[in]  current_address - the location of he instruction in 
 *			   memory thats being excuted
 * @param[in]  addressing_mode - holds desired addressing mode
 * @param[in]  add - holds the AC from the memory array 
 *
 * @returns AC the accumulator
 * 
 *****************************************************************************/
uint32_t AND_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode, uint32_t add)
{

	if (0 == addressing_mode)
	{
		AC &= add;
	}
	else if (1 == addressing_mode)
	{
		AC &= instruc.address;
	}
	else if (2 == addressing_mode || 4 == addressing_mode || 6 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - unimplemented addressing mode" << endl;
		exit(0);
	}
	else
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
	return AC;
}

/**************************************************************************//** 
 * @author Lyndon Engel, Wyatt Engel
 * 
 * @par Description: 
 * This function OR's memory to the accumulator
 *
 * @param[in]  instruc - the instruction from the the object file
 * @param[in]  current_address - the location of he instruction in 
 *			   memory thats being excuted
 * @param[in]  addressing_mode - holds desired addressing mode
 * @param[in]  add - holds the AC from the memory array 
 *
 * @returns AC the accumulator
 * 
 *****************************************************************************/
uint32_t OR_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode, uint32_t add)
{

	if (0 == addressing_mode)
	{
		AC |= add;
	}
	else if (1 == addressing_mode)
	{
		AC |= instruc.address;
	}
	else if (2 == addressing_mode || 4 == addressing_mode || 6 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - unimplemented addressing mode" << endl;
		exit(0);
	}
	else
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
	return AC;
}

/**************************************************************************//** 
 * @author Lyndon Engel, Wyatt Engel
 * 
 * @par Description: 
 * This function XOR's memory to the accumulator
 *
 * @param[in]  instruc - the instruction from the the object file
 * @param[in]  current_address - the location of he instruction in 
 *			   memory thats being excuted
 * @param[in]  addressing_mode - holds desired addressing mode
 * @param[in]  add - holds the AC from the memory array 
 *
 * @returns AC the accumulator
 * 
 *****************************************************************************/
uint32_t XOR_funct(instruct_info &instruc, uint32_t &current_address, uint32_t &addressing_mode, uint32_t add)
{

	if (0 == addressing_mode)
	{
		AC ^= memory[instruc.address];
	}
	else if (1 == addressing_mode)
	{
		AC ^= instruc.address;
	}
	else if (2 == addressing_mode || 4 == addressing_mode || 6 == addressing_mode)
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - unimplemented addressing mode" << endl;
		exit(0);
	}
	else
	{
		trace_line(instruc, current_address, memory[current_address]);
		cout << "Machine Halted - illegal addressing mode" << endl;
		exit(0);
	}
	return AC;
}
