import requests
import time

def getDaysArray(stock):
    '''
    Function Name:
        def getDaysArray(stock)

    Description:
        Gets an array of all the days for a stock as it appears on the HTML of
        the nasdaq historical page for the provided stock. Has additional
        precautions to save the results from the last operation, so if the same
        stock is called twice, it won't pull the HTML the second time. However
        if it has been 15 minutes since the last pull, it will pull again.

    Arguments:
        stock - stockname to look for

    Returns:
        an array of all the days on the historical website as they appear in
        the HTML.

    Todos/Known Bugs:
        None Known
    '''
    #if this was called last time / was recent (save runtime)
    if (stock != getDaysArray.prevStock or
          time.time() - getDaysArray.timeStamp > 60):
        #clear array and set new stock for static variables
        del getDaysArray.prevList[:]
        getDaysArray.prevStock = stock

        #get the HTML text from nasdaq for the specified stock
        url = "http://www.nasdaq.com/symbol/"+stock+"/historical"
        html = requests.get(url).text

        #goes to the point in the HTML where the historical data starts
        html = html.split("The closing daily official volumes represented")[1]

        #seperate values by day
        getDaysArray.prevList = html.split("<tr>")

        #save the current time
        getDaysArray.timeStamp = time.time()

    return getDaysArray.prevList
getDaysArray.prevStock = ""
getDaysArray.timeStamp = time.time()
getDaysArray.prevList = []

def getDayValue(day, value, days):
    '''
    Function Name:
        def getDayValue(day, value, days)

    Description:
        Gets a specific value for a specified day as indicated by their order
        in the HTML.

    Arguments:
        day - the number of stock market days ago (1 is today)
        value - which value to obtain as it appears in the order in the HTML.
        1 is date, 2 is open, 3 is high, 4 is low, 5 is close, 6 is volume
        days - the collection of days to select from. Obtained from
        getDaysArray()

    Returns:
        the requested value

    Todos/Known Bugs:
        None Known
    '''
    #seperate different values for that day
    values = days[day].split("<td>")

    #get the closing price
    val = values[value].split("</td>")[0]

    #remove whitespace and commas
    val = ''.join(val.split())
    val = val.replace(',','')

    #special case for days where market is not open
    if val == "":
        values = days[day+1].split("<td>")
        val = values[value].split("</td>")[0]
        val = ''.join(val.split())
        val = val.replace(',','')
    return float(val)

def percentIncrease(stock, long, short):
    '''
    Function Name:
        def percentIncrease(stock, long, short)

    Description:
        finds the percent increase of the moving average for a short amount of
        days as specified, in relation to the moving average of a long amount of
        days as specified.

    Arguments:
        stock - the stock name to find the percent increase for
        long - the long amount of days, should be longer than short
        short - the short amount of days, should be shorter than long

    Returns:
        percent increase

    Todos/Known Bugs:
        None Known
    '''
    longAvg = movingAverage(stock,long)
    if longAvg == float("inf"):
        return longAvg
    shortAvg = movingAverage(stock,short)
    pct =  100 * (shortAvg - longAvg) / longAvg

    return pct

def movingAverage(stock, time):
    '''
    Function Name:
        def movingAverage(stock, time)

    Description:
        Gets the moving average for the specified stock for the past number of
        days as specified. (average of the past x stock days)

    Arguments:
        stock - stock to find the moving average
        time - number of days to find the moving average for

    Returns:
        moving average

    Todos/Known Bugs:
        None Known
    '''
    sum = 0.0
    movAvg = float("inf")
    try:
        days = getDaysArray(stock)

        #perform for specified number of days
        #start at 2 to skip over incomplete days, start at last open day (not today)
        for x in range(2,time+2):
            num = getDayValue(x, 5, days)
            sum = sum + num
            movAvg = sum / time
    except:
        pass

    return movAvg

#GETS OPENING PRICE FOR A STOCK FOR TODAY OR MOST RECENT DAY
def getOpenPrice(stock,day):
    '''
    Function Name:
        def getOpenPrice(stock,day)

    Description:
        Gets the opening price for a specified stock on a specified day

    Arguments:
        stock - the stock to get the opening price for
        day - how many stock market days ago

    Returns:
        The specified opening price for a stock.

    Todos/Known Bugs:
        None Known
    '''
    try:
        days = getDaysArray(stock)
        return getDayValue(day,2,days)
    except:
        return float("inf")

#GETS HIGH PRICE FOR A STOCK FOR TODAY OR MOST RECENT DAY
def getHighPrice(stock, day):
    '''
    Function Name:
        def getOpenPrice(stock,day)

    Description:
        Gets the high price for a specified stock on a specified day

    Arguments:
        stock - the stock to get the high price for
        day - how many stock market days ago

    Returns:
        The specified high price for a stock.

    Todos/Known Bugs:
        None Known
    '''
    try:
        days = getDaysArray(stock)
        return getDayValue(day,3,days)
    except:
        return float("inf")

#GETS LOW PRICE FOR A STOCK FOR TODAY OR MOST RECENT DAY
def getLowPrice(stock, day):
    '''
    Function Name:
        def getLowPrice(stock,day)

    Description:
        Gets the low price for a specified stock on a specified day

    Arguments:
        stock - the stock to get the low price for
        day - how many stock market days ago

    Returns:
        The specified low price for a stock.

    Todos/Known Bugs:
        None Known
    '''
    try:
        days = getDaysArray(stock)
        return getDayValue(day,4,days)
    except:
        return float("inf")

#GETS CLOSING PRICE FOR A STOCK FOR TODAY OR MOST RECENT DAY
def getClosePrice(stock,day):
    '''
    Function Name:
        def getClosePrice(stock,day)

    Description:
        Gets the closing price for a specified stock on a specified day

    Arguments:
        stock - the stock to get the closing price for
        day - how many stock market days ago

    Returns:
        The specified closing price for a stock.

    Todos/Known Bugs:
        None Known
    '''
    try:
        days = getDaysArray(stock)
        return getDayValue(day,5,days)
    except:
        return float("inf")

#GETS VOLUME FOR A STOCK FOR TODAY OR MOST RECENT DAY
def getVolume(stock,day):
    '''
    Function Name:
        def getVolume(stock,day)

    Description:
        Gets the volume for a specified stock on a specified day

    Arguments:
        stock - the stock to get the volume for
        day - how many stock market days ago

    Returns:
        The specified volume for a stock.

    Todos/Known Bugs:
        None Known
    '''
    try:
        days = getDaysArray(stock)
        return int(getDayValue(day,6,days))
    except:
        return float("inf")


'''EXAMPLES OF USAGES OF ALL THE OPERATIONS
pct = percentIncrease("AAPL", 20, 5)
print(pct)
open = getOpenPrice("AAPL")
print(open)
close = getClosePrice("AAPL")
print(close)
high = getHighPrice("AAPL")
print(high)
low = getLowPrice("AAPL")
print(low)
volume = getVolume("AAPL")
print(volume)'''
