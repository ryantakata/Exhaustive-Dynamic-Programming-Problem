#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

void stock_dp(int limit, std::vector<int>& stocks, std::vector<int>& cost, int index, std::ofstream& output)
{
    // 2D array for Dynamic Programming Storage
    std::vector<std::vector<int> > res(index+1, std::vector<int>(limit+1, 0));

    // DP Solution
    for(int i = 0; i < (index + 1); ++i)
    {
        for(int k = 0; k < (limit + 1); ++k)
        {
            if(i == 0 || k == 0)
            {
                res[i][k] = 0;
            }
            else if(cost[i-1] <= k)
            {
                res[i][k] = std::max(stocks[i-1] + res[i-1][k - cost[i-1]], res[i-1][k]);               
            }
            else
            {
                res[i][k] = res[i-1][k];
            }
        }
    }

    // Printing output
    int total = res[index][limit];
    std::cout << total << " # ";
    output << total << " # ";

    // Back track to find the companies that were included
    std::vector<int> stck, stckVal, indc;
    int l = limit;
    for(int i = index; i > 0 && total > 0; --i)
    {
        if(total != res[i-1][limit])
        {
            indc.push_back(i-1);                // Stores the indices of companies in a vector
            stck.push_back(stocks[i-1]);        // Stores the stocks associated with companies in a vector
            stckVal.push_back(cost[i-1]);       // Stores the value associated with companies in a vector
            total = total - stocks[i-1];
            limit = limit - cost[i-1];
        }
    }

    // Prints the stocks associated with companies
    for(int i = stck.size()-1; i >= 0; --i)
    {
        if(--i < 0)
        {
            ++i;
            std::cout << stck[i];
            output << stck[i];
        }
        else
        {
            ++i;
            std::cout << stck[i] << "+";
            output << stck[i] << "+";
        }
    }
    std::cout << " at index ";
    output << " at index ";
    // Prints the indices of companies
    for(int i = indc.size() - 1; i >= 0; --i)
    {
        std::cout << indc[i] << ", ";
        output << indc[i] << ", ";
    }
    std::cout << "sum of the values at these indices = ";
    output << "sum of the values at these indices = ";
    // Prints the values associated with companies
    int totalCost = 0;
    for(int i = stckVal.size()-1; i >= 0; --i)
    {
        totalCost += stckVal[i];
        if(--i < 0)
        {
            ++i;
            std::cout << stckVal[i] << " = " << totalCost;
            output << stckVal[i] << " = " << totalCost;
        }
        else
        {
            ++i;
            std::cout << stckVal[i] << "+";
            output << stckVal[i] << "+";
        }
    }
    std::cout << " <= " << l;
    output << " <= " << l;
    std::cout << std::endl;
    output << std::endl;
}

int main()
{   
    std::ifstream ipFile("input.txt");
    std::ofstream out("output.txt");
    int arrSize, cost, nums;
    std::string stcks;
    std::vector<int> companies, stocks, value;

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
            stocks.push_back(companies[i]);
            value.push_back(companies[i+1]);
            ++i;
        }

        stock_dp(cost, stocks, value, arrSize, out);

        stocks.clear();
        value.clear();
        companies.clear();

    }
    return 0;
}