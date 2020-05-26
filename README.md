# TemplateCpu
Implementing a CPU emulator using C++ Meta Programming with Concepts.

## Syntax
The syntax is pure C++, with classes which behave like instructions. 
The assembly-syntax is heavily inspired by MIPS:

```c++
#include "cpu.hpp"
#include "util.hpp"

using test_prog =
        Program<
            AddI<int, Reg::A, Reg::ZERO, 40>,// 0: a = 40
            AddI<int, Reg::B, Reg::ZERO, 1>, // 1: b = 1
            AddI<int, Reg::C, Reg::ZERO, 0>, // 2: c = 0
            AddI<int, Reg::D, Reg::ZERO, 0>, // 3: d = 0
            AddI<int, Reg::E, Reg::ZERO, 1>, // 4: e = 1
            AddI<int, Reg::B, Reg::B, 1>,    // 5: b += 1
            AddI<int, Reg::C, Reg::D, 0>,    // 6: c = d
            AddI<int, Reg::D, Reg::E, 0>,    // 7: d = e
            Add<Reg::E, Reg::C, Reg::D>,     // 8: e = c + d
            BranchNEqI<int, Reg::A, Reg::B, 5> // 9: if a != c -> jmp 5
        >;

int main() {
    using registers = Cpu<test_prog>::run;
    registerPrinter<registers>::print();

    return 0;
}
```
