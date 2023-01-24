#include <cassert>
#include <cfloat>
#include <cmath>
#include <iomanip>
#include <iostream>


struct Point
{
    long long x = 0;
    long long y = 0;
};


float get_square(float value)
{
    assert(std::isfinite(value));

    return value * value;
}

float get_segment_length(const Point &point1, const Point &point2)
{
    return sqrtf(get_square(point1.x - point2.x) + get_square(point1.y - point2.y));
}

float get_min_distance_for_tuple(const Point *points, float *dp, size_t cur_tuple_bit_representation, int points_arr_size)
{
    assert(points != nullptr);
    assert(dp     != nullptr);
    assert(points_arr_size > 0);

    if (cur_tuple_bit_representation == (1ull << points_arr_size) - 1)                                                  // just nothing 2 connect
    {
        return 0;
    }

    if (dp[cur_tuple_bit_representation] != FLT_MAX)                                                                    // if min distance for current tuple has already been calculated then just return it
    {
        return dp[cur_tuple_bit_representation];
    }

    float min_distance = FLT_MAX;                                                                                       // min distance for tuple was not calculated
    for (int first_point_index = 0; first_point_index < points_arr_size; ++first_point_index)
    {
        size_t first_point_bit_checker = 1ull << first_point_index;
        
        if ((cur_tuple_bit_representation & first_point_bit_checker) == 0)                                              // if first point is not already in some segment
        {
            for (int second_point_index = first_point_index + 1; second_point_index < points_arr_size; ++second_point_index)
            {
                size_t second_point_bit_checker = 1ull << second_point_index;

                if ((cur_tuple_bit_representation & second_point_bit_checker) == 0)                                     // if second point is not already in some segment
                {
                    min_distance = std::min(min_distance, get_segment_length(points[first_point_index], 
                                                                             points[second_point_index])   + 
                                   get_min_distance_for_tuple(points, dp, 
                                                              cur_tuple_bit_representation + 
                                                              first_point_bit_checker      + 
                                                              second_point_bit_checker,
                                  points_arr_size));
                }
            }

            break;
        }
    }

    dp[cur_tuple_bit_representation] = min_distance;

    return min_distance;
}

int main()
{
    int N = 0;
    std::cin >> N;

    Point *points = new Point[N];
    for (int i = 0; i < N; ++i)
    {
        std::cin >> points[i].x >> points[i].y;
    }

    float *dp = new float[1 << N];
    for (size_t i = 0; i < (1 << N); ++i)
    {
        dp[i] = FLT_MAX;
    }
    
    std::cout << std::fixed << std::setprecision(3) << get_min_distance_for_tuple(points, dp, 0, N);


    delete [] dp;
    delete [] points;

    return 0;
}