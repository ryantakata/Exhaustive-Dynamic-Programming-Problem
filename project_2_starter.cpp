#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// bool verifier(int instance, int candidate)
// {

// }

// int stock_combinations()
// {

// }

// int stock_maximization(int cost)
// {
    
// }



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
        for(int i = 0; i < stocks.size(); ++i)
        {
            std::cout << stocks[i].first << " " << stocks[i].second << "\n";
        }

        companies.clear();
    }
    return 0;
}