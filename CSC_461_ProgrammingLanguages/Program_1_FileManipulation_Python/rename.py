'''
Program: Programming Assignment #1: File Rename Utility in Python
Author: Lyndon Engel, Kenneth Petry
Class: CSC 461 Programming Languages
Instructor: Dr.Weiss
Date: 9/17/2016
Description: This program handles batch file renaming. How it works is the user specifies a variety 
of options from the command line and then the program applies each change to a list of filenames. 
The program currently supports the following renaming options; converting filenames to lowercase/uppercase, 
trimming characters from the front or back of a filename, replacing a filename with a new name, and renaming 
files in a sequence (i.e., file01, file02,..). On top of the programs renaming capabilities it also supports 
several other utilities those being; the ability to delete a file, change the date and time stamp to the current 
date and time, changing just the date stamps, and changing just the time stamps.  

On top of all the file capabilities it also contains several general use options. The first being a help option 
which will print out a list of every possible command, what each command does, and how to call the command. 
The second option is verbose which will print the old and new file names during processing. The third option 
‘print’ will print the old and new files names during processing but won’t actually change the file names. 
The fourth and final option is interactive, which will ask you if you want to make the change to the file 
before each name change.  
Input:
Output:
Compilation instructions:
Renaming options:
-l, --lower convert filenames to lowercase
-u, --upper convert filenames to uppercase
-t n, --trim n positive n: trim n chars from the start of each filename 
               negative n: trim n chars from the end of each filename
-r oldstring newstring, --replace oldstring newstring replace oldstring with newstring in filenames
-n countstring, --number countstring rename files in sequence using countstring #’s in countstring become numbers; 
                                            e.g., ## becomes 01,02,...
Other (non-renaming) options:
-h, --help print a help message
-v, --verbose print old and new filenames during processing
-p, --print only print old and new filenames, do not rename
-i, --interactive interactive mode, ask user prior to processing each file
-d, --delete delete files
-dt, --touch “touch” files (update date/time stamp to current date/time)
-D DDMMYYYY, --date DDMMYYYY change file datestamps
-T HHMMSS, --time HHMMSS change file timestamps

Usage: python rename.py options file1 file2 ...
Known bugs/missing features:
Modifications:
Date                Comment
9/5     uppercase,lowercase,trim
9/11    used glob to grab filenames and added argparse
9/12    added flags for verbose,interactive,print,delete
9/14    countstring,touch,date,time,replace
9/15    delete,verbose,print,interactive
9/17    added argument order handling
----    ------------------------------------------------
'''
import os
import sys
import argparse
import funct

if __name__ == "__main__":
    # define arguments passed in
    parse = argparse.ArgumentParser ( description = "Edit file names and dates" )
    parse.add_argument ( '-l', '--lower', action = "store_true", \
                        help = "convert file names to lowercase\n" )

    parse.add_argument ( '-u', '--upper', action = "store_true", \
                        help = "convert file names to uppercase")

    parse.add_argument ( '-t', '--trim', type = int, nargs =1, metavar = "n", action = "append", \
                        help = "if n > 0: remove n characters from front of string\n \
                        if n < 0: remove n characters from end of string\n")

    parse.add_argument( '-r', '--replace', nargs = 2, metavar = ( "oldstring", "newstring"), action = "append", \
                        help = " replace oldstring with newstring in file names\n")

    parse.add_argument ( '-n', '--number', nargs = 1, metavar = "'<string>##...#<string>'", action = "append", \
                        help = "rename files in sequence using the number of '#'s eg, ## -> 01, 02, 03, ...\n")
                        
    parse.add_argument ( '-v', '--verbose', action = "store_true", \
                        help = "print old and new filenames during processing\n")

    parse.add_argument ( '-p', '--print', action='store_true', \
                        help = "only prints the old and new file names.  Does not rename\n")
                        
    parse.add_argument ( '-i', '--interactive', action = "store_true", \
                        help = "Asks user prior to processing each file\n")
                        
    parse.add_argument ( '-d', '--delete', action = "store_true", \
                        help = "delete files\n")
                        
    parse.add_argument ( '-dt', '--touch', action = "store_true", \
                        help = "update time and date stamp to current time and date\n" )
                        
    parse.add_argument ( '-D', "--date", nargs = 1, metavar = "DDMMYYYY", action = "append", \
                        help = "change file date stamps\n")
                        
    parse.add_argument ( '-T', '--time', nargs = 1, metavar = "HHMMSS", action = "append", \
                        help = "change file time stamps\n")
                        
    parse.add_argument ( "files",nargs = "*", metavar = "file1, file2, ... fileN")
                        
    args = parse.parse_args()

    #########################################################################################

    args = parse.parse_args()
    path = os.getcwd() #gets current directory
    Allfiles = os.listdir(path) #creates a list of all files in directory
    Mfiles = funct.getfname(args.files) #Grabs all files that need to be modified
    cmdargs = sys.argv[1:] #creates a list of all command line arguments
    dashtracker = [] #Used to make a list of all arguments in order
    
    #Used to keep track of multiple argument calls of the same type
    trimCount = 0
    replaceCount = 0
    numberCount = 0
    dateCount = 0
    timeCount = 0
    #########################################################################################
    #Keeps track of the order the arguments are called in
    for i in cmdargs:
        if '-' in i:
            dashtracker.append(i)

    #########################################################################################
    ''' 
        flags[0] = verbose
        flags[1] = interactive
        flags[2] = print
    '''
    flags = [ False, False, False ]

    if args.verbose:
        flags[0] = True
        
    if args.interactive:
        flags[1] = True

    if args.print:
        flags[2] = True

    #########################################################################################
    for i in dashtracker: #Handles running arguments in the correct order

        Allfiles = os.listdir(path) #Make sure all file names are up to date

        if i == '-l' or i == '--lower':
            Mfiles = funct.lower(Allfiles,Mfiles, flags )

        elif i == '-u' or i == '--upper':
            Mfiles = funct.upper(Allfiles,Mfiles, flags)

        elif i == '-t' or i == '--trim':          
            Mfiles = funct.trim(Allfiles,Mfiles, args.trim[trimCount][0],flags)
            trimCount += 1

        elif i == '-r' or i == '--replace':
            Mfiles = funct.replace(Mfiles, args.replace[replaceCount][0], args.replace[replaceCount][1],flags)
            replaceCount += 1

        elif i == '-n' or i == '--number':
            Mfiles = funct.numberFiles ( Allfiles, Mfiles, args.number[numberCount][0], flags )
            numberCount += 1

        elif i == '-d' or i == '--delete':
            funct.deleteFiles ( Allfiles, Mfiles, flags )

        elif i == '-dt' or i == '--touch':
            funct.touchFile ( Allfiles, Mfiles, flags )
        
        elif i == '-D' or i == '--date':
            funct.changeDate ( Allfiles, Mfiles, int(args.date[dateCount][0]), flags )
            dateCount += 1
        
        elif i == '-T' or i == '--time':
            funct.changeTime ( Allfiles, Mfiles, int(args.time[timeCount][0]), flags )
            timeCount += 1
