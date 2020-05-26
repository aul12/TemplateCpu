#include "cpu.hpp"
#include "util.hpp"

using test_prog =
        Program<
            AddI<int, Reg::A, Reg::ZERO, 10>, // a = 10
            AddI<int, Reg::C, Reg::C, 1>, // c += 1
            BranchNEqI<int, Reg::A, Reg::C, 1>
        >;

int main() {
    using registers = Cpu<test_prog>::run;
    registerPrinter<registers>::print();

    return 0;
}
