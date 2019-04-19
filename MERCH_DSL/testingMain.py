"""
Program: Complilers Semester Project - Team MERCH
Author: Joe Ceritelli, Lyndon Engel, Jimmy Hinker, Ryan McCaskell, Jeff Ross
Class: CSC 492 Topics: Compilers
Instructor: Dr. Hinker
Date: 12/05/2018


Description:
@TODO


Compilation instructions:
@TODO

Usage:
@TODO

Known bugs/missing features:
@TODO

"""
import ParserV2Listener
import ParserV2Lexer
import ParserV2Parser
from operations import *
from progInfo import *
from antlr4 import *
import time
import sys


def getAllStocks(stockname, stocks):
    '''
    Function Name:
        getAllStocks(stockname, stocks)

    Description:
        gets all the stocks for a given get operation. Goes through recursively
        to check all the lines that have been matched with the operation,
        calling on stockname, and adds them to a list to be returned.

    Arguments:
        stockname - portion of the tree containing the stock names
        stocks - list of stocks collected so far

    Returns:
        stocks - list of all stocks

    Todos/Known Bugs:
        None Known
    '''
    if stockname is not None:
        for temp in stockname.WRDS():
            stocks.append(temp.getText().replace(" ", ""))
        stocks = getAllStocks(stockname.stockname(), stocks)
        return stocks
    else:
        return stocks

def handleIf(startCond, varHold):
	'''
    Function Name:
        def handleIf(startCond, varHold)

    Description:
        Handles the if command. Takes in a line started by "if" and calls
        a function to handle the get statement included. Once the value is 
        returned it compares with the value included in the if statement
        and depending on whether its true or false, handles the following
        statement appropriately. If the function is a use, it returns the 
        location for the program to jump to, otherwise returns nothing.

    Arguments:
        startCond - Section of the tree containing the information for the
                    if statement.

        varHold - a progInfo class holding all variables and gotos

    Todos/Known Bugs:
        None Known
	'''
	ck = startCond.ifkey().numkey().iffunc().iskey().isstock().compkey()
	result = handleIfGet(startCond.ifkey(), varHold)
	op = ck.COMP().getText().lower().replace(" ","")
	compVal = float(ck.dec().getText().replace(" ",""))
	next = ck.firstkey()
	if result == float("inf"):
		return 

	if result == float("-inf"):
		return

	cmpResult = False
	if op == "greaterthan":
		cmpResult = result > compVal
	if op == "lessthan":
		cmpResult = result < compVal
	if op == "equalto":
		cmpResult = result == compVal

	if cmpResult != False:

		if next.GET() != None:
			handleGet(next, varHold)

		if next.TAG() != None:
			print("Improper tag location, skipping...")

		if next.NAP() != None:
			handleSleep(next)
	
		if next.IF() != None:
			handleIf(next, varHold)

		if next.WRT() != None:
			printOut(next.wrtkey())
	
		if next.WRDS() != None:
			print("Invalid operation: " + next.WRDS().getText())

		if next.USE() != None:
			tagName = next.tagkey().getText().replace('\n','')
			if varHold.getInclusion(tagName):
				val = varHold.getGoto(tagName)
				if val != None:	
					return val
			else:
				print (tagName + 'has not been defined.')	
	

def handleIfGet(startCond, varHold):
	'''
    Function Name:
        def handleIf(startCond, varHold)

    Description:
        Handles the get command being sent in, using the tree with the
        structure coming from the if tree.

    Arguments:
        startCond - Section of the tree containing the information for the
                    statement.

        varHold - a progInfo class holding all variables and gotos

    Todos/Known Bugs:
        None Known
	'''
	func = startCond.numkey().iffunc().FUNC().getText().lower().replace(" ","")
	stock = startCond.numkey().iffunc().iskey().isstock().WRDS().getText().replace(" ","")
	days = 30

	if varHold.getVar(stock) != float("inf"):
		stock = varHold.getVar(stock)

	if isinstance(stock,list):
		if len(stock) > 1:
			print("too many stocks provided for if statement")
			return(float("-inf"))
		else:
			stock = str(stock[0])

	if startCond.numkey().NUM() != None:
		days = int(startCond.numkey().NUM().getText())
	
	val = 0.0

	if func == "movingaverage":
		val = movingAverage(stock,days)
	
	elif func == "percentchange":
		val = percentIncrease(stock, 20, 5)

	elif func == "highprice":
		val = getHighPrice(stock, 1)

	elif func == "lowprice":
		val = getLowPrice(stock, 1)

	elif func == "openingprice":
		val = getOpenPrice(stock, 1)

	elif func == "closingprice" or func == "price":
		val = getClosePrice(stock, 1)

	elif func == "volume":
		val = getVolume(stock, 1)
	
	if val == float("inf"):
		print(str(stock) + " is not a valid stock")
		return val

	return val

