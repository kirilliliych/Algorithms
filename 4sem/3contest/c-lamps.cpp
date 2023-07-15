#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <istream>
#include <limits>
#include <vector>


namespace math_consts
{
    const double PI = std::acos(-1);
    const double DEGREES_IN_PI_RADIANS = 180;
};


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

template<typename Type, typename AnotherType>
int64_t dot_product(const Point2d<Type> &v1, const Point2d<AnotherType> &v2)
{
    return static_cast<int64_t> (v1.x() * static_cast<AnotherType> (v2.x()) + v1.y() * static_cast<AnotherType> (v2.y()));
}

template<typename Type, typename AnotherType>
double angle_between(const Point2d<Type> &v1, const Point2d<AnotherType> &v2)
{
    return std::acos(dot_product(v1, v2) / (get_length(v1) * get_length(v2)));
}

double degrees_to_radians(double angle_in_degrees)
{
    return angle_in_degrees / math_consts::DEGREES_IN_PI_RADIANS * math_consts::PI;
}

template<typename Type>
Point2d<Type> rotate_vector(const Point2d<Type> &vector, double angle)
{
    double sin = std::sin(angle);
    double cos = std::cos(angle);

    Type x = vector.x();
    Type y = vector.y();

    return {x * cos - y * sin,
            x * sin + y * cos
           };
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
class Lamp
{
public:

    Lamp()
      : location_(),
        angle_()
    {}

    Lamp(const Point2d<Type> &location, Type angle)
      : location_(location),
        angle_(angle)
    {}

    Point2d<Type> get_location() const
    {
        return location_;
    }

    Type get_angle() const
    {
        return angle_;
    }

    void set_location(Point2d<Type> location)
    {
        location_ = location;
    }

    void set_angle(Type angle)
    {
        angle_ = angle;
    }

private:

    Point2d<Type> location_;
    Type angle_;
};

template<typename Type>
std::istream &operator >>(std::istream &in, Lamp<Type> &lamp)
{
    Point2d<Type> temp_location;
    Type temp_angle;
    std::cin >> temp_location >> temp_angle;
    lamp.set_location(temp_location);
    lamp.set_angle(temp_angle);

    return in;
}


template<typename Type>
double calculate_new_max_distance(double prev_right, const Lamp<Type> &rotated_lamp, double right_border)
{
    double lamp_x = static_cast<double> (rotated_lamp.get_location().x());
    double lamp_y = static_cast<double> (rotated_lamp.get_location().y());
    double lamp_angle = degrees_to_radians(static_cast<double> (rotated_lamp.get_angle()));

    Point2d<double> lamp_to_shadow_edge_vector{prev_right -lamp_x,
                                                          -lamp_y
                                              };
    Point2d<double> lamp_to_end_vector{right_border - lamp_x, -lamp_y};
    if (lamp_angle >= angle_between(lamp_to_shadow_edge_vector, lamp_to_end_vector))
    {
        return std::numeric_limits<double>::max();
    }

    Point2d<double> lamp_to_max_right_lit_point_vector = rotate_vector(lamp_to_shadow_edge_vector,
                                                                       lamp_angle);

    double coef = lamp_to_max_right_lit_point_vector.x() / lamp_to_max_right_lit_point_vector.y();
    assert(std::isfinite(coef));
    double result = lamp_x - lamp_y * coef;

    return result;

}

template<typename Type>
double get_max_walk_distance(const std::vector<Lamp<Type>> &lamps, int64_t left, int64_t right)
{
    int64_t lamps_quantity = static_cast<int64_t> (lamps.size());
    int64_t lamps_configuration_quantity = static_cast<int64_t> (1llu << lamps_quantity);
    std::vector<double> dp_lamps_used(lamps_configuration_quantity, static_cast<double> (left));

    for (int64_t cur_lamps_configuration = 0; cur_lamps_configuration < lamps_configuration_quantity; ++cur_lamps_configuration)
    {
        for (int64_t cur_lamp_bit_index = 0; cur_lamp_bit_index < lamps_quantity; ++cur_lamp_bit_index)
        {
            uint64_t cur_lamp_mask = 1llu << cur_lamp_bit_index;
            uint64_t new_lamps_configuration = cur_lamps_configuration | cur_lamp_mask;
            if (!(cur_lamps_configuration & cur_lamp_mask))
            {
                double new_distance = calculate_new_max_distance(dp_lamps_used[cur_lamps_configuration], lamps[cur_lamp_bit_index], right);
                if (new_distance >= static_cast<double> (right))
                {
                    return static_cast<double> (right - left);
                }

                dp_lamps_used[new_lamps_configuration] = std::max(dp_lamps_used[new_lamps_configuration], new_distance);
            }
        }
    }

    return dp_lamps_used[lamps_configuration_quantity - 1] - static_cast<double> (left);
}


int main()
{
    int64_t n = 0;
    int64_t l = 0;
    int64_t r = 0;
    std::cin >> n >> l >> r;

    std::vector<Lamp<int64_t>> lamps(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> lamps[i];
    }

    std::cout << std::fixed << std::setprecision(7) << get_max_walk_distance(lamps, l, r) << std::endl;

    return 0;
}

