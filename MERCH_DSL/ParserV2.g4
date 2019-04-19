// Define grammar called ParserV2
grammar ParserV2;

/*
 * Lexer Rules
 *
 * - Lexer rules are upper case
 * - Lexer rules are analyzed in the order they appear
 * - Lexer rules can be ambiguous
 * - Rules end in a semi-colon ';'
 */

COMMA	:           ','    ->skip      ; //We will skip comma's when writing out
DOT	:           '.'(' ')*          ;
COMET   :           '#'(' ')*          ; 
GET	:     ('G'|'g')('et')(' ')*    ;
FOR	:     ('F'|'f')('or')(' ')*    ;
// FUNC matches movingAverage with any capitalization of the M and A
FUNC	:    ('m'|'M')('oving')(' ')*
	    ('a'|'A')('verage')(' ')*  |
             ('P'|'p')('rice')(' ')*   |
	     ('H'|'h')('igh')(' ')*
             ('P'|'p')('rice')(' ')*   |
	      ('L'|'l')('ow')(' ')*
             ('P'|'p')('rice')(' ')*   |  
	     ('V'|'v')('olume')(' ')*  |
            ('C'|'c')('losing')(' ')*
             ('P'|'p')('rice')(' ')*    |
             ('O'|'o')('pening')(' ')*
             ('P'|'p')('rice')(' ')*   |
             ('C'|'c')('urrent')(' ')*
             ('P'|'p')('rice')(' ')*   
	     ('P'|'p')('rice')(' ')*   |
	     ('P'|'p')('ercent')(' ')*
	     ('C'|'c')('hange')(' ')*  ;
ARE     :    ('A'|'a')('re')(' ')*     ;
TAG     :           '@'(' ')*          ;  // the symbol for the tag
NAP     :     ('W'|'w')('ait')(' ')*   ;  // for the sleeping
TIME    :('M'|'m')('inute')('s')?(' ')*|
	 ('H'|'h')('our')('s')?(' ')*  |
	 ('S'|'s')('econd')('s')?(' ')*|
                 ('S'|'s')(' ')*       |
                 ('M'|'m')(' ')*       |
                 ('H'|'h')(' ')*       ;
IF      :   ('I'|'i')('F'|'f')(' ')*   ;
IS      :   ('I'|'i')('S'|'s')(' ')*   ;
USE     :     ('U'|'u')('se')(' ')*    ;  // goto functionality 
COMP    :('G'|'g')('reater than')(' ')*|
          ('L'|'l')('ess than')(' ')*  |
           ('E'|'e')('qual to')(' ')*  ;
WRT     :    ('W'|'w')('rite')(' ')*   ;
NUM	:        [0-9]+(' ')*          ;
WS	:  [ \t\r]+ -> skip      ;  // skip spaces and tabs
END     :         '\n'           ; 
DAY     :      ('D'|'d')('ay')(' ')*   ;
DATE    :        ' '             ;  // how to date stuff
WRDS	: [a-zA-Z0-9!$%&;:{}~_'()]+(' ')*;  // match any word. Untested
                                    // might need STOC to only match X char





/*
 * startRule will need to be expanded based on more viable sentences
 * an idea I have is keeping it the same but changing the parser
 * rules to encompass more?
 */
startRule: ('\n')*(firstkey)+ EOF;

/*
 * Parser Rules
 *
 * - Parser rules are lower case
 * - Rules end in a semi-colon ';'
 */


                //Tag will consume multiple tags if nothing is in between two tags
                //Which will arbitrarily build the tree downwards
firstkey	: GET  timekey        | 
                  TAG  tagkey	      |
                  NAP waitkey         |
                  IF   ifkey          |
                  WRT wrtkey          |
		  WRDS listkey        |
                  USE tagkey          |
		  COMET tagkey        ;

//for building a list of stocknames
listkey         : (IS|ARE) stockname     ;

//for pulling information on specific stocks
//get function (timestuff) for stocks looking into
timekey         : (NUM DAY)? funcKey  ;
funcKey         : FUNC secondkey   ; 
secondkey	: FOR stockname    ;
stockname	: (WRDS)+ (usekey)?
		  (END+|EOF) stockname?;

//gets the name for a goto then looks for another Token after a newline
//@beginning
tagkey          : (WRDS+|GET|FOR|NAP
		  |NUM|TIME|COMP|TAG
		  |DAY|IS|USE|COMET
                  |WRT|ARE|FUNC)* 
		  (END+|EOF)       ;

//looks for a number and time increment
//wait 30 m
waitkey         : (NUM+ (TIME|DAY))+ (END+|EOF)   ; //number followed by incriment followed by newline

//set up a if true run this
//if stock equal to num
ifkey           : GET numkey       ;
numkey          : (NUM DAY)? iffunc   ;
iffunc          : FUNC iskey       ;
iskey           : FOR  isstock     ;
isstock         : WRDS IS compkey ;
compkey         : COMP dec firstkey? ; //usekey is a goto

//for the moving to specific spot in the program
usekey          : USE tagkey   ;

//for outputting text
wrtkey          : (WRDS|GET|FOR|NAP
		  |NUM|TIME|COMP|TAG
		  |DAY|IS|USE|COMET|WRT
                  |ARE|DOT|COMET|IF|FUNC)* 
		  (END+|EOF) ; //one word or no words followed by a newline


dec             : NUM* (DOT NUM+)? ;













