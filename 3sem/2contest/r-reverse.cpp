#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>


int count_reverses(std::string &perm1, std::string &perm2, int perm_size)
{
    std::unordered_map<std::string, int> perm1_dist;
    std::unordered_map<std::string, int> perm2_dist;
    
    std::queue<std::string> q1{};
    std::queue<std::string> q2{};

    perm1_dist[perm1] = 0;
    perm2_dist[perm2] = 0;
    q1.push(perm1);
    q2.push(perm2);

    while (!q1.empty() && !q2.empty())
    {
        std::string cur_perm1 = q1.front();
        std::string cur_perm2 = q2.front();
        int dist1 = perm1_dist[cur_perm1];
        int dist2 = perm2_dist[cur_perm2];
        
        if (dist1 <= dist2)
        {
            q1.pop();
            for (int i = 0; i < perm_size - 1; ++i)
            {
                for (int j = i + 1; j < perm_size; ++j)
                {
                    std::string changed_perm1 = cur_perm1;
                    std::reverse(changed_perm1.begin() + i, changed_perm1.begin() + j + 1);
 
                    if (perm2_dist.find(changed_perm1) != perm2_dist.end())
                    {
                        return dist1 + perm2_dist[changed_perm1] + 1;
                    }
                    else if (perm1_dist.find(changed_perm1) == perm1_dist.end())
                    {
                        perm1_dist[changed_perm1] = dist1 + 1;
                        q1.push(changed_perm1);
                    } 
                }
            }
        }
        else
        {
            q2.pop();
            for (int i = 0; i < perm_size - 1; ++i)
            {
                for (int j = i + 1; j < perm_size; ++j)
                {
                    std::string changed_perm2 = cur_perm2;
                    std::reverse(changed_perm2.begin() + i, changed_perm2.begin() + j + 1);

                    if (perm1_dist.find(changed_perm2) != perm1_dist.end())
                    {
                        return dist2 + perm1_dist[changed_perm2] + 1;
                    }
                    else if (perm2_dist.find(changed_perm2) == perm2_dist.end())
                    {
                        perm2_dist[changed_perm2] = dist2 + 1;
                        q2.push(changed_perm2);
                    } 
                }
            }
        }
    }

    return -1;
}


int main()
{
    int N = 0;
    std::cin >> N;

    std::string perm1{};
    for (int i = 0; i < N; ++i)
    {
        int num = 0;
        std::cin >> num;
        perm1.push_back(num + '0');
    }

    std::string perm2{};
    for (int i = 0; i < N; ++i)
    {
        int num = 0;
        std::cin >> num;
        perm2.push_back(num + '0');
    }

    if (perm1 == perm2)
    {
        std::cout << "0";
        
        return 0;
    }
    
    std::cout << count_reverses(perm1, perm2, N);
    
    return 0;
}