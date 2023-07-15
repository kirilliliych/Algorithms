#include <cassert>
#include <cstdint>
#include <iostream>


namespace consts
{
   static const int64_t MODULO = 1e9 + 7;
}


class ModuledInt
{
    friend std::ostream &operator <<(std::ostream &stream, const ModuledInt &moduled_int);

public:
//---------------------------------------------------------------------------------
    ModuledInt(int64_t value, int64_t modulo)
      : modulo_(modulo),
        value_(get_modulo_(value))
    {
        assert(modulo > 0);
    }

    ModuledInt(const ModuledInt &other) = default;
    ModuledInt(ModuledInt &&other) = default;

    ModuledInt &operator =(const ModuledInt &other) = default;
    ModuledInt &operator =(ModuledInt &&other) = default;
//---------------------------------------------------------------------------------
    ModuledInt operator -() const
    {
        if (value_ == INT64_MIN)
        {
            int64_t ret_val = modulo_ - (INT64_MAX % modulo_) - 1;

            return {ret_val, modulo_};
        }

        return {-value_, modulo_};
    }

    ModuledInt &operator +=(const ModuledInt &other)
    {
        assert(modulo_ == other.modulo_);

        enum class OFCode
        {
            OK = 0,
            POSITIVE,
            NEGATIVE
        };

        OFCode code = OFCode::OK;

        if ((value_ > 0) && (other.value_ > 0) && (value_ >= INT64_MAX - other.value_))
        {
            code = OFCode::POSITIVE;
        }
        else if ((value_ < 0) && (other.value_ < 0) && (value_ <= INT64_MIN - other.value_))
        {
            code = OFCode::NEGATIVE;
        }

        if (code != OFCode::OK)
        {
            std::cerr << "Class " << typeid(*this).name() << ": ";
            switch (code)
            {
                case OFCode::POSITIVE:
                    std::cerr << "positive overflow in func ";
                break;

                case OFCode::NEGATIVE:
                    std::cerr << "negative overflow in func ";

                case OFCode::OK:
                default:
                break;
            }
            std::cerr << __FUNCTION__ << " arg1: " << value_ << " arg2: " << other.value_ << std::endl;

            return *this;
        }

        value_ += other.value_;
        value_ = get_modulo_(value_);

        return *this;
    }

    ModuledInt &operator -=(const ModuledInt &other)
    {
        assert(modulo_ == other.modulo_);

        if (other.value_ == INT64_MIN)
        {
            if (value_ < 0)
            {
                value_ += INT64_MAX;
            }
            else
            {
                std::cerr << "Class " << typeid(*this).name() << ": positive overflow in func " << __FUNCTION__
                          << " arg1: " << value_ << " arg2: " << INT64_MIN << std::endl;

                return *this; 
            }

        }
        operator +=(-other);

        return *this;
    }

    ModuledInt &operator *=(const ModuledInt &other)
    {
        assert(modulo_ == other.modulo_);

        enum class OFCode
        {
            OK = 0,
            POSITIVE,
            NEGATIVE
        };

        OFCode code = OFCode::OK;

        if (((value_       == -1) && (other.value_ == INT64_MIN)) ||
            ((other.value_ == -1) && (value_       == INT64_MIN)) ||
            ((value_       !=  0) && (other.value_ > INT64_MAX / value_)))
        {
            code = OFCode::POSITIVE;
        }
        if ((value_ != 0) && (other.value_ < INT64_MIN / value_))
        {
            code = OFCode::NEGATIVE;
        }

        if (code != OFCode::OK)
        {
            std::cerr << "Class " << typeid(*this).name() << ": ";
            switch (code)
            {
                case OFCode::POSITIVE:
                    std::cerr << "positive overflow in func ";
                break;

                case OFCode::NEGATIVE:
                    std::cerr << "negative overflow in func ";
                break;

                case OFCode::OK:
                default:
                break;
            }
            std::cerr << __FUNCTION__ << " arg1: " << value_ << " arg2: " << other.value_ << std::endl;

            return *this;
        }

        value_ *= other.value_;
        value_ = get_modulo_(value_);

        return *this;
    }

    ModuledInt &operator /=(const ModuledInt &other)
    {
        assert(modulo_ == other.modulo_);

        ModuledInt multiplier = ModuledInt(binpow_(other.value_, modulo_ - 2), modulo_);
        
        return operator *=(multiplier);
    }

#define BINARY_OP(op_code)                                          \
    ModuledInt operator op_code(const ModuledInt &other)            \
    {                                                               \
        assert(modulo_ == other.modulo_);                           \
                                                                    \
        return ModuledInt(*this) op_code##= ModuledInt(other);      \
    }

    BINARY_OP(+);
    BINARY_OP(-);
    BINARY_OP(*);
    BINARY_OP(/);

private:
//---------------------------------------------------------------------------------
    int64_t binpow_(int64_t base, int64_t deg)
    {
        int64_t result = 1;
        while (deg > 0)
        {
            if (deg & 1)
            {
                result *= base;
                result %= modulo_;
            }
            base *= base;
            base %= modulo_;
            deg >>= 1;
        }

        return result;
    }

    int64_t get_modulo_(int64_t value)
    {
        return value < 0 ? modulo_ - (-value % modulo_) : value % modulo_;
    }

private:
//-----------------------------------Variables-------------------------------------
    int64_t modulo_  = 0;
    int64_t value_   = 0;
};

std::ostream &operator <<(std::ostream &stream, const ModuledInt &moduled_int)
{
    return stream << moduled_int.value_;
}


int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    std::cin >> a >> b >> c >> d;

    ModuledInt a_mod(a, consts::MODULO);
    ModuledInt b_mod(b, consts::MODULO);
    ModuledInt c_mod(c, consts::MODULO);
    ModuledInt d_mod(d, consts::MODULO);

    std::cout << a_mod / b_mod + c_mod / d_mod;


    return 0;
}
