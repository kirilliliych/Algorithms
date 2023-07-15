#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <istream>
#include <ostream>
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
double distance(const Point2d<Type> &p1, const Point2d<AnotherType> &p2)
{
    double dx = static_cast<double> (static_cast<Type> (p2.x()) - p1.x());
    double dy = static_cast<double> (static_cast<Type> (p2.y()) - p1.y());

    return sqrt(dx * dx + dy * dy);
}

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

template<typename Type>
std::ostream &operator <<(std::ostream &out, const Point2d<Type> &point)
{
    out << point.x() << " " << point.y();

    return out;
}

bool polar_angle_comparator(const Point2d<int64_t> &p1, const Point2d<int64_t> &p2, const Point2d<int64_t> &rel_point)
{
    int64_t skew_prod = skew_product(p1 - rel_point, p2 - rel_point);

    return (( skew_prod < 0) ||
            ((skew_prod == 0) && (distance(rel_point, p1) < distance(rel_point, p2))));
}

std::vector<Point2d<int64_t>> get_convex_hull(const std::vector<Point2d<int64_t>> &points)
{
    Point2d<int64_t> left_bottom_point = points[0];
    uint64_t points_quantity = points.size();
    for (uint64_t cur_point_index = 1; cur_point_index < points_quantity; ++cur_point_index)
    {
        Point2d<int64_t> cur_point = points[cur_point_index];
        if (( cur_point.x() <  left_bottom_point.x()) ||
            ((cur_point.x() == left_bottom_point.x()) && (cur_point.y() < left_bottom_point.y())))
        {
            left_bottom_point = cur_point;
        }
    }

    std::vector<Point2d<int64_t>> all_points = points;
    std::sort(all_points.begin(), all_points.end(), [&](const Point2d<int64_t> &p1, const Point2d<int64_t> &p2)
                                                                {
                                                                    return polar_angle_comparator(p1, p2, left_bottom_point);
                                                                });
    std::vector<Point2d<int64_t>> result;
    uint64_t cur_result_size = 0;
    uint64_t deletion_threshold = 2;
    for (uint64_t cur_point_index = 0; cur_point_index < points_quantity; ++cur_point_index)
    {
        Point2d<int64_t> cur_point = all_points[cur_point_index];
        while (cur_result_size >= deletion_threshold)
        {
            Point2d<int64_t> last_included_point = result[cur_result_size - 1];
            Point2d<int64_t> penultimate_included_point = result[cur_result_size - 2];
            
            Point2d<int64_t> new_border  = cur_point - last_included_point;
            Point2d<int64_t> last_border = last_included_point - penultimate_included_point;

            if (skew_product(new_border, last_border) <= 0)
            {
                result.pop_back();

                --cur_result_size;
            }
            else
            {
                break;
            }
        }

        result.push_back(cur_point);

        ++cur_result_size;
    }

    return result;
}

double get_polygon_area(const std::vector<Point2d<int64_t>> &polygon_contour)
{
    int64_t result = 0;

    uint64_t size = polygon_contour.size();
    for (uint64_t i = 1; i < size; ++i)
    {
        Point2d<int64_t> prev_point = polygon_contour[i - 1];
        Point2d<int64_t> cur_point  = polygon_contour[i];

        result += prev_point.x() * cur_point.y() - cur_point.x() * prev_point.y();
    }

    Point2d<int64_t> first_point = polygon_contour[0];
    Point2d<int64_t> last_point  = polygon_contour[size - 1];

    result += last_point.x() * first_point.y() - first_point.x() * last_point.y();

    return std::abs((static_cast<double> (result)) / 2);
}


int main()
{
    int N = 0;
    std::cin >> N;
    std::vector<Point2d<int64_t>> points(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> points[i];
    }

    std::vector<Point2d<int64_t>> hull = get_convex_hull(points);
    uint64_t hull_size = hull.size();
    std::cout << hull_size << std::endl;
    for (uint64_t i = 0; i < hull_size; ++i)
    {
        std::cout << hull[i] << std::endl;
    }
    
    std::cout << std::fixed << std::setprecision(1) << get_polygon_area(hull) << std::endl;
     
    return 0;
}
