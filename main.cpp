#include <sw/bits/uint.h>

#include <format>
#include <iostream>

int main()
{
    for (auto i = 0u; i < 10u; ++i)
    {
        for (auto j = 0u; j <= i; ++j)
        {
            sw::bits::uint<24> a{i};
            std::cout << std::format("a = {} ({})", a.bits.to_string(), a.bits.to_ulong()) << std::endl;

            sw::bits::uint<24> b{j};
            std::cout << std::format("b = {} ({})", b.bits.to_string(), b.bits.to_ulong()) << std::endl;

            const auto sum = a + b;
            std::cout << std::format("a + b = {} ({})", sum.bits.to_string(), sum.bits.to_ulong()) << std::endl;

            const auto diff = a - b;
            std::cout << std::format("a - b = {} ({})", diff.bits.to_string(), diff.bits.to_ulong()) << std::endl
                      << std::endl;
        }
    }

    return 0;
}
