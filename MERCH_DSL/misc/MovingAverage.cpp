#include "../procedure.hpp"
//THIS ALGORITHM GOES THROUGH THE STOCKS AND LOOKS FOR ANY INSTANCES WHERE THE
//MOVING AVERAGE OF THE LAST 5 DAYS IS GREATER THAN THE LAST 20 DAYS AND BUYS
//THE STOCKS IN THE ORDER FROM HIGHEST PERCENT INCREASE TO LOWEST PERCENT
//INCREASE. ANY INSTANCES WHERE THE 5 DAY AVERAGE IS LOWER THAN THE 20 DAY
//AVERAGE SELLS A STOCK.
struct holder
{
    double percent;
    std::string stock;
};

bool compare(holder left, holder right)
{
    return left.percent < right.percent;
}

void procedure(Trader trader)
{
    Analyst analyst(trader);
    Logger logger;

    //get current end of day prices
    map<string, double> curr = analyst.getCurrentPrices();

    //get average for past 5 days
    map<string, double> fiveDay = analyst.getAverages(5);
    
    //get average for past 20 days
    map<string, double> twentyDay = analyst.getAverages(20);

    vector<holder> list;

    //sell any owned stock in which it is below a specified percentage
    for (auto x: analyst.openPositions)
    {
        if(curr[x.symbol] != 0.0 && curr[x.symbol] != 1.0)
        {
            double diff = ((fiveDay[x.symbol] - 
                twentyDay[x.symbol])/twentyDay[x.symbol])*100;
            if (diff < 0)
            {
                trader.sell(x, x.count);
                logger.addLog(false, x.symbol, x.count, curr[x.symbol],
                    std::to_string(diff) + " moving average.");
            }
        }
    }

    for (auto x: analyst.symbols)
    {
        if(curr[x] != 0.0 && curr[x] != 1.0)
        {
            double diff = ((fiveDay[x] - twentyDay[x])/twentyDay[x])*100;
            if ( diff > 0)
            {   //if meets criteria, add to list
                holder temp;
                temp.percent = diff;
                temp.stock = x;
                list.push_back(temp);
            }
        }
    }
    
    //sort the percentages
    std::sort(list.begin(),list.end(),compare);

    //go from highest percent to least, buying any that have enough funds for
    for(int i = list.size() - 1; i >= 0; i--)
    {
        int count = analyst.numToPurchase(trader.getStockPrice(list[i].stock),
                                    trader.getAccountCash(), 0.03);
                                    
        if (!trader.buy(list[i].stock, count))
            logger.addLog(true, list[i].stock, count, curr[list[i].stock],
                std::to_string(list[i].percent) + " moving average.");
    }
    
    //calculate account value
    analyst.updatePortfolio(trader);
    double value = 0;
    for (auto x: analyst.openPositions)
    {
        value += curr[x.symbol] * x.count;
    }
    
    value += trader.getAccountCash();
    
    logger.printLogs("TradingLog.txt", value);
    
    return;
}
