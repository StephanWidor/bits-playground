#pragma once
#include <bitset>

namespace sw::bits {

template<size_t bitlength>
struct uint
{
    using bitset = std::bitset<bitlength>;
    bitset bits;

    uint(const uint &) = default;

    uint(const unsigned long i): bits(i) {}

    bool operator==(const uint &) const = default;

    uint &operator++()
    {
        for (auto i = 0u; i < bitlength; ++i)
        {
            if (bits[i])
                bits[i] = false;
            else
            {
                bits[i] = true;
                break;
            }
        }
        return *this;
    }

    uint operator++(int)
    {
        uint copy = *this;
        operator++();
        return copy;
    }

    uint &operator--()
    {
        for (auto i = 0u; i < bitlength; ++i)
        {
            if (bits[i])
            {
                bits[i] = false;
                break;
            }
            else
                bits[i] = true;
        }
        return *this;
    }

    uint operator--(int)
    {
        uint copy = *this;
        operator--();
        return copy;
    }

    uint &operator+=(const uint<bitlength> &other)
    {
        uint<2> overflow{0u};
        for (auto i = 0u; i < bitlength; ++i)
        {
            overflow.bits >>= 1;
            if (bits[i])
                ++overflow;
            if (other.bits[i])
                ++overflow;
            bits[i] = overflow.bits[0];
        }
        return *this;
    }

    uint &operator-=(const uint &b)
    {
        uint<2> overflow{0u};
        for (auto i = 0u; i < bitlength; ++i)
        {
            overflow.bits >>= 1;
            if (b.bits[i])
                ++overflow;
            if (overflow.bits[0] && !bits[i])
                overflow.bits[1] = true;
            bits[i] = overflow.bits[0] != bits[i];
        }
        return *this;
    }
};

template<size_t bitlength>
uint<bitlength> operator+(const uint<bitlength> &a, const uint<bitlength> &b)
{
    return uint<bitlength>{a} += b;
}

template<size_t bitlength>
uint<bitlength> operator-(const uint<bitlength> &a, const uint<bitlength> &b)
{
    return uint<bitlength>{a} -= b;
}

}    // namespace sw::bits
