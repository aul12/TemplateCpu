#include "cpu.hpp"
#include "util.hpp"

using test_prog =
        Program<
            AddI<int, Reg::A, Reg::ZERO, 20>, // 0: a = 10
            AddI<int, Reg::C, Reg::ZERO, 0>, // 1: c = 0
            AddI<int, Reg::D, Reg::ZERO, 0>, // 2: d = 0
            AddI<int, Reg::E, Reg::ZERO, 1>, // 3: e = 1
            AddI<int, Reg::B, Reg::B, 1>,    // 4: b += 1
            AddI<int, Reg::C, Reg::D, 0>,    // 5: c = d
            AddI<int, Reg::D, Reg::E, 0>,    // 6: d = e
            Add<Reg::E, Reg::C, Reg::D>,     // 7: e = c + d
            BranchNEqI<int, Reg::A, Reg::B, 4> // 8: if a != c -> jmp 4
        >;

int main() {
    using registers = Cpu<test_prog>::run;
    registerPrinter<registers>::print();

    return 0;
}
