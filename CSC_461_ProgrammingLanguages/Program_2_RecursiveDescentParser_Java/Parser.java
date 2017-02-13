package Parser;

import java.util.*;

/**
 * Program: Programming Assignment #2: Recursive Descent Parser in Java
Author: Lyndon Engel, Charles Bonn
Class: CSC 461 Programming Languages
Instructor: Dr.Weiss
Date: 10/25/2016
Description: This program is a recursive descent parsers for the following 
EBNF Expression Grammar:

<expr> -> <term> { <addop> <term> }
<term> -> <factor> { <mulop> <factor> }
<factor> -> <integer> | <float> | <id> | '(' <expr> ')' | [-] <factor>
<integer> -> <digit> { <digit> }
<float> -> <integer> . <integer>
<id> -> <letter> { <letter> | <digit> }
<letter> -> A | B | C | D | E | F | G | H | I | J | K | L | M |
 N | O | P | Q | R | S | T | U | V | W | X | Y | Z |
 a | b | c | d | e | f | g | h | i | j | k | l | m |
 n | o | p | q | r | s | t | u | v | w | x | y | z | _
<digit> -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
<addop> -> + | -
<mulop> -> * | / | %

The program works by taking in a user inputted expression and then outputting 
whether the expression is a valid or not. Each expression should be inputted 
on a separate a line. Spaces can be included between expression tokens but 
is not necessary. The program will continue to except input until the user
enters a blank line. The user can also input a -t into the command line in 
order for the program to print out each token of the expression. 

Usage: java Parser [-t]

The –t switch prints out a list of tokens in addition to the validity message.

Known bugs/missing features:
* a b is recognized as a valid expression
Modifications:
Date                Comment
10/01    User input
10/05    Mulop,addop,digit,and letter function
10/10    id and float function
10/14	 factor/integer function
10/15    term function
10/20    expression function
10/22	 commenting/error checking
----    ------------------------------------------------
 */

/**
 * This class handles the command line argument for printing token charters
 * if -t is entered it will set the flag to true otherwise it will remain false.
 * @author Lyndon Engel
 */
public class Parser
{
    /**
     *A global flag, so the program knows whether to print the tokens or not.
     */
    public static boolean tokenFlag = false;

    /**
     *This function pulls in the command line arguments
     * 
     * @param args command line arguments
     */
    public static void main( String [] args )
    {
        parseCMD( args );
        Scan scan = new Scan( tokenFlag );
    }
 
    /**
     *This function checks whether or not to set the tokenFlag to true
     * @param args command line arguments
     */
    public static void parseCMD(String [] args)
    {
	for( String arg : args )
 	{
	    if( arg.equals("-t") )
	    {
		tokenFlag = true;
            }
	}
    }    
}
