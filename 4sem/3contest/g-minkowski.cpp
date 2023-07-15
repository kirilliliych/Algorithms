#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>


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
        return {-x_,
                -y_
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

template<typename Type>
double get_length(const Point2d<Type> &vector)
{
    return std::sqrt(static_cast<double> (vector.x() * vector.x() + vector.y() * vector.y()));
}

template<typename Type, typename AnotherType>
int64_t skew_product(const Point2d<Type> &v1, const Point2d<AnotherType> &v2)
{
    return static_cast<int64_t> (v1.x() * static_cast<Type> (v2.y()) - v1.y() * static_cast<Type> (v2.x()));
}

template<typename Type>
double line_segment_point_distance(const Point2d<Type> &line_segment_left_pos, const Point2d<Type> &line_segment_right_pos,
                                   const Point2d<Type> &point)
{
    Type line_segment_dx = line_segment_right_pos.x() - line_segment_left_pos.x();
    Type line_segment_dy = line_segment_right_pos.y() - line_segment_left_pos.y();
    double separation_coef = (static_cast<double> ((point.x() - line_segment_left_pos.x()) * line_segment_dx +
                                                   (point.y() - line_segment_left_pos.y()) * line_segment_dy))    /
                             (line_segment_dx * line_segment_dx + line_segment_dy * line_segment_dy);

    if (separation_coef < 0)
    {
        separation_coef = 0;
    }
    else if (separation_coef > 1)
    {
        separation_coef = 1;
    }

    double term1_sqrt = line_segment_left_pos.x() - point.x() + line_segment_dx * separation_coef;
    double term2_sqrt = line_segment_left_pos.y() - point.y() + line_segment_dy * separation_coef; 
    
    double result = sqrt(term1_sqrt * term1_sqrt + term2_sqrt * term2_sqrt);

    return result;
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


std::vector<Point2d<int64_t>> polygon_clockwise_reordering(const std::vector<Point2d<int64_t>> &polygon)
{
    int64_t polygon_points_quantity = static_cast<int64_t> (polygon.size());
    std::vector<Point2d<int64_t>> result(polygon_points_quantity);
    Point2d<int64_t> left_bottom_point = polygon[0];
    int64_t polygon_left_bottom_point_index = 0;
    for (int64_t i = 1; i < polygon_points_quantity; ++i)
    {
        if (polygon[i] < left_bottom_point)
        {
            left_bottom_point = polygon[i];
            polygon_left_bottom_point_index = i;
        }
    }

    for (int64_t i = polygon_left_bottom_point_index; i < polygon_points_quantity; ++i)
    {
        result[i - polygon_left_bottom_point_index] = polygon[i];
    }
    int64_t start_pos = polygon_points_quantity - polygon_left_bottom_point_index;
    for (int64_t i = 0; i < polygon_left_bottom_point_index; ++i)
    {
        result[start_pos + i] = polygon[i];
    }

    return result;
}

std::vector<Point2d<int64_t>> reflect_polygon(const std::vector<Point2d<int64_t>> &polygon)
{
    uint64_t polygon_size = polygon.size();
    std::vector<Point2d<int64_t>> neg_polygon(polygon_size);
    for (uint64_t i = 0; i < polygon_size; ++i)
    {
        neg_polygon[i] = -polygon[i];
    }

    return polygon_clockwise_reordering(neg_polygon);
}


std::vector<Point2d<int64_t>> get_minkowski_sum(const std::vector<Point2d<int64_t>> &polygon1,
                                                const std::vector<Point2d<int64_t>> &polygon2)
{
    std::vector<Point2d<int64_t>> pol1 = polygon1;
    std::vector<Point2d<int64_t>> pol2 = polygon2;

    int64_t pol1_size = static_cast<int64_t> (polygon1.size());
    int64_t pol2_size = static_cast<int64_t> (polygon2.size());

    pol1.emplace_back(polygon1[0]);
    pol1.emplace_back(polygon1[1]);
    pol2.emplace_back(polygon2[0]);
    pol2.emplace_back(polygon2[1]);

    int64_t pol1_index = 0;
    int64_t pol2_index = 0;
    std::vector<Point2d<int64_t>> result;
    while ((pol1_index < pol1_size) ||
           (pol2_index < pol2_size))
    {
        result.emplace_back(pol1[pol1_index] + pol2[pol2_index]);

        Point2d<int64_t> pol1_border_vector = pol1[pol1_index + 1] - pol1[pol1_index];
        Point2d<int64_t> pol2_border_vector = pol2[pol2_index + 1] - pol2[pol2_index];
        int64_t skew_prod = skew_product(pol1_border_vector, pol2_border_vector);

        if (skew_prod > 0)
        {
            ++pol1_index;
        }
        else if (skew_prod < 0)
        {
            ++pol2_index;
        }
        else
        {
            ++pol1_index;
            ++pol2_index;
        }
    }

    return result;
}


bool origin_is_inside_polygon(const std::vector<Point2d<int64_t>> &polygon)
{
    bool OX_smaller_zero = false;
    bool OX_bigger_zero  = false;
    bool OY_smaller_zero = false;
    bool OY_bigger_zero  = false;
    uint64_t minkowski_sum_size = polygon.size();
    for (uint64_t i = 0; i < minkowski_sum_size; ++i)
    {
        Point2d<int64_t> cur_point = polygon[i];
        if (cur_point.x() <= 0)
        {
            OX_smaller_zero = true;
        }
        if (cur_point.x() >= 0)
        {
            OX_bigger_zero = true;
        }

        if (cur_point.y() <= 0)
        {
            OY_smaller_zero = true;
        }
        if (cur_point.y() >= 0)
        {
            OY_bigger_zero = true;
        }
    }

    return OX_smaller_zero && OX_bigger_zero && OY_smaller_zero && OY_bigger_zero;
}


int main()
{
    int64_t n = 0;
    int64_t m = 0;
    std::cin >> n >> m;

    std::vector<Point2d<int64_t>> airport(n);
    for (int64_t i = 0; i < n; ++i)
    {
        std::cin >> airport[i];
    }
    std::vector<Point2d<int64_t>> airport_reordered = polygon_clockwise_reordering(airport);

    std::vector<Point2d<int64_t>> cloud(m);
    for (int64_t i = 0; i < m; ++i)
    {
        std::cin >> cloud[i];
    }
    std::vector<Point2d<int64_t>> reflected_cloud = reflect_polygon(cloud);
    std::vector<Point2d<int64_t>> minkowski_sum = get_minkowski_sum(airport_reordered, reflected_cloud);
    
    double result = 0;
    if (origin_is_inside_polygon(minkowski_sum))
    {
        result = std::numeric_limits<double>::max();

        uint64_t minkowski_sum_size = minkowski_sum.size();
        for (uint64_t i = 0; i < minkowski_sum_size; ++i)
        {
            result = std::min(result, line_segment_point_distance(minkowski_sum[i],
                                                                       minkowski_sum[(i + 1) % minkowski_sum_size],
                                                                       {0, 0}));
        }

        double time_already_passed = 60;    // from problem statement

        result = std::max(0.0, result - time_already_passed);
    }

    std::cout << std::fixed << std::setprecision(7) << result << std::endl;

    return 0;
}
