#include <cassert>
#include <iostream>
#include <vector>


struct Conversion
{
    int from         = -1;
    int to           = -1;
    double rate      = -1;
    double comission = -1;
};


bool system_abuse_success(const std::vector<Conversion> &conversions, 
                          const int currencies_quantity,
                          const double money,
                          const int start_currency_index)
{
    std::vector<double> max_money(currencies_quantity, -1);
    max_money[start_currency_index] = money;

    for (int i = 0; i < currencies_quantity * currencies_quantity; ++i)
    {
        for (int j = 0; j < conversions.size(); ++j)
        {
            if ((max_money[conversions[j].from] - conversions[j].comission > 0) &&
                (max_money[conversions[j].to] < (max_money[conversions[j].from] - conversions[j].comission) * conversions[j].rate))
            {
                max_money[conversions[j].to] = (max_money[conversions[j].from] - conversions[j].comission) * conversions[j].rate;
            }
        }        
    }

    if (max_money[start_currency_index] > money)
    {
        return true;
    }

    return false;
}

int main()
{
    int N = 0;
    int M = 0;
    int S = 0;
    double V = 0;
    std::cin >> N >> M >> S >> V;

    std::vector<Conversion> conversions{};
    for (int i = 0; i < M; ++i)
    {
        Conversion temp1;
        Conversion temp2;
        std::cin >> temp1.from >> temp1.to;
        temp2.from = temp1.to;
        temp2.to   = temp1.from;
        --temp1.from;
        --temp1.to;
        --temp2.from;
        --temp2.to;
        std::cin >> temp1.rate >> temp1.comission;
        std::cin >> temp2.rate >> temp2.comission;
        conversions.push_back(temp1);
        conversions.push_back(temp2);
    }

    if (system_abuse_success(conversions, N, V, S - 1))
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }

    return 0;
}