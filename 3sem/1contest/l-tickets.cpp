

const long long MAX_NUMBER_DECIMAL_FORM_SIZE = 10000;
const long long MAX_NUMBER_WRITTEN_FORM_SIZE = 18;
const long long BASE = 10000000000;


class BigInt
{
public:

    BigInt() = default;

    BigInt(int value)
      : written_form_size(0),
        base(BASE)
    {
        *this = value;
    }

    ~BigInt() = default;


    const BigInt &operator =(int value)                                         // cringe not zero-cost operator :/
    {
        number[0] = value;
        written_form_size = 1;

        return *this;
    }

    void operator +=(const BigInt &rhs)                                         // another cringe not zero-cost operator :/
    {
              long long *cur_number    = number;
        const long long *number_to_add = rhs.number;

        long long max_size = std::max(written_form_size, rhs.written_form_size);
        for (long long i = 0; i < max_size; ++i)
        {
            long long cur_value = cur_number[i] + number_to_add[i];
            if (cur_value >= base)
            {
                cur_value -= base;
                ++cur_number[i + 1];

                if (i == max_size - 1)
                {
                    ++max_size;
                }
            }

            cur_number[i] = cur_value;
        }

        written_form_size = max_size;
    }

    BigInt operator +(const BigInt &rhs)
    {
        BigInt result = *this;
        result += rhs;

        return result;
    }

    friend std::ostream &operator <<(std::ostream &out, const BigInt &value)
    {
        char decimal_form[MAX_NUMBER_DECIMAL_FORM_SIZE] = {};
        long long cur_decimal_index = 0;
        long long zeros_in_base = 10;
        for (long long cur_cell = 0; cur_cell < value.written_form_size; ++cur_cell)
        {
            cur_decimal_index = zeros_in_base * cur_cell;
            long long cur_val = value.number[cur_cell];
            while (cur_val > 0)
            {
                decimal_form[cur_decimal_index] = cur_val % 10 + '0';
                cur_val /= 10;

                ++cur_decimal_index;
            }
        }

        for (long long index = cur_decimal_index - 1; index >= 0; --index)
        {
            if (decimal_form[index] == '\0')
            {
                std::cout << "0";
            }
            else
            {
                std::cout << decimal_form[index];
            }
        }

        return out;
    }

private:
public:

    long long base = BASE;
    long long written_form_size = 0;
    long long number[MAX_NUMBER_WRITTEN_FORM_SIZE] = {};
};


BigInt get_lucky_tickets_quantity(long long num_size, long long base)
{
    BigInt **dp = new BigInt *[num_size + 1];
    for (long long i = 0; i < num_size + 1; ++i)
    {
        dp[i] = new BigInt[(num_size / 2) * (base - 1) + 1];
    }

    for (long long i = 0; i < base; ++i)
    {
        dp[1][i] = 1;
    }
    
    for (long long i = 2; i < num_size + 1; ++i)
    {
        long long max_value_of_i_digits = std::min(i * (base - 1), (num_size / 2) * (base - 1));
        for (long long j = 0; j <= max_value_of_i_digits; ++j)
        {
            for (long long k = 0; (k < base) && (j - k >= 0); ++k)
            {
                dp[i][j] += dp[i - 1][j - k];
            }
        }
    }

    BigInt result = dp[num_size][(num_size / 2) * (base - 1)];

    for (long long i = 0; i < num_size + 1; ++i)
    {
        delete [] dp[i];
    }
    delete [] dp;

    return result;
}


int main()
{
    long long N = 0;
    long long M = 0;
    std::cin >> N >> M;

    std::cout << get_lucky_tickets_quantity(N, M);

    return 0;
}s