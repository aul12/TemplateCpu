#include "cpu.hpp"
#include "util.hpp"

using fib_iterative =
        DeclareProgram<
            AddI<int, Register::A, Register::ZERO, 40>,// 0: a = 40
            AddI<int, Register::B, Register::ZERO, 1>, // 1: b = 1
            AddI<int, Register::C, Register::ZERO, 0>, // 2: c = 0
            AddI<int, Register::D, Register::ZERO, 0>, // 3: d = 0
            AddI<int, Register::E, Register::ZERO, 1>, // 4: e = 1
            AddI<int, Register::B, Register::B, 1>,    // 5: b += 1
            Mov<Register::C, Register::D>,             // 6: c = d
            Mov<Register::D, Register::E>,             // 7: d = e
            Add<Register::E, Register::C, Register::D>,// 8: e = c + d
            BranchNEqI<int, Register::A, Register::B, 5>, // 9: if a != c -> jmp 5
            StoreI<0, Register::E>
        >;

/*
 * Stack Layout
 * STACK_PTR, RET, ARG, RES1 = FIB(ARG-1), ...
 */

using fib_recursive =
        DeclareProgram<
            // Init
            AddI<int, Register::A, Register::ZERO, 2>, // a = 40

            // Check if base
            GreaterI<int, Register::B, Register::A, 3>, // b = (a > 3)
            BranchEqI<int, Register::ZERO, Register::B, 0>, // if a > 3 -> jmp LABEL_1 TODO
            BranchNEqI<int, Register::ZERO, Register::B, 0>, // else -> jmp LABEL_2 TODO

            // Build up stack
            Store<Register::STACK_PTR, Register::STACK_PTR>, // LABEL_1 (recursion) push STACK_PTR to stack
            AddI<int, Register::STACK_PTR, Register::STACK_PTR, 1>, // Forward stackptr to stack
            Store<Register::STACK_PTR, Register::RET>, // store ret on stack
            AddI<int, Register::STACK_PTR, Register::STACK_PTR, 1>, // Forward stackptr to stack
            Store<Register::STACK_PTR, Register::A>, // push a to stack
            AddI<int, Register::STACK_PTR, Register::STACK_PTR, 2>, // Forward stackptr to stack by 2

            // Recursion
            AddI<int, Register::A, Register::A, -1>, // a -= 1
            AddI<int, Register::RET, Register::ZERO, 0>, // Store return address TODO
            JumpI<int, 1>, // Recursion, jump to 1, result in e
            AddI<int, Register::B, Register::STACK_PTR, -1>, // b point to RES1
            Store<Register::B, Register::E>, // Save e to RES1
            AddI<int, Register::B, Register::STACK_PTR, -2>, // b points to ARG on stack
            Load<Register::A, Register::B>, // load ARG from stack into a
            AddI<int, Register::A, Register::A, -2>, // a -= 2
            AddI<int, Register::RET, Register::ZERO, 0>, // Store return address TODO
            JumpI<int, 1>, // Recursion, jump to 1, result in e

            // Final result
            AddI<int, Register::B, Register::STACK_PTR, -1>, // b points to RES1
            Load<Register::C, Register::B>, // load RES1 into C
            Add<Register::E, Register::E, Register::C>, // e = e + c = fib(a-1) + fib(a-2)

            // Cleanup stack
            AddI<int, Register::B, Register::STACK_PTR, -3>, // b points to RET
            Load<Register::RET, Register::B>, // Restore RET
            AddI<int, Register::B, Register::STACK_PTR, -4>, // b points to STACK_PTR
            Load<Register::STACK_PTR, Register::B>, // Restore RET
            JumpI<int, 0>, // jmp LABEL_3 TODO

            // Base
            AddI<int, Register::E, Register::ZERO, 1>, // LABEL_2: e = 1

            Jump<Register::RET> // LABEL 3, return
        >;



int main() {
    using result = Cpu<fib_iterative>::run;
    using printer = printer<result::Reg, result::Mem>;

    std::cout << "Registers:" << std::endl;
    printer::reg();

    std::cout << "\nMemory:" << std::endl;
    printer::mem();

    return 0;
}
