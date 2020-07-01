#include "cpu.hpp"
#include "util.hpp"

#include "examples/turing_machine.hpp"

int main() {
    using result = Cpu<turing_machine>::run;
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
