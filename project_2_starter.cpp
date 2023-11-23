#include <iostream>
#include <string>
#include <vector>
#include <fstream>

bool verify(std::vector<std::pair<int,int> > candidates, int limit)
{
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
    // best = res[0];
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



int main()
{   
    std::ifstream ipFile("input.txt");
    std::ofstream out("output.txt");
    int arrSize, cost;
    std::string stcks;
    std::vector<int> companies;
    std::vector<std::pair<int, int> > stocks, res;
    
    while(ipFile >> arrSize >> stcks >> cost)
    {
        // Extract digits from stcks string
        for(int i = 0; i < stcks.size(); ++i)
        {
            if(isdigit(stcks.at(i)))
            {
                if(isdigit(stcks.at(i+1)))
                {
                    companies.push_back(stoi(stcks.substr(i, i+1)));
                    ++i;
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

        // Generate the correct sample output HERE

        for(int i = 0; i < res.size(); ++i)
        {
            std::cout << "[" << res[i].first << ", " << res[i].second << "] ";
        }
        std::cout << std::endl;

        res.clear();
        stocks.clear();
        companies.clear();
    }
    return 0;
}