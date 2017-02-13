import os
import glob
import datetime
import IOfunct
import re
import sys

###############################################################################

def lower(fnames,files, flags):
    '''
    Author: Lyndon Engel, Kenneth Petry
    Description:
        Turns all letters lower case in the file names of specified files
    
    Variables:
        fnames = files in the directory
        files = files to change the name of
        flags = boolean flags for pirinting -i, -v, and -p
    
    '''
    newfiles = []
    for f in files: 
        flag = IOfunct.renameFile ( fnames, f, f.lower(), flags )
        if flag == True:
            newfiles += [ f.lower() ]
        else:
            newfiles += [f]
            
    return newfiles
###############################################################################

def upper(fnames, files, flags): #Same as lower but makes the names uppercase
    '''
    Author: Lyndon Engel, Kenneth Petry
    Description:
        Turns all letters upper case in the file names of specified files.
        Does not change the .extentions
    
    Variables:
        fnames = files in the directory
        files = files to change the name of
        flags = boolean flags for pirinting -i, -v, and -p
    
    '''
    newfiles = []
    for f in files:
        #Makes sure the file extension doesnt become uppercase
        newName = f[ : f.find('.') ].upper() + f[ f.find('.') : ] 
        flag = IOfunct.renameFile ( fnames, f, newName, flags )
        
        if flag == True:
            newfiles += [ newName ]
        else:
            newfiles += [f]
        
    return newfiles
###############################################################################
    
def trim(fnames,files,number,flags):
    '''
    Author: Lyndon Engel, Kenneth Petry
    Description:
        This function trims the elements from a file name. If you want to remove
        elements from the front of the name you input a positive number, and if 
        you want to remove from the back you input a negative number. If the
        number of elements you designate to remove is bigger than file name it 
        will leave either the front or back charcter depending on if its removing
        from the front or back. 
    
    Variables:
        fnames = files in the directory
        files = files to change the name of
        number = number of elements you want to remove
        flags = boolean flags for pirinting -i, -v, and -p
    
    '''
    newfiles = []
    
    for filename in files:  #same start as the lower and upper
        #if filename in files:
        dot = int(filename.index('.')) #keeps track of where the '.' is in the file name
        
        if number > 0: # if the number is positive remove from front
            if number >= dot: #if the number is greater than the position of the dot then some math is required so it doesnt delete the whole file
            
                diff = number - dot
                number = number - (diff + 1)
                flag = IOfunct.renameFile( fnames, filename,filename[number:],flags)
                
                if flag == True:
                    temp = filename[number:]
                else:
                    temp = filename
                newfiles += [temp]
                
            else: #otherwise it just removes how ever many charcters from the front
                flag = IOfunct.renameFile(fnames, filename,filename[number:],flags)
                
                if flag == True:
                    temp = filename[number:]
                else:
                    temp = filename
                newfiles += [temp]

                
        else: #if the number isnt positive it removes charcters from the back
        
            back = filename[dot:] #creates a string of the '.txt,.pdf,...'
            front = filename[:dot] #creates a string of just the file name
            diff = int((dot - 1) + number) #checks the difference in character wanting to remove and length of file name
            
            if diff < 0: #if the difference is negative it will only keep the front charcter
                flag = IOfunct.renameFile(fnames, filename,front[0]+back,flags)
                
                if flag == True:
                    temp = front[0]+back
                else:
                    temp = filename
                newfiles += [temp]

                
            else:#otherwise it removes how ever many characters from the back of the filename
                flag = IOfunct.renameFile(fnames, filename,front[:number]+back,flags)
                
                if flag == True:
                    temp = front[:number] + back
                else:
                    temp = filename
                newfiles += [temp]

    return newfiles
###############################################################################
def replace(fnames,old,new,flags):
    '''
    Author: Lyndon Engel
    Description:
        Uses the Regular expression operations to find a pattern match for the users
        givin file name pattern. If it can find files in the directory matching the 
        users file name pattern it will store them into oldfiles list. After that is
        done it uses the re.sub expressions to rename each of the files in the list using
        the users given new file pattern and stores them into a newfile list. Then runs
        are rename function.
    
    Variables:
        fnames = files in the directory
        old = users file pattern that they want to change
        new = users new file pattern
        flags = boolean flags for pirinting -i, -v, and -p
    
    '''
    oldfiles = []
    newfiles = []
    count = 0
    returnFiles = []
    '''
    Checks all files in the directory to see if they match the users pattern
    If a file does match the pattern its stored in a list.
    '''
    for i in fnames:
        match = re.match(old,i) 
        if match:
            oldfiles.append(i)

    #uses the list made above to rename the files
    for i in oldfiles:
        newfiles.append(re.sub(old,new,i)) 
 
    #After all file renames are done we then pass them into are rename function
    for f in oldfiles:
            flag = IOfunct.renameFile(fnames, f,newfiles[count],flags)
            
            if flag == True and count < len(newfiles ):
                returnFiles += [newfiles[count]]
            else:
                returnFiles += [f]
            count += 1    
    return returnFiles
###############################################################################

def strFromInt ( number, numDigits ):
    '''
    Author: Kenneth Petry
    Description:
        Gets a string with the number specified from an integer.  The number will takes
        the number of digits specified in numDigits.  Leading 0's will be applied if needed.
        Helper funciton for numberFiles.
        
    variables:
        number = number to convert into a string
        numDigits = number of digits, will apply leading 0's if needed
    '''
    result = ""
    while number > 0:   # number assumed to fit in the number of digits specified
        result = str( number % 10 ) + result    # get last digit and add to string
        number = number // 10   # shift the number (base 10) to the right
        numDigits -= 1
    
    # if leading 0's are needed,
    while numDigits > 0:
        result = '0' + result
        numDigits -= 1
        
    return result

def numberFiles ( dirFiles, files, inString, flags ):
    ''' 
    Author: Kenneth Petry
    Description:
        Function to handle a -n flag set.  Renames files counting from 1, to the number 
        of files specified to change.  It will not modify the .extention at the end of the name.
    
    variables:
        dirFiles = files in the directory
        files = files to rename
        inString = string stated on the command with nested #'s
        flags = boolean flags for printing -v, -p, and -i
    '''
    count = 0
    newfiles = [ ]
    
    i = inString.find( '#' )
    prePounds = inString[ : i ]
    
    numDigits = i
    while i < len(inString) and inString[i] == '#':
        i += 1
        
    numDigits = i - numDigits
    
    postPounds = inString [ i :  ]
    
    for f in files:
        #if f in dirFiles:
        count += 1
        finalName = prePounds + strFromInt ( count, numDigits ) + postPounds #+ f[ f.find('.') : ] 
        flag = IOfunct.renameFile ( dirFiles, f, finalName, flags )
        
        if flag == True:
            newfiles += [finalName]
        else:
            newfiles += [f]
            
    return newfiles
###############################################################################

def deleteFiles ( dirFiles, files, flags ):
    '''
    Author: Kenneth Petry
    Description:
        Function handler for the -d flag.  It will delete the files specified.
    
    variables:
        dirFiles = files in the directory
        files = files to delete
        flags = boolean variables for printing -i, -v, and -p
    '''
    for f in files:
        IOfunct.removeFile ( f, flags )

###############################################################################
def touchFile ( dirFiles, files, flags ):
    '''
    Author:Kennenth Petry
    Description:
    Updates the file timestamp with the current time/date.
    
    Variables:
    dirFiles = files in the directory
    files = files to change
    flags = boolean printing flags
    '''

    now = datetime.datetime.now()
    for f in files:
        IOfunct.setTime ( f, now, flags )

###############################################################################

def changeDate ( dirFiles, files, newdate, flags ):
    '''
    Author: Kenneth Petry
    Description:
        Changes the date stamp on a file
    
    Variables:
        dirFiles = files in the directory
        files = files to change 
        newdate = new date to set on each file
        flags = boolean printing variables for -i, -p, and -v
    '''
    # DDMMYYYY
    
    # get last 4 digits
    year = newdate % 10000
    newdate = newdate // 10000 # shift number (base 10) so MM is right justified
    
    # retrieve last 2 digits and shift
    month = newdate % 100
    newdate = newdate // 100
    
    # 2 digits left are the day
    day = newdate
    
    for f in files:
        #if f in dirFiles:
        olddate = os.path.getmtime( f )
        olddate = datetime.datetime.fromtimestamp ( olddate )
       
        newFullDate = datetime.datetime ( year, month, day, olddate.hour, olddate.minute, olddate.second )

        IOfunct.setTime ( f, newFullDate, flags )

###############################################################################

def changeTime ( dirFiles, files, newtime, flags ):
    '''
    Author: Kenneth Petry
    Descriptoin:
        changeTime is called if the -T flag is set.  It will change the time on files
        to a specified time.
    
    Variables:
        dirFiles = all files in the directory - used to make sure the files requested to 
            change are actually in the current directory
        files = list of files to change
        newtime = time to set each file's modification time
        flags = flags with the -i, -v, and -p settings
    '''
    # HHMMSS
    
    # get the last 2 digits in the new time
    second = newtime % 100
    newtime = newtime // 100
    
    # get another 2 digits for minutes
    minute = newtime % 100
    newtime = newtime // 100
    
    # what is left is the seconds
    hour = newtime
    
    for f in files:
        #if f in dirFiles:
        oldtime = os.path.getmtime ( f )
        oldtime = datetime.datetime.fromtimestamp ( oldtime )
            
        newFullTime = datetime.datetime ( oldtime.year, oldtime.month, oldtime.day, hour, minute, second )
        #print ( newFullTime )
        IOfunct.setTime ( f, newFullTime, flags )

###############################################################################        
#Grabs all file names/file designations from command line and stores them in Mfiles
def getfname(files):
    '''
    Author: Lyndon Engel
    Descriptoin:
        Uses glob to grab the files the user wants to change from the directory.
        This is mainly used for when the user wants to change all files with the
        same file extension. 
    
    Variables:
        files = list of files to change
    '''
    Mfiles = []
    for i in files:
        Mfiles += glob.glob(i)
    return Mfiles