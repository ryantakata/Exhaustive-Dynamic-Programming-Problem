#include <iostream>
#include <string>
#include <vector>
#include <fstream>

bool verify(std::vector<std::pair<int,int> > candidates, int limit)
{
    // Verifies the candidate is valid by checking 
    // the cost does not exceed the limit
    int totalCost = 0;
    for(int i = 0; i < candidates.size(); ++i)
    {
        totalCost += candidates[i].second;
    }
    if(totalCost <= limit)
    {
        return true;
    }
    return false;
}

int combined_stocks(std::vector<std::pair<int, int> > candidates)
{
    // Combines the total stock number
    int totalStocks = 0;
    for(int i = 0; i < candidates.size(); ++i)
    {
        totalStocks += candidates[i].first;
    }
    return totalStocks;
}

void generate_instances(std::vector<std::pair<int, int> > stockPrices, std::vector<std::pair<int, int> > subset, 
                        std::vector<std::vector<std::pair<int, int> > >& res, int index)
{
    // Base Case: Adds subset into resolution vector when end of vector is reached
    if (index == stockPrices.size())
    {
        for(auto i : subset)
        {
            res.push_back(subset);
        }
        return;
    }

    // Includes current element in subset
    subset.push_back(stockPrices[index]);
    generate_instances(stockPrices, subset, res, index + 1);

    // Excludes current element from subset
    subset.pop_back();
    generate_instances(stockPrices, subset, res, index + 1);
}

std::vector<std::pair<int, int> > stock_maximization(std::vector<std::pair<int, int> > companyStcks, int limit)
{
    std::vector<std::vector<std::pair<int, int> > > res;
    std::vector<std::pair<int, int> > subset, best;

    // Generate all the subsets
    generate_instances(companyStcks, subset, res, 0);
    // Replace best variable with best subset
    for(int i = 0; i < res.size(); ++i)
    {
        if(verify(res[i], limit))
        {
            if(best.empty() || combined_stocks(res[i]) > combined_stocks(best))
            {
                best = res[i];
            }
        }
    }
    return best;
}

void printOutput(std::vector<std::pair<int, int> > res, std::vector<std::pair<int, int> > stocks,
                 int totalCost, int totalStocks, int cost, std::ofstream& output)
{
    for(int i = 0; i < res.size(); ++i)
    {
        totalStocks += res[i].first;
        totalCost += res[i].second;
    }
    std::cout << totalStocks << " # ";
    output << totalStocks << " # ";
    for(int i = 0; i < res.size(); ++i)
    {
        if(++i != res.size())
        {
            --i;
            std::cout << res[i].first << "+";
            output << res[i].first << "+";
        }
        else
        {
            --i;
            std::cout << res[i].first;
            output << res[i].first;
        }
    }
    std::cout << " at index ";
    output << " at index ";
    for(int i = 0; i < res.size(); ++i)
    {
        for(int k = 0; k < stocks.size(); ++k)
        {
            if(res[i] == stocks[k])
            {
                std::cout << k << ", ";
                output << k << ", ";
            }
        }
    }
    std::cout << "sum of the values at these indices = ";
    output << "sum of the values at these indices = ";
    int totCost = 0;
    for(int i = 0; i < res.size(); ++i)
    {
        totCost += res[i].second;
        if(++i != res.size())
        {
            --i;
            std::cout << res[i].second << "+";
            output << res[i].second << "+";
        }
        else
        {
            --i;
            std::cout << res[i].second << " = " << totCost;
            output << res[i].second << " = " << totCost;
        }
    }
    std::cout << " <= " << cost;
    output << " <= " << cost;
    std::cout << std::endl;
    output << std::endl;
}

int main()
{   
    std::ifstream ipFile("input.txt");
    std::ofstream out("output.txt");
    int arrSize, cost, totalStocks = 0, totalCost = 0;
    std::string stcks;
    std::vector<int> companies;
    std::vector<std::pair<int, int> > stocks, res;
    
    while(ipFile >> arrSize >> stcks >> cost)
    {
        // Extract digits from stcks string
        for(int i = 0; i < stcks.size(); ++i)
        { 
            int substrTrack = 0, strTrack = i;
            if(isdigit(stcks.at(i)))
            {
                if(isdigit(stcks.at(i+1)))
                {
                    while(isdigit(stcks.at(strTrack)))
                    {
                        ++substrTrack;
                        ++strTrack;
                    }
                    companies.push_back(stoi(stcks.substr(i, i+substrTrack)));
                    i += substrTrack;
                }
                else
                {
                    companies.push_back(stcks[i] - '0');
                }
            }
        }
        
        // Put the stock and cost pairs into the stocks vector
        for(int i = 0; i < companies.size(); ++i)
        {
            std::pair<int, int> p1;
            p1.first = companies[i];
            p1.second = companies[i+1];
            stocks.push_back(p1);
            ++i;
        }
    
        // Gets the combination of companies with highest stock value possible
        res = stock_maximization(stocks, cost);

        printOutput(res, stocks, totalCost, totalStocks, cost, out);

        res.clear();
        stocks.clear();
        companies.clear();
    }
    return 0;
}