#include "analyst.hpp"

Analyst::Analyst(Trader trader)
{
    openPositions = trader.getOpenPositions();
    Stock temp;
    for(auto x: trader.getAvailablePositions())
    {
        symbols.push_back(x.second.symbol);

        temp.symbol = x.second.symbol;
        temp.h_high = x.second.h_high;
        temp.h_low = x.second.h_low;
        temp.h_start = x.second.h_start;
        temp.h_end = x.second.h_end;
        temp.h_volume = x.second.h_volume;
        availablePositions.push_back(temp);
    }
}

map<string, double> Analyst::getAverages(int range)
{
    map<string, double> averages;
    double sum = 0.0;
    int currIndex;
    
    for (auto x: availablePositions)
    {
        if (x.h_end.size())
        {
            for (int i = range; i > 0; i--)
            {
                currIndex = x.h_end.size() - i;
                
                sum += x.h_end[currIndex];
            }
        }
        
        else
            averages[x.symbol] = 0.00;
        
        averages[x.symbol] = (sum / range);
        sum = 0.0;
    }
    
    return averages;
}

map<string, vector<double>> Analyst::getMovingAverages(unsigned int period, int range)
{
    map<string, vector<double>> averages;
    int currIndex;
    double sum = 0.0;
    
    vector<double> queue;
    
    for (auto x: availablePositions)
    {
        if (x.h_end.size())
        {
            for (int i = range; i > 0; i--)
            {
                currIndex = x.h_end.size() - i;
                queue.push_back(x.h_end[currIndex]);

                if (queue.size() > period)
                    queue.erase(queue.begin());

                if (queue.size() == period)
                {
                    for (auto x: queue)
                        sum += x;

                    averages[x.symbol].push_back(sum / period);
                    sum = 0.0;
                }
            }
        }
    }
    
    return averages;
}

map<string, double> Analyst::getCurrentPrices()
{
    map<string, double> prices;
    
    for (auto x: availablePositions)
    {
        if (x.h_end.size())
            prices[x.symbol] = x.h_end[0];
    }
    
    return prices;
}

int Analyst::numToPurchase(double price, double cash, double percent)
{
    double toSpend = (cash * percent);
    return (int) toSpend / price;
}

void Analyst::updatePortfolio(Trader trader)
{
    openPositions = trader.getOpenPositions();
}
