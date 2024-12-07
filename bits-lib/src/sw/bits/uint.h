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

    bool operator<=(const bitset &otherBits) const
    {
        for (auto i = bitlength - 1u; i < bitlength; --i)
        {
            if (bits[i] != otherBits[i])
                return otherBits[i];
        }
        return true;
    }

    bool operator<=(const uint &other) const { return operator<=(other.bits); }

    bool operator>=(const bitset &otherBits) const
    {
        for (auto i = bitlength - 1u; i < bitlength; --i)
        {
            if (bits[i] != otherBits[i])
                return bits[i];
        }
        return true;
    }

    bool operator>=(const uint &other) const { return operator>=(other.bits); }

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

    uint &operator+=(const bitset &otherBits)
    {
        uint<2> overflow{0u};
        for (auto i = 0u; i < bitlength; ++i)
        {
            overflow.bits >>= 1;
            if (bits[i])
                ++overflow;
            if (otherBits[i])
                ++overflow;
            bits[i] = overflow.bits[0];
        }
        return *this;
    }

    uint &operator+=(const uint<bitlength> &other) { return operator+=(other.bits); }

    uint &operator-=(const bitset &otherBits)
    {
        uint<2> overflow{0u};
        for (auto i = 0u; i < bitlength; ++i)
        {
            overflow.bits >>= 1;
            if (otherBits[i])
                ++overflow;
            if (overflow.bits[0] && !bits[i])
                overflow.bits[1] = true;
            bits[i] = overflow.bits[0] != bits[i];
        }
        return *this;
    }

    uint &operator-=(const uint &other) { return operator-=(other.bits); }

    uint &operator*=(const bitset &otherBits)
    {
        bitset copy{bits};
        bits.reset();
        for (auto i = 0u; i < bitlength; ++i)
        {
            if (otherBits[i])
                operator+=(copy << i);
        }
        return *this;
    }

    uint &operator*=(const uint<bitlength> &other) { return operator*=(other.bits); }
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
    return uint<bitlength>{a} *= b;
}

}    // namespace sw::bits
