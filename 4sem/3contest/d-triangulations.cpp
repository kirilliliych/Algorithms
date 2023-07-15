#include <algorithm>
#include <iostream>
#include <vector>


namespace modulo
{
    const int64_t MODULO = 1e9 + 7;
}


template<typename Type>
class Point2d
{
    template<typename AnotherType>
    friend class Point2d;

public:
//---------------------------------------------------------------------------------
    Point2d()
      : Point2d(0, 0)
    {}

    Point2d(Type x, Type y)
      : x_(x),
        y_(y)
    {}
//---------------------------------------------------------------------------------
    Type x() const
    {
        return x_;
    }

    Type y() const
    {
        return y_;
    }

    void set_x(Type x)
    {
        x_ = x;
    }

    void set_y(Type y) 
    {
        y_ = y;
    }

    template<typename AnotherType>
    void operator +=(const Point2d<AnotherType> &another_point)
    {
        x_ += static_cast<Type> (another_point.x_);
        y_ += static_cast<Type> (another_point.y_);
    }

    template<typename AnotherType>
    void operator -=(const Point2d<AnotherType> &another_point)
    {
        x_ -= static_cast<Type> (another_point.x_);
        y_ -= static_cast<Type> (another_point.y_);
    }

    template<typename AnotherType>
    Point2d<Type> operator +(const Point2d<AnotherType> &another_point) const
    {      
        return {x_ + static_cast<Type> (another_point.x_),
                y_ + static_cast<Type> (another_point.y_)
               };
    }
    
    template<typename AnotherType>
    Point2d<Type> operator -(const Point2d<AnotherType> &another_point) const
    {
        return {x_ - static_cast<Type> (another_point.x_),
                y_ - static_cast<Type> (another_point.y_)
               };
    }

    Point2d<Type> operator -() const
    {
        return {x_,
                y_
               };
    }

    template<typename AnotherType>
    bool operator ==(const Point2d<AnotherType> &another_point) const
    {
        return (x_ == static_cast<Type> (another_point.x_)) && (y_ == static_cast<Type> (another_point.y_));
    }

    template<typename AnotherType>
    bool operator !=(const Point2d<AnotherType> &another_point) const
    {
        return !(*this == another_point);
    }

    template<typename AnotherType>
    bool operator <=(const Point2d<AnotherType> &another_point) const
    {
        return x_ == static_cast<Type> (another_point.x_) ? y_ <= static_cast<Type> (another_point.y_) :
                                                            x_ <= static_cast<Type> (another_point.x_);
    }

    template<typename AnotherType>
    bool operator <(const Point2d<AnotherType> &another_point) const
    {
        return x_ == static_cast<Type> (another_point.x_) ? y_ < static_cast<Type> (another_point.y_) :
                                                            x_ < static_cast<Type> (another_point.x_);
    }

    template<typename AnotherType>
    bool operator >=(const Point2d<AnotherType> &another_point) const
    {
        return x_ == static_cast<Type> (another_point.x_) ? y_ >= static_cast<Type> (another_point.y_) :
                                                            x_ >= static_cast<Type> (another_point.x_);
    }

    template<typename AnotherType>
    bool operator >(const Point2d<AnotherType> &another_point) const
    {
        return x_ == static_cast<Type> (another_point.x_) ? y_ > static_cast<Type> (another_point.y_) :
                                                            x_ > static_cast<Type> (another_point.x_); 
    }

private:
//-----------------------------------Variables-------------------------------------
    Type x_;
    Type y_;
};


template<typename Type, typename AnotherType>
int64_t skew_product(const Point2d<Type> &p1, const Point2d<AnotherType> &p2)
{
    return (p1.x() * static_cast<Type> (p2.y()) - p1.y() * static_cast<Type> (p2.x()));
}

template<typename Type>
std::istream &operator >>(std::istream &in, Point2d<Type> &point)
{
    Type temp_x = 0;
    Type temp_y = 0;
    std::cin >> temp_x >> temp_y;
    point.set_x(temp_x);
    point.set_y(temp_y);

    return in;
}


int64_t get_triangulations_quantity(const std::vector<Point2d<int64_t>> &polygon_vertices)
{
    int64_t vertices_quantity = static_cast<int64_t> (polygon_vertices.size());
    std::vector<std::vector<int64_t>> start_end_vertices_dp(vertices_quantity, std::vector<int64_t>(vertices_quantity, 0));

    for (int64_t chain_length_in_vertices = 1; chain_length_in_vertices < vertices_quantity; ++chain_length_in_vertices)
    {
        for (int64_t chain_start = 0; chain_start < vertices_quantity - chain_length_in_vertices; ++chain_start)
        {
            int64_t chain_end = chain_start + chain_length_in_vertices;
            if (chain_length_in_vertices == 1)
            {
                start_end_vertices_dp[chain_start][chain_end] = 1;
            }
            else
            {
                for (int64_t chain_cur_pos = chain_start + 1; chain_cur_pos <  chain_end; ++chain_cur_pos)
                {
                    int64_t skew_prod = skew_product(polygon_vertices[chain_cur_pos] - polygon_vertices[chain_start],
                                                  polygon_vertices[chain_cur_pos] - polygon_vertices[chain_end]);
                    if (skew_prod < 0)
                    {
                        start_end_vertices_dp[chain_start][chain_end] += start_end_vertices_dp[chain_start][chain_cur_pos] *
                                                                         start_end_vertices_dp[chain_cur_pos][chain_end] % modulo::MODULO;
                        start_end_vertices_dp[chain_start][chain_end] %= modulo::MODULO;
                    }
                }
            }
        }
    }

    return start_end_vertices_dp[0][vertices_quantity - 1];
}


int main()
{
    int n = 0;
    std::cin >> n;

    std::vector<Point2d<int64_t>> polygon_vertices(n);
    std::cin >> polygon_vertices[0];
    int64_t orientation_indicator = 0;
    for (int i = 1; i < n; ++i)
    {
        std::cin >> polygon_vertices[i];
        orientation_indicator += skew_product(polygon_vertices[i - 1], polygon_vertices[i]);
    }
    orientation_indicator += skew_product(polygon_vertices[n - 1], polygon_vertices[0]);
    if (orientation_indicator < 0)
    {
        std::reverse(polygon_vertices.begin(), polygon_vertices.end());
    }

    std::cout << get_triangulations_quantity(polygon_vertices);


    return 0;
}
