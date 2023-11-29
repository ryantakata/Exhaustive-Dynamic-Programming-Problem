#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int stock_dp(int limit, std::vector<int> stocks, std::vector<int> cost, int index)
{
    std::vector<std::vector<int> > res(limit+1, std::vector<int>(index+1, 0));

    for(int i = 0; i < (index + 1); ++i)
    {
        for(int k = 0; k < (limit + 1); ++k)
        {
            if(i == 0 || k == 0)
            {
                res[i][k] = 0;
            }
            else if(stocks[i-1] <= limit)
            {
                res[i][k] = std::max(cost[i-1] + res[i-1][limit - stocks[i-1]], res[i-1][limit]);
            }
            else
            {
                res[i][k] = res[i-1][limit];
            }
        }
    }
    return res[index][limit];

}

int main()
{   
    std::ifstream ipFile("input.txt");
    //std::ofstream out("output.txt");
    int arrSize, cost;
    std::string stcks;
    std::vector<int> companies, stocks, value;

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
            stocks.push_back(companies[i]);
            value.push_back(companies[i+1]);
            ++i;
        }
        
        int fin = stock_dp(cost, stocks, value, stocks.size());
        std::cout << fin << " ";

        stocks.clear();
        value.clear();
        companies.clear();

    }
    return 0;
}