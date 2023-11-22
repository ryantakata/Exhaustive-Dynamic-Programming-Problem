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

int combined_cost(std::vector<std::pair<int, int> > candidates)
{
    int totalCost = 0;
    for(int i = 0; i < candidates.size(); ++i)
    {
        totalCost += candidates[i].second;
    }
    return totalCost;
}

int stock_maximization(std::vector<std::pair<int, int> > companyStcks, int limit)
{
    std::pair<int, int> best;

    // Figure out how to generate all the possible combinations and find the best.
    // Look at knapsack for reference
    for(int i = 0; i < companyStcks.size(); ++i)
    {
        
    }
     
}



int main()
{   
    std::ifstream ipFile("input.txt");
    std::ofstream out("output.txt");
    int arrSize, cost;
    std::string stcks;
    std::vector<int> companies;
    std::vector<std::pair<int, int> > stocks;
    
    while(ipFile >> arrSize >> stcks >> cost)
    {
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
        for(int i = 0; i < companies.size(); ++i)
        {
            std::pair<int, int> p1;
            p1.first = companies[i];
            p1.second = companies[i+1];
            stocks.push_back(p1);
            ++i;
        }
        // Print stock pairs
        for(int i = 0; i < stocks.size(); ++i)
        {
            std::cout << stocks[i].first << " " << stocks[i].second << "\n";
        }
        companies.clear();
    }
    return 0;
}