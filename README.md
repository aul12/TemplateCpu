# TemplateCpu
Implementing a CPU emulator using C++ Meta Programming with Concepts.

## Syntax
The syntax is pure C++, with classes which behave like instructions. 
The assembly-syntax is heavily inspired by MIPS:

```c++
#include "cpu.hpp"
#include "util.hpp"

using test_prog = // Test Prog is a type which is your program
        Program<
            AddI<int, 1, 0, 1>, // AddImmediate 1 to Reg-1
            Add<2, 0, 1>, // Fibonacci Step 1: Reg2 = Reg0 + Reg1
            Add<3, 1, 2>,
            Add<4, 2, 3>,
            Add<5, 3, 4>,
            Add<6, 4, 5>
        >;

int main() {
    using registers = Cpu<test_prog, 10>::run; // Run the program, with 10 registers. registers is a type with the registers after execution

    registerPrinter<registers>::print(); // Print the register content, this is the only line that actually exists during execution
    return 0;
}

```
