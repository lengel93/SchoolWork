import os
import glob
import datetime
import time

###############################################################################

''' 
    Special printing flags passed into each function:
    flags[0] = verbose
    flags[1] = interactive
    flags[2] = print 
'''
def renameFile ( allDirFiles, oldfile, newfile, flags ):
    '''
    Author: Kenneth Petry
    Description:
        Changes the name of a given file.  oldfile is the file's current name coming into
        the function.  newfile is the name to change it to.  The function will handle the
        -i, -v, and -p flags.
    
    Variables:
        oldfile = old file name
        newfile = what to change the file name to
        flags = list of boolean printing flags
    '''
    
    # if -v or -p, print the old and new file names
    if flags[0] == True or flags[2] == True:
        print ("File:", oldfile, "->", newfile)
        
        # quit if -p is set
        if flags[2] == True:
            return True
        
    # if -i, ask user before changing file name
    if flags[1] == True:
        print ( "Change file:", oldfile, "->", newfile, " y/N > ", end ="")
        YorN = input()
        YorN.lower()
        
        # if user says yes, change the name
        if YorN == "y" or YorN == "yes":
            try:
                os.rename ( oldfile, newfile )
            except:
                print ( "Unable to rename: ", oldfile )
                return False
                
    else: # if user did not specify -i, just change the file
        try:
            os.rename ( oldfile, newfile )
        except:
            print ( "Unable to rename: ", oldfile)
            return False
    
    return True
###############################################################################
        
def removeFile ( fileName, flags ):
    '''
    Author: Kenneth Petry
    Description:
        Removes a specified file.  It will handle the -i, -v, and -p flags.
    
    Variables:
        fileName = name of the file to remove
        flags = list with flag booleans
    '''
    # if -v or -p is set, print the file to delete
    if flags[0] == True or flags[2] == True:
        print ("File:", fileName )
        
        # if -p is set, quit the function
        if flags[2] == True:
            return
        
    # if -i, ask user to delete file
    if flags[1] == True:
        print ( "Delete file:", fileName, " y/N > ", end ="")
        YorN = input()
        YorN.lower()
        
        # if user agrees, delete the file
        if YorN == "y" or YorN == "yes":
            try:
                os.remove ( fileName )
            except:
                print ("Unable to remove: ", fileName )
                
    else:   # if no -i, remove the file
        try:
            os.remove ( fileName )
        except:
            print ( "Unable to remove: ", fileName)

###############################################################################

def setTime ( fileName, newtime, flags ):
    '''
    Author: Kenneth Petry
    Description:
        Changes the creation and modification date/time on a file.
        This function handles the flags being set, such as the interactive, verbose, 
        and print flags.
        
    Variables:
        fileName = name of the file to change
        newtime = new time to set on each file
        flags = the boolean list of printing flags
    '''

    # get old time and convert to usefull form
    oldtime = os.path.getmtime ( fileName )
    oldtime = datetime.datetime.fromtimestamp ( oldtime )
    
    # if -v or -p, print the new and old times
    if flags[0] == True or flags[2] == True:
        print ("\n\tFile:", fileName, "\nChange date/time:", oldtime, "->", newtime )
        
        # if -p, quit the function
        if flags[2] == True:
            return
    # if -i, ask if user wants to change
    if flags[1] == True:
        print ( "\n\tFile:", fileName, "\nChange date/time:", oldtime, "->", newtime, " y/N > ", end ="")
        YorN = input()
        YorN.lower()
        
        # if the user says yes, change the time
        if YorN == "y" or YorN == "yes":                
            try:
                os.utime( fileName, ( newtime.timestamp(), newtime.timestamp() ) )
            except:
                print ( "Unable to change date/time on: ", fileName)
            
    else: # if the user did not want an interactive mode, change the time
                        
        try:
            os.utime( fileName, ( newtime.timestamp(), newtime.timestamp() ) )
        except:
            print ( "Unable to change date/time on: ", fileName)
                
###############################################################################
