#include <sw/bits/uint.h>

#include <gtest/gtest.h>

#include <random>

namespace sw::bits {

TEST(uint_test, increment)
{
    constexpr size_t bitlength = 16u;
    for (auto i = 0u; i < (1u << bitlength) - 2; ++i)
    {
        sw::bits::uint<bitlength> b0{i};
        const auto b1 = b0++;
        EXPECT_EQ(b1.bits.to_ulong(), i);
        EXPECT_EQ(b0.bits.to_ulong(), i + 1);
        EXPECT_EQ((++b0).bits.to_ulong(), i + 2);
    }
}

TEST(uint_test, decrement)
{
    constexpr size_t bitlength = 16u;
    for (auto i = 2u; i < (1u << bitlength); ++i)
    {
        sw::bits::uint<bitlength> b0{i};
        const auto b1 = b0--;
        EXPECT_EQ(b1.bits.to_ulong(), i);
        EXPECT_EQ(b0.bits.to_ulong(), i - 1);
        EXPECT_EQ((--b0).bits.to_ulong(), i - 2);
    }
}

TEST(uint_test, addition)
{
    constexpr size_t bitlength = 32u;

    const auto check = [](const unsigned long i0, const unsigned long i1) {
        uint<bitlength> b0{i0};
        uint<bitlength> b1{i1};

        const auto sum = (b0 + b1).bits.to_ulong();
        const auto sumExpected = i0 + i1;
        EXPECT_EQ(sum, sumExpected);

        b0 += b1;
        const auto sumInPlace = b0.bits.to_ulong();
        EXPECT_EQ(sumInPlace, sumExpected);
    };

    std::default_random_engine rand(1);
    std::uniform_int_distribution<unsigned long> dist(0u, 1u << (bitlength - 1));

    for (auto i = 0; i < 100; ++i)
        check(dist(rand), dist(rand));
}

TEST(uint_test, subtraction)
{
    constexpr size_t bitlength = 32u;

    const auto check = [](unsigned long i0, unsigned long i1) {
        if (i0 < i1)
            std::swap(i0, i1);

        uint<bitlength> b0{i0};
        uint<bitlength> b1{i1};

        const auto diff = (b0 - b1).bits.to_ulong();
        const auto diffExpected = i0 - i1;
        EXPECT_EQ(diff, diffExpected);

        b0 -= b1;
        const auto diffInPlace = b0.bits.to_ulong();
        EXPECT_EQ(diffInPlace, diffExpected);
    };

    std::default_random_engine rand(12);
    std::uniform_int_distribution<unsigned long> dist(0u, 1u << (bitlength - 1));

    for (auto i = 0; i < 100; ++i)
        check(dist(rand), dist(rand));
}

}    // namespace sw::bits