def handleGet(startCond, varHold):
    '''
    Function Name:
        def handleGet(startCond)

    Description:
        Handles the get command. Takes in a line started by "get" and goes
        through to find all the stocks linked with that get statement. Once
        found it goes through to identify a valid operation, which it then
        performs that operation on those sets of stocks and outputs their
        results.

    Arguments:
        startCond - Section of the tree containing the information for the
                    get statement.

        varHold - a progInfo class holding all variables and gotos

    Todos/Known Bugs:
        None Known
    '''
    stocks = []
    func = startCond.timekey().funcKey().FUNC().getText().lower().replace(" ", "")
    try:
        stocks = getAllStocks(startCond.timekey().funcKey().secondkey().stockname(), stocks)
    except:
        return
    i = 0
    while i < len(stocks):
        if varHold.getVar(stocks[i]) != float("inf"):
            for var in varHold.getVar(stocks[i]):
                stocks.append(var.replace(" ", ""))
            stocks.remove(stocks[i])
	else:
	    i = i + 1
    #get number of days
    if startCond.timekey().NUM() != None:
        days = int(startCond.timekey().NUM().getText())
        daysFound = True
    else:
        daysFound = False

    if func == "movingaverage":
        if not daysFound:
            days = 30
        for stock in stocks:
            avg = movingAverage(stock,days)
            if avg == float("inf"):
                print str(stock) + " is not a valid stock"
            else:
                print(str(days) + " day Moving average for "
                    + str(stock) + " is " + str(avg))

    if func == "percentchange":
        for stock in stocks:
            pct = percentIncrease(stock, 20, 5)
            if pct == float("inf"):
                print str(stock) + " is not a valid stock"
            else:
                print "Percent Change for " + str(stock) + " is " + str(pct)

    if not daysFound:
        days = 1
    for stock in stocks:
        for i in range(2,days+2):
            if days == 1:
                i = 1
            if func == "highprice":
                prc = getHighPrice(stock, i)
                if prc == float("inf"):
                    print str(stock) + " is not a valid stock"
                    break
                elif daysFound:
                    print("High price " + str(i - 1) + " day(s) ago for "
                        + str(stock) + " was " + str(prc))
                else:
                    print "High Price for " + str(stock) + " is " + str(prc)

            elif func == "lowprice":
                prc = getLowPrice(stock, i)
                if prc == float("inf"):
                    print str(stock) + " is not a valid stock"
                    break
                elif daysFound:
                    print("Low price " + str(i - 1) + " day(s) ago for "
                        + str(stock) + " was " + str(prc))
                else:
                    print "Low Price for " + str(stock) + " is " + str(prc)

            elif func == "openingprice":
                prc = getOpenPrice(stock, i)
                if prc == float("inf"):
                    print str(stock) + " is not a valid stock"
                    break
                elif daysFound:
                    print("Opening price " + str(i - 1) + " day(s) ago for "
                        + str(stock) + " was " + str(prc))
                else:
                    print "Opening Price for " + str(stock) + " is " + str(prc)

            elif func == "closingprice" or func == "price":
                prc = getClosePrice(stock, i)
                if prc == float("inf"):
                    print str(stock) + " is not a valid stock"
                    break
                elif func == "price":
                    if daysFound:
                        print("Closing price " + str(i - 1) + " day(s) ago for "
                            + str(stock) + " was " + str(prc))
                    else:
                        print "Price for " + str(stock) + " is " + str(prc)
                else:
                    if daysFound:
                        print("Closing price " + str(i - 1) + " day(s) ago for "
                            + str(stock) + " was " + str(prc))
                    else:
                        print "Closing Price for " + str(stock) + " is " + str(prc)

            elif func == "volume":
                prc = getVolume(stock, i)
                if prc == float("inf"):
                    print str(stock) + " is not a valid stock"
                    break
                elif daysFound:
                    print("Volume " + str(i - 1) + " day(s) ago for "
                        + str(stock) + " was " + str(prc))
                else:
                    print "Volume for " + str(stock) + " is " + str(prc)
    print("-----")


