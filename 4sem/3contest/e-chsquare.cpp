#include <cmath>
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


class FenwickTree
{
public:

    explicit FenwickTree(int64_t size)
      : ft_(size, 0)
    {}

    void add(int from, int64_t value)
    {
        int64_t fenwick_size = static_cast<int64_t> (ft_.size());
        for (int i = from; i < fenwick_size; i |= (i + 1))
        {
            ft_[i] += value;
        }
    }

    int64_t sum(int from) const
    {
        int64_t result = 0;
        for (int i = from; i > 0; i &= (i - 1))
        {
            result += ft_[i - 1];
        }

        return result;
    }

private:

    std::vector<int64_t> ft_;
};


std::vector<int64_t> polygon_reordering(const std::vector<Point2d<int64_t>> &polygon)
{
    int64_t polygon_points_quantity = static_cast<int64_t> (polygon.size());
    int64_t coef = 0;
    for (int64_t i = 0; i < polygon_points_quantity; ++i)
    {
        coef += skew_product(polygon[i], polygon[(i + 1) % polygon_points_quantity]);
    }
    std::vector<int64_t> result(polygon_points_quantity);
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

    if (coef > 0)
    {
        for (int64_t i = 0; i < polygon_points_quantity; ++i)
        {
            result[i] = (polygon_left_bottom_point_index - i + polygon_points_quantity) % polygon_points_quantity;
        }
    }
    else
    {
        for (int64_t i = 0; i < polygon_points_quantity; ++i)
        {
            result[i] = (polygon_left_bottom_point_index + i) % polygon_points_quantity;
        }
    }

    return result;
}

int64_t get_tranezium_area(const Point2d<int64_t> &p1,
                         const Point2d<int64_t> &p2)
{
    return (p2.x() - p1.x()) * (p1.y() + p2.y());
}

Point2d<int64_t> calculate_area(int64_t index1, int64_t index2, const FenwickTree &ft,
                                const std::vector<Point2d<int64_t>> &polygon, const std::vector<int64_t> &polygon_reordered_indexes,
                                int64_t whole_area)
{
    if (index1 > index2)
    {
        std::swap(index1, index2);
    }

    int64_t smaller_part_area = 0;
    if (index1 > 0)
    {
        smaller_part_area += ft.sum(static_cast<int> (index1));
    }
    smaller_part_area += whole_area - ft.sum(static_cast<int> (index2));
    smaller_part_area += get_tranezium_area(polygon[polygon_reordered_indexes[index1]], polygon[polygon_reordered_indexes[index2]]);

    int64_t bigger_part_area = whole_area - smaller_part_area;
    if (smaller_part_area > bigger_part_area)
    {
        std::swap(smaller_part_area, bigger_part_area);
    }

    return {smaller_part_area, bigger_part_area};
}


int main()
{
    int64_t N = 0;
    std::cin >> N;

    std::vector<Point2d<int64_t>> polygon(N);
    for (int64_t i = 0; i < N; ++i)
    {
        std::cin >> polygon[i];
    }

    std::vector<int64_t> polygon_reordered_indexes = polygon_reordering(polygon);
    std::vector<int64_t> polygon_index_inv(N);
    for (int64_t i = 0; i < N; ++i)
    {
        polygon_index_inv[polygon_reordered_indexes[i]] = i;
    }

    FenwickTree ft(N);
    std::vector<int64_t> calculated_areas(N);

    int64_t full_area = 0;
    for (int64_t i = 0; i < N; ++i)
    {
        Point2d<int64_t> last_point = polygon[polygon_reordered_indexes[i]];
        Point2d<int64_t> cur_point  = polygon[polygon_reordered_indexes[(i + 1) % N]];

        calculated_areas[i] = get_tranezium_area(last_point, cur_point);
        full_area += calculated_areas[i];
        ft.add(static_cast<int> (i), calculated_areas[i]);
    }

    int64_t Q = 0;
    std::cin >> Q;
    for (int64_t cur_query = 0; cur_query < Q; ++cur_query)
    {
        int query_type = 0;
        std::cin >> query_type;

        switch (query_type)
        {
            case 1:
            {
                int64_t m = 0;
                int64_t n = 0;
                std::cin >> m >> n;

                m = polygon_index_inv[m - 1];
                n = polygon_index_inv[n - 1];

                Point2d<int64_t> result = calculate_area(m, n, ft, polygon, polygon_reordered_indexes, full_area);
                std::cout << static_cast<double> (result.x()) / 2 << " " << static_cast<double> (result.y()) / 2 << std::endl;

                break;
            }

            case 2:
            {
                int64_t vertex_index = 0;
                Point2d<int64_t> new_vertex;

                std::cin >> vertex_index >> new_vertex;
                vertex_index = polygon_index_inv[vertex_index - 1];

                polygon[polygon_reordered_indexes[vertex_index]] = new_vertex;
                auto prev_index = (vertex_index - 1 + N) % N;
                auto prev_area = get_tranezium_area(polygon[polygon_reordered_indexes[prev_index]],
                                                             polygon[polygon_reordered_indexes[vertex_index]]);
                int64_t diff = prev_area - calculated_areas[prev_index];
                calculated_areas[prev_index] += diff;
                full_area += diff;
                ft.add(static_cast<int> (prev_index), diff);

                auto next_index = (vertex_index + 1) % N;
                auto next_area = get_tranezium_area(polygon[polygon_reordered_indexes[vertex_index]],
                                                             polygon[polygon_reordered_indexes[next_index]]);
                diff = next_area - calculated_areas[vertex_index];
                calculated_areas[vertex_index] += diff;
                full_area += diff;
                ft.add(static_cast<int> (vertex_index), diff);

                break;
            }

            default:
            {
                break;
            }
        }
    }

    return 0;
}
