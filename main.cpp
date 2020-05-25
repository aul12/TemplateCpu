#include <iostream>

#include "cpu.hpp"

using test_prog =
        FromVariadicType<
            Add<2, 0, 1>,
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
