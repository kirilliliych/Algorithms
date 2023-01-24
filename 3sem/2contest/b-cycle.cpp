#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <vector>


enum DFSColor
{
    WHITE, 
    GREY,
    BLACK
};


struct Vertex
{
    int color   = WHITE;
    bool marked = true;
};


int main()
{
    unsigned N = 0;
    unsigned M = 0;
    std::cin >> N >> M;

    std::vector<std::vector<int>> graph{N + 1};
    for (int i = 0; i < M; ++i)
    {
        int v1 = 0;
        int v2 = 0;
        std::cin >> v1 >> v2;

        graph[v1].push_back(v2);
    }
    
    std::vector<Vertex> vertices{N + 1};
    std::vector<int> path{};
    std::stack<int> stack{};
    bool cycle_exists = false;

    int *previous = new int[N + 1];
    for (int i = 0; i < N; ++i)
    {
        previous[i] = -1;
    }
    for (int vertex_index = 1; vertex_index < N + 1; ++vertex_index)
    {
        if (cycle_exists)
        {
            break;
        }

        if (vertices[vertex_index].color != WHITE)
        {
            continue;
        }

        stack.push(vertex_index);
        //std::cout << "pushed new component from " << vertex_index << std::endl;

        while (!stack.empty())
        {
            if (cycle_exists)
            {
                break;
            }

            int cur_vertex_index = stack.top();
            vertices[cur_vertex_index].color = GREY;
            //std::cout << cur_vertex_index << " is now grey" << std::endl;

            if (vertices[cur_vertex_index].marked)
            {
                vertices[cur_vertex_index].marked = false;

                for (int i = 0; i < graph[cur_vertex_index].size(); ++i)
                {
                    int neighbour_index = graph[cur_vertex_index][i];
                    if (vertices[neighbour_index].color == WHITE)
                    {
                        stack.push(neighbour_index);
                        //std::cout << "pushed as neighbour: " <<  neighbour_index << std::endl;
                        previous[neighbour_index] = cur_vertex_index;

                    }
                    else if (vertices[neighbour_index].color == GREY)
                    {
                        cycle_exists = true;
                        int cycle_last_vertex_index  = cur_vertex_index;
                        int cycle_first_vertex_index = neighbour_index;
                        //std::cout << "last: " << cycle_last_vertex_index << " first: " << 
                        while (cycle_last_vertex_index != previous[cycle_first_vertex_index])
                        {
                            path.push_back(cycle_last_vertex_index);
                            cycle_last_vertex_index = previous[cycle_last_vertex_index];
                        }

                        break;
                    }
                }
            }
            else
            {
                vertices[cur_vertex_index].color = BLACK;
                stack.pop();
                //std::cout << "popped" << std::endl;
            }
        }
    }

    if (cycle_exists)
    {   
        std::cout << "YES" << std::endl;

        std::reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); ++i)
        {
            std::cout << path.at(i) << " ";
        }
    }
    else 
    {
        std::cout << "NO" << std::endl;
    }

    delete [] previous; 

    return 0;
}