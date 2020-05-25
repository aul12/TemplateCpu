#include <iostream>

#include "cpu.hpp"

using test_prog =
        FromVariadicType<
            AddI<int, 1, 0, 1>, // Add 1 to Reg-1
            Add<2, 0, 1>, // Fibonacci Step 1: Reg2 = Reg0 + Reg1
            Add<3, 1, 2>,
            Add<4, 2, 3>,
            Add<5, 3, 4>,
            Add<6, 4, 5>
        >::type;

int main() {
    using list = FromVariadicVal<int, 0, 1, 0, 0, 0, 0, 0>::type;

    std::cout << Cpu<test_prog>::type{};
    return 0;
}