def handleSleep(startCond):
    '''
    Function Name:
        def handleSleep(startCond)

    Description:
        This function handles a sleep command. The sleep command handles
        Hours, minutes and seconds. Upon receiving the sleep command,
        program execution is haulted until for the duration given.

    Arguments:
        startCond - portion of the tree with the information for the sleep
                    statement

    Returns:
        None

    Todos/Known Bugs:
        None Known
    '''
    runTime = 0
    for i in range(0, len(startCond.waitkey().TIME())):
        unit = startCond.waitkey().TIME(i).getText().lower().replace(" ", "")

        if unit == "second" or unit == "seconds":
            runTime += int(startCond.waitkey().NUM(i).getText())

        elif unit == "minute" or unit == "minutes":
            runTime += 60*int(startCond.waitkey().NUM(i).getText())

        elif unit == "hour" or unit == "hours":
            runTime += 3600*int(startCond.waitkey().NUM(i).getText())
    time.sleep(runTime)


def parseTree(expr):
    '''
    Function Name:
        def parseTree(expr)

    Description:
        @TODO

    Arguments:
        expr - @TODO

    Returns:
        Returns 0 upon completion

    Todos/Known Bugs:
        None Known
    '''

    #This is for checking outputs are correct
    startCond = []
    for child in expr.firstkey():
    #this takes all firstkeys pointers and saves to startCond array
        startCond.append(child)

    #make a loop for startCond
    start = 0
    variable = progInfo()
    i = start

    #run through the program and get all the USE tag locations set
    while i < len(startCond):
        if startCond[i].TAG() is not None:
            variable.addGoto(startCond[i].tagkey().getText().replace('\n',''), i)
        i += 1

    # Run through the program a second time and execute the statements
    i = start
    while i < len(startCond):
        if startCond[i].GET() is not None:
            handleGet(startCond[i], variable)

        elif startCond[i].TAG() is not None:
            pass

        elif startCond[i].NAP() is not None:

            handleSleep(startCond[i])

        elif startCond[i].IF() is not None:
			val = handleIf(startCond[i], variable)
			if val is not None:
				i = val

        elif startCond[i].WRT() is not None:
            x = printOut(startCond[i].wrtkey())

            pass
                 
        elif startCond[i].WRDS() is not None:
            stocklist = []

            #Grabs string of stocknames example (MicrosoftAppl)
            removeString = startCond[i].listkey().getText()

            #Grabs string that contains list name and stocks (MystocksMicrosoftAppl)
            currentString = startCond[i].getText()

            #removes stock names from current string (Mystocks)
            name = currentString.replace(removeString,"")

            #loops through stocks and adds them to a list
            for stock in startCond[i].listkey().stockname().WRDS():
                stocklist.append(stock.getText())

            #hashes the stocklist with the name as the key
            variable.addVar(name,stocklist)
            pass

        elif startCond[i].COMET() is not None:
            pass

        elif startCond[i].USE() is not None:
            tagName = startCond[i].tagkey().getText().replace('\n','')
            if variable.getInclusion(tagName):
                i = variable.getGoto(tagName)
                continue
            else:
                print (tagName + 'has not been defined.')
                break

        else:
# @TODO: fix error message
            print "Invalid Command"
        i += 1


    return 0



def printOut(node):
    '''
    Function Name:
        def printOut(node)

    Description:
        This is specifically for the write function. This function prints the text
        of a given node.

    Arguments:
        node - passed in as startCond[i].wrtkey()

    Returns:
        Returns 0 upon completion

    Todos/Known Bugs:
        1. This might break bunch of tests and things because you added ' ' on every rule,
                further testing required
    '''
    #node.getText should print out all words inside the wrtkey rule
    print node.getText(),
    return 0


def main():
    '''
    Function Name:
        def main()

    Description:
        This function initalizes the MERCH interpreter. The lexical analyzer is called
        and creates a tree from the input merch program provided by the user. The tree
        is analyzed and the appropriate program execution of the merch program is
        completed.

    Arguments:
        None

    Returns:
        None

    Todos/Known Bugs:
        None Known
    '''

    if len(sys.argv) > 1:
        input = FileStream(sys.argv[1])
        lexer = ParserV2Lexer.ParserV2Lexer(input)
        stream = CommonTokenStream(lexer)
        parser = ParserV2Parser.ParserV2Parser(stream)
        tree = parser.startRule()
        eof = parseTree(tree)
    else:
        lexer = ParserV2Lexer.ParserV2Lexer(StdinStream())
        stream = CommonTokenStream(lexer)
        parser = ParserV2Parser.ParserV2Parser(stream)
        tree = parser.startRule()
        eof = parseTree(tree)



if __name__ == '__main__':
    main()
