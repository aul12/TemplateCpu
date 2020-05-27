#include "cpu.hpp"
#include "util.hpp"

using fib_iterative =
        Program<
            AddI<int, Reg::A, Reg::ZERO, 40>,// 0: a = 40
            AddI<int, Reg::B, Reg::ZERO, 1>, // 1: b = 1
            AddI<int, Reg::C, Reg::ZERO, 0>, // 2: c = 0
            AddI<int, Reg::D, Reg::ZERO, 0>, // 3: d = 0
            AddI<int, Reg::E, Reg::ZERO, 1>, // 4: e = 1
            AddI<int, Reg::B, Reg::B, 1>,    // 5: b += 1
            Mov<Reg::C, Reg::D>,             // 6: c = d
            Mov<Reg::D, Reg::E>,             // 7: d = e
            Add<Reg::E, Reg::C, Reg::D>,     // 8: e = c + d
            BranchNEqI<int, Reg::A, Reg::B, 5> // 9: if a != c -> jmp 5
        >;

int main() {
    using registers = Cpu<fib_iterative>::run;
    registerPrinter<registers>::print();

    return 0;
}
