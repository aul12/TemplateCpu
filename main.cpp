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
            BranchNEqI<int, Register::A, Register::B, 5>, // 9: if a != b -> jmp 5
            StoreI<0, Register::E>
        >;

/*
 * Stack Layout
 * STACK_PTR, RET, ARG, RES1 = FIB(ARG-1), ...
 */
using fib_recursive =
        DeclareProgram<
            // Init
            AddI<int, Register::A, Register::ZERO, 8>,              //0: set max value
            AddI<int, Register::RET, Register::ZERO, 31>,           //1: store last address in RET

            // Check if base
            GreaterI<int, Register::B, Register::A, 2>,             //2: LABEL_0 b = (a > 2)
            BranchNEqI<int, Register::ZERO, Register::B, 5>,        //3: if a > 2 -> jmp LABEL_1
            BranchEqI<int, Register::ZERO, Register::B, 29>,        //4: else -> jmp LABEL_2

            // Build up stack
            Store<Register::STACK_PTR, Register::STACK_PTR>,        //5: LABEL_1 (recursion) push STACK_PTR to stack
            AddI<int, Register::STACK_PTR, Register::STACK_PTR, 1>, //6: Forward stackptr to stack
            Store<Register::STACK_PTR, Register::RET>,              //7: store ret on stack
            AddI<int, Register::STACK_PTR, Register::STACK_PTR, 1>, //8: Forward stackptr to stack
            Store<Register::STACK_PTR, Register::A>,                //9: push a to stack
            AddI<int, Register::STACK_PTR, Register::STACK_PTR, 2>, //10: Forward stackptr to stack by 2

            // Recursion
            AddI<int, Register::A, Register::A, -1>,                //11: a -= 1
            AddI<int, Register::RET, Register::ZERO, 14>,           //12: Store return address
            JumpI<int, 2>,                                          //13: Recursion, jump to LABEL_0, result in e
            AddI<int, Register::B, Register::STACK_PTR, -1>,        //14: b point to RES1
            Store<Register::B, Register::E>,                        //15: Save e to RES1
            AddI<int, Register::B, Register::STACK_PTR, -2>,        //16: b points to ARG on stack
            Load<Register::A, Register::B>,                         //17: load ARG from stack into a
            AddI<int, Register::A, Register::A, -2>,                //18: a -= 2
            AddI<int, Register::RET, Register::ZERO, 21>,           //19: Store return address
            JumpI<int, 2>,                                          //20, recursion, jump to LABEL_0, result in e

            // Final result
            AddI<int, Register::B, Register::STACK_PTR, -1>,        //21: b points to RES1
            Load<Register::C, Register::B>,                         //22: load RES1 into C
            Add<Register::E, Register::E, Register::C>,             //23: e = e + c = fib(a-1) + fib(a-2)

            // Cleanup stack
            AddI<int, Register::B, Register::STACK_PTR, -3>,        //24: b points to RET
            Load<Register::RET, Register::B>,                       //25: Restore RET
            AddI<int, Register::B, Register::STACK_PTR, -4>,        //26: b points to STACK_PTR
            Load<Register::STACK_PTR, Register::B>,                 //27: Restore RET
            JumpI<int, 30>,                                         //28: jmp LABEL_3

            // Base
            AddI<int, Register::E, Register::ZERO, 1>,              //29: LABEL_2: e = 1

            // Return
            Jump<Register::RET>                                     //30: LABEL_3, return
        >;



int main() {
    using result = Cpu<fib_recursive>::run;
    using printer = printer<result::Reg, result::Mem>;

    if constexpr (result::is_breakpoint) {
        std::cout << "Stopped at breakpoint (PC=" << result::PC << ")" << std::endl;
    }

    std::cout << "Executed " << result::instr_count << " instructions\n" << std::endl;
    std::cout << "Registers:" << std::endl;
    printer::reg();

    std::cout << "\nMemory:" << std::endl;
    printer::mem();

    return 0;
}
