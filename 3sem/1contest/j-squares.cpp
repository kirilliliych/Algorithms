#include <cassert>
#include <iostream>


struct matrix_t
{
    int value  = 0;
    int result = 0;
};


void DumpMatrix(matrix_t **matrix, int size)
{
    for (int i = 1; i < size + 1; ++i)
    {
        for (int j = 1; j < size + 1; ++j)
        {
            std::cout << "(" << matrix[i][j].value << ", " << matrix[i][j].result << ") ";
        }

        std::cout << std::endl;
    }
}

int Min(int v1, int v2, int v3)
{
    if (v2 < v1)
    {
        v1 = v2;
    }
    if (v3 < v1)
    {
        v1 = v3;
    }

    return v1;
}


int main()
{
    int N = 0;
    std::cin >> N;
    matrix_t **matrix = new matrix_t *[N + 2];
    for (int i = 0; i < N + 2; ++i)
    {
        matrix[i] = new matrix_t[N + 2];
        for (int j = 1; i > 0 && i < N + 1 && j < N + 1; j++)
        {
            std::cin >> matrix[i][j].value;
        }
    }
    
    for (int i = 1; i < N + 1; ++i)
    {
        for (int j = 1; j < N + 1; ++j)
        {
            if (matrix[i][j].value != 0)
            {
                matrix[i][j].result = Min(matrix[i - 1][j].result, 
                                          matrix[i][j - 1].result, 
                                          matrix[i - 1][j - 1].result) + 1;
            }
        }
    }

    int max = 0;
    for (int i = 1; i < N + 1; ++i)
    {
        for (int j = 1; j < N + 1; ++j)
        {
            if (max < matrix[i][j].result)
            {
                max = matrix[i][j].result;
            }
        }
    }
    std::cout << max << std::endl;

    for (int i = 0; i < N + 2; ++i)
    {
        delete [] matrix[i];
    }
    delete [] matrix;

    return 0;
}