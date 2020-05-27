# TemplateCpu
Implementing a CPU emulator using C++ Meta Programming with Concepts.

## Syntax
The syntax is pure C++, with classes which behave like instructions. 
The assembly-syntax is heavily inspired by MIPS:

```c++
#include "cpu.hpp"
#include "util.hpp"

using test_prog =
        DeclareProgram<
            AddI<int, registers::A, registers::ZERO, 40>,// 0: a = 40
            AddI<int, registers::B, registers::ZERO, 1>, // 1: b = 1
            AddI<int, registers::C, registers::ZERO, 0>, // 2: c = 0
            AddI<int, registers::D, registers::ZERO, 0>, // 3: d = 0
            AddI<int, registers::E, registers::ZERO, 1>, // 4: e = 1
            AddI<int, registers::B, registers::B, 1>,    // 5: b += 1
            AddI<int, registers::C, registers::D, 0>,    // 6: c = d
            AddI<int, registers::D, registers::E, 0>,    // 7: d = e
            Add<registers::E, registers::C, registers::D>,     // 8: e = c + d
            BranchNEqI<int, registers::A, registers::B, 5> // 9: if a != c -> jmp 5
        >;

int main() {
    using registers = Cpu<test_prog>::run;
    registerPrinter<registers>::print();

    return 0;
}
```
