#include <cassert>
#include <iostream>
#include <stack>
#include <vector>


#define aboba std::cout << "aboba " << __LINE__ << std::endl;


void find_euler_cycle(int init_index, std::vector<std::vector<int>> &matrix)
{
    assert(init_index >= 0);

    std::stack<int> stack{};
    std::stack<int> path{};
    stack.push(init_index);
    path.push(init_index);
    
    while (!stack.empty())
    {
        int cur_index = stack.top();
        bool edge_exists = false;
        for (int i = 0; i < matrix[cur_index].size(); ++i)
        {
            if (matrix[cur_index][i] == 1)
            {
                matrix[cur_index][i] = 0;
                stack.push(i);
                edge_exists = true;

                break;
            }
        }
        if (!edge_exists)
        {
            stack.pop();
            path.push(cur_index);
        }
    }

    int first = path.top();
    path.pop();
    int second = path.top();
    path.pop();
    while (!path.empty())
    {
        std::cout << first + 1 << " " << second + 1 << std::endl;

        first = second;
        second = path.top();
        path.pop();
    }
}


int main()
{
    int N = 0;
    int A = 0;
    std::cin >> N >> A;

    std::vector<std::vector<int>> matrix{N};
    for (int i = 0; i < N; ++i)
    {
        matrix.resize(N);
        for (int j = 0; j < N; ++j)
        {
            int value = 0;
            std::cin >> value;
            matrix[i].push_back(value);
            if (i != j)
            {
                matrix[i][j] = 1 - matrix[i][j];
            }
        }
    }
    
    find_euler_cycle(A - 1, matrix);

    return 0;
}