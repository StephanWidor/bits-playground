#pragma once
#include <bitset>

namespace sw::bits {

template<bool strongOrder, size_t bitlength>
bool smaller(const std::bitset<bitlength> &bits0, const std::bitset<bitlength> &bits1)
{
    for (auto i = bitlength - 1u; i < bitlength; --i)
    {
        if (bits0[i] != bits1[i])
            return bits1[i];
    }
    return !strongOrder;
}

template<bool strongOrder, size_t bitlength>
bool greater(const std::bitset<bitlength> &bits0, const std::bitset<bitlength> &bits1)
{
    for (auto i = bitlength - 1u; i < bitlength; --i)
    {
        if (bits0[i] != bits1[i])
            return bits0[i];
    }
    return !strongOrder;
}

template<size_t bitlength>
void increment(std::bitset<bitlength> &bits)
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
}

template<size_t bitlength>
void decrement(std::bitset<bitlength> &bits)
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
}

template<size_t bitlength>
void addInPlace(std::bitset<bitlength> &bits0, const std::bitset<bitlength> &bits1)
{
    std::bitset<2> overflow{0u};
    for (auto i = 0u; i < bitlength; ++i)
    {
        overflow >>= 1;
        if (bits0[i])
            increment(overflow);
        if (bits1[i])
            increment(overflow);
        bits0[i] = overflow[0];
    }
}

template<size_t bitlength>
void subtractInPlace(std::bitset<bitlength> &bits0, const std::bitset<bitlength> &bits1)
{
    std::bitset<2> overflow{0u};
    for (auto i = 0u; i < bitlength; ++i)
    {
        overflow >>= 1;
        if (bits1[i])
            increment(overflow);
        if (overflow[0] && !bits0[i])
            overflow[1] = true;
        bits0[i] = overflow[0] != bits0[i];
    }
}

template<size_t bitlength>
std::bitset<bitlength> multiply(const std::bitset<bitlength> &bits0, const std::bitset<bitlength> &bits1)
{
    std::bitset<bitlength> accumulator{0u};
    for (auto i = 0u; i < bitlength; ++i)
    {
        if (bits1[i])
            addInPlace(accumulator, bits0 << i);
    }
    return accumulator;
}

template<size_t bitlength>
struct uint
{
    using bitset = std::bitset<bitlength>;
    bitset bits;

    bool operator==(const uint &) const = default;

    bool operator<=(const uint &other) const { return smaller<false>(bits, other.bits); }

    bool operator<(const uint &other) const { return smaller<true>(bits, other.bits); }

    bool operator>=(const uint &other) const { return greater<false>(bits, other.bits); }

    bool operator>(const uint &other) const { return greater<true>(bits, other.bits); }

    uint &operator++()
    {
        increment(bits);
        return *this;
    }

    uint operator++(int)
    {
        uint copy = *this;
        increment(bits);
        return copy;
    }

    uint &operator--()
    {
        decrement(bits);
        return *this;
    }

    uint operator--(int)
    {
        uint copy = *this;
        decrement(bits);
        return copy;
    }

    uint &operator+=(const uint<bitlength> &other)
    {
        addInPlace(bits, other.bits);
        return *this;
    }

    uint &operator-=(const uint &other)
    {
        subtractInPlace(bits, other.bits);
        return *this;
    }

    uint &operator*=(const uint<bitlength> &other)
    {
        bits = multiply(bits, other.bits);
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

template<size_t bitlength>
uint<bitlength> operator*(const uint<bitlength> &a, const uint<bitlength> &b)
{
    return uint<bitlength>{multiply(a.bits, b.bits)};
}

}    // namespace sw::bits
