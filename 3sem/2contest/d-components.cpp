#include <iostream>
#include <stack>
#include <vector>


enum Color
{
    WHITE,
    GREY,
    BLACK
};


struct Vertex
{
    int component_index = -1;
    Color color         = WHITE;
};


int main()
{
    int N = 0;
    int M = 0;
    std::cin >> N >> M;

    std::vector<std::vector<int>> graph{};
    graph.resize(N + 1);
    
    for (int i = 0; i < M; ++i)
    {
        int v1 = 0;
        int v2 = 0;
        std::cin >> v1 >> v2;

        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    std::vector<Vertex> vertices{};
    vertices.resize(N + 1);
    int cur_component = 0;

    std::stack<Vertex *> stack{};
    for (int i = 1; i < N + 1; ++i)
    {
        if (vertices[i].color != WHITE)
        {
            continue;
        }

        ++cur_component;

        stack.push(&vertices[i]);

        while (!stack.empty())
        {
            Vertex *cur_vertex = stack.top();
            int cur_vertex_index = cur_vertex - &vertices[0];
            stack.pop();
            cur_vertex->color = GREY;
            cur_vertex->component_index = cur_component;

            for (int i = 0; i < graph[cur_vertex_index].size(); ++i)
            {
                int cur_index = graph[cur_vertex_index][i];
                if (vertices[cur_index].color == WHITE)
                {
                    stack.push(&vertices[cur_index]);
                }
            }

            cur_vertex->color = BLACK;
        }
    }

    std::cout << cur_component << std::endl;
    for (int i = 1; i < vertices.size(); ++i)
    {
        std::cout << vertices[i].component_index << " ";
    }

    return 0;
}