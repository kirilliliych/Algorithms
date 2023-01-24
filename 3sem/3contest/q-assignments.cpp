#include <cassert>
#include <climits>
#include <iostream>
#include <vector>


void recalc_min_val(const std::vector<std::vector<long long>> &cells,
                    const std::vector<long long> &row_potential,
                    const std::vector<long long> &col_potential,
                    const std::vector<bool> &used,
                    const long long cur_row,
                    const long long cur_col,
                    std::vector<long long> &min_val_for_potential,
                    std::vector<long long> &result,
                    long long *min_elem,
                    long long *min_col)
{
    long long N = used.size();

    for (long long j = 1; j < N; ++j)
    {
        if (!used[j])
        {
            long long cur_val = cells[cur_row][j] - row_potential[cur_row] - col_potential[j];
            if (cur_val < min_val_for_potential[j])
            {
                min_val_for_potential[j] = cur_val;
                result[j] = cur_col;
            }
            if (min_val_for_potential[j] < *min_elem)
            {
                *min_elem = min_val_for_potential[j];
                *min_col = j;
            }
        }
    }
}

void recalc_potentials(const std::vector<long long> &parsoch_array,
                        const std::vector<bool> &used,
                        const long long min_elem,
                        std::vector<long long> &row_potential,
                        std::vector<long long> &col_potential,
                        std::vector<long long> &min_val_for_potential)
{
    long long N = used.size();

    for (long long j = 0; j < N; ++j)
    {
        if (used[j])
        {
            row_potential[parsoch_array[j]] += min_elem;
            col_potential[j] -= min_elem;
        }
        else
        {
            min_val_for_potential[j] -= min_elem;
        }
    }
}

std::vector<long long> hungarian_algorithm(const std::vector<std::vector<long long>> &cells)
{
    long long N = cells.size();
    std::vector<long long> row_potential(N, 0);
    std::vector<long long> col_potential(N, 0);
    std::vector<long long> result(N, 0);
    std::vector<long long> parsoch_array(N, 0);

    for (long long i = 1; i < N; ++i) 
    {
        std::vector<long long> min_val_for_potential(N, INT_MAX);
        std::vector<bool> used(N, false);
        parsoch_array[0] = i;
        long long cur_col = 0;

        bool been_in_a_while = false;
        while (!been_in_a_while || (parsoch_array[cur_col] != 0))
        {
            been_in_a_while = true;

            long long cur_row = parsoch_array[cur_col];
            long long min_elem = INT_MAX;
            long long min_col = 0;
            used[cur_col] = true;

            recalc_min_val(cells,
                           row_potential,
                           col_potential,
                           used,
                           cur_row,
                           cur_col,
                           min_val_for_potential,
                           result,
                           &min_elem,
                           &min_col);
            
            recalc_potentials(parsoch_array,
                              used,
                              min_elem,
                              row_potential,
                              col_potential,
                              min_val_for_potential);

            cur_col = min_col;
        }

        bool recalc_parsoch = false;
        while (!recalc_parsoch || (cur_col != 0))
        {
            recalc_parsoch = true;

            long long min_col = result[cur_col];
            parsoch_array[cur_col] = parsoch_array[result[cur_col]];
            cur_col = min_col;
        }
    }

    for (long long i = 1; i < N; ++i)
    {
        result[parsoch_array[i]] = i;
        result[0] += cells[parsoch_array[i]][i];
    }

    return result;
}

int main()
{
    long long N = 0;
    std::cin >> N;

    std::vector<std::vector<long long>> cells(N + 1, std::vector<long long>(N + 1, 0));
    for (long long i = 1; i < N + 1; ++i)
    {
        for (long long j = 1; j < N + 1; ++j)
        {
            std::cin >> cells[i][j];
        }
    } 

    std::vector<long long> result = hungarian_algorithm(cells);
    std::cout << result[0] << std::endl;
    for (long long i = 1; i < N + 1; ++i)
    {
        std::cout << i << ' ' << result[i] << std::endl;
    }

    return 0;
}