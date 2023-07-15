#include <cmath>
#include <iostream>
#include <set>
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

    Point2d<Type> operator *(double scalar) const
    {
        return {x_ * scalar,
                y_ * scalar
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

    explicit operator Point2d<double>() const
    {
        return {static_cast<double> (x_),
                static_cast<double> (y_)
               };
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

template<typename Type>
Point2d<Type> normalize_vector(const Point2d<Type> &vector)
{ 
    double length = get_length(vector);

    return {vector.x() / length,
            vector.y() / length
           };
}

template<typename Type>
Point2d<double> get_normal(const Point2d<Type> &vector)
{
    double length = get_length(vector);

    return {-vector.y() / length,
             vector.x() / length
           };
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


int main()
{
    int64_t N = 0;
    std::cin >> N;

    std::vector<Point2d<int64_t>> modules(N);
    std::set<Point2d<int64_t>> modules_presence_set;
    for (int64_t i = 0; i < N; ++i)
    {
        std::cin >> modules[i];
        modules_presence_set.insert(modules[i]);
    }

    int64_t synchronization_cells_quantity = 0;
    for (int64_t diag_module1 = 0; diag_module1 < N; ++diag_module1)
    {
        for (int64_t diag_module2 = diag_module1 + 1; diag_module2 < N; ++diag_module2)
        {
            Point2d<double> normal_to_square_diag_vector = get_normal(modules[diag_module2] - modules[diag_module1]);
            Point2d<double> square_diag_vector_center(static_cast<double> (modules[diag_module1].x() + modules[diag_module2].x()) / 2.0,
                                                      static_cast<double> (modules[diag_module1].y() + modules[diag_module2].y()) / 2.0
                                                     );
            double square_half_diag_length = get_length(static_cast<Point2d<double>> (modules[diag_module1]) - square_diag_vector_center);

            Point2d<double> square_calculated_potential_point1 = square_diag_vector_center + normal_to_square_diag_vector * square_half_diag_length;
            Point2d<double> square_calculated_potential_point2 = square_diag_vector_center - normal_to_square_diag_vector * square_half_diag_length;

            Point2d<int64_t> square_int_potential_point1(static_cast<int64_t> (std::round(square_calculated_potential_point1.x())),
                                                         static_cast<int64_t> (std::round(square_calculated_potential_point1.y())));
            Point2d<int64_t> square_int_potential_point2(static_cast<int64_t> (std::round(square_calculated_potential_point2.x())),
                                                         static_cast<int64_t> (std::round(square_calculated_potential_point2.y())));
            double precision_threshold = 1e-10;
            if ((std::abs(static_cast<double> (square_int_potential_point1.x()) - square_calculated_potential_point1.x()) < precision_threshold) &&
                (std::abs(static_cast<double> (square_int_potential_point1.y()) - square_calculated_potential_point1.y()) < precision_threshold) &&
                (std::abs(static_cast<double> (square_int_potential_point2.x()) - square_calculated_potential_point2.x()) < precision_threshold) &&
                (std::abs(static_cast<double> (square_int_potential_point2.y()) - square_calculated_potential_point2.y()) < precision_threshold) &&
                (modules_presence_set.find(square_int_potential_point1) != modules_presence_set.cend())                                          &&
                (modules_presence_set.find(square_int_potential_point2) != modules_presence_set.cend()))
            {
                ++synchronization_cells_quantity;
            }
        }
    }

    std::cout << synchronization_cells_quantity / 2;

    return 0;
}
