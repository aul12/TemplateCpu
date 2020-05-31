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
            AddI<int, Register::A, Register::ZERO, 2>, //0: a = 2

            // Check if base
            GreaterI<int, Register::B, Register::A, 3>, //1: b = (a > 3)
            BranchEqI<int, Register::ZERO, Register::B, 4>, //2: if a > 3 -> jmp LABEL_1
            BranchNEqI<int, Register::ZERO, Register::B, 28>, //3: else -> jmp LABEL_2

            // Build up stack
            Store<Register::STACK_PTR, Register::STACK_PTR>, //4: LABEL_1 (recursion) push STACK_PTR to stack
            AddI<int, Register::STACK_PTR, Register::STACK_PTR, 1>, //5: Forward stackptr to stack
            Store<Register::STACK_PTR, Register::RET>, //6: store ret on stack
            AddI<int, Register::STACK_PTR, Register::STACK_PTR, 1>, //7: Forward stackptr to stack
            Store<Register::STACK_PTR, Register::A>, //8: push a to stack
            AddI<int, Register::STACK_PTR, Register::STACK_PTR, 2>, //9: Forward stackptr to stack by 2

            // Recursion
            AddI<int, Register::A, Register::A, -1>, //10: a -= 1
            AddI<int, Register::RET, Register::ZERO, 13>, //11: Store return address
            JumpI<int, 1>, //12: Recursion, jump to 1, result in e
            AddI<int, Register::B, Register::STACK_PTR, -1>, //13: b point to RES1
            Store<Register::B, Register::E>, //14: Save e to RES1
            AddI<int, Register::B, Register::STACK_PTR, -2>, //15: b points to ARG on stack
            Load<Register::A, Register::B>, //16: load ARG from stack into a
            AddI<int, Register::A, Register::A, -2>, //17: a -= 2
            AddI<int, Register::RET, Register::ZERO, 20>, //18: Store return address
            JumpI<int, 1>, //19: Recursion, jump to 1, result in e

            // Final result
            AddI<int, Register::B, Register::STACK_PTR, -1>, //20: b points to RES1
            Load<Register::C, Register::B>, //21: load RES1 into C
            Add<Register::E, Register::E, Register::C>, //22: e = e + c = fib(a-1) + fib(a-2)

            // Cleanup stack
            AddI<int, Register::B, Register::STACK_PTR, -3>, //23: b points to RET
            Load<Register::RET, Register::B>, //24: Restore RET
            AddI<int, Register::B, Register::STACK_PTR, -4>, //25: b points to STACK_PTR
            Load<Register::STACK_PTR, Register::B>, //26: Restore RET
            JumpI<int, 29>, //27: jmp LABEL_3

            // Base
            AddI<int, Register::E, Register::ZERO, 1>, //28: LABEL_2: e = 1

            Jump<Register::RET> //29: LABEL 3, return
        >;



int main() {
    using result = Cpu<fib_recursive>::run;
    using printer = printer<result::Reg, result::Mem>;

    if constexpr (result::is_breakpoint) {
        std::cout << "Stopped at breakpoint (PC=" << result::PC << ")" << std::endl;
    }

    std::cout << "Exectuted " << result::instr_count << " instructions\n" << std::endl;
    std::cout << "Registers:" << std::endl;
    printer::reg();

    std::cout << "\nMemory:" << std::endl;
    printer::mem();

    return 0;
}
