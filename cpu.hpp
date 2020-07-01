/**
 * @file cpu.hpp
 * @author paul
 * @date 25.05.20
 * Definition of the structs used for the main emulation loop.
 */
#ifndef TEMPLATE_CPU_CPU_HPP
#define TEMPLATE_CPU_CPU_HPP

#include "instructions.hpp"

/**
 * Concept for a program as an alias for a type list
 * @tparam T the type to check
 */
template<typename T>
concept Program = IsTypeList<T>::val;

/**
 * Alias for declaring a program using a variadic template.
 * @tparam instructions the instructions
 */
template<instruction ... instructions>
using DeclareProgram = typename FromVariadicType<instructions...>::type;

/**
 * Struct containing the results of the execution of a program
 * @tparam registers the registers after execution
 * @tparam memory the memory after execution
 * @tparam PC_ the program counter after execution
 * @tparam instr_count_ the number of instructions executed
 * @tparam breakpoint true if the program was stopped due to a breakpoint
 */
template<Registers registers, Memory memory, std::size_t PC_, std::size_t instr_count_, bool breakpoint>
struct Result {
    using Reg = registers;
    using Mem = memory;
    static constexpr auto PC = PC_;
    static constexpr auto instr_count = instr_count_;
    static constexpr auto is_breakpoint = breakpoint;
};

/**
 * Struct used for fetching the instruction and running the instruction on the current state.
 * @tparam program the program
 * @tparam old_pc the old/current program counter
 * @tparam registers the registers
 * @tparam memory the memory
 */
template<Program program, std::size_t old_pc, Registers registers, Memory memory>
struct ExecuteInstr {
    static constexpr auto PC = InstrImpl<typename GetType<program, old_pc>::type, registers, memory, old_pc>::PC;
    using Reg = typename InstrImpl<typename GetType<program, old_pc>::type, registers, memory, old_pc>::Reg;
    using Mem = typename InstrImpl<typename GetType<program, old_pc>::type, registers, memory, old_pc>::Mem;
};

/**
 * The main struct for running the CPU emulation code.
 * @tparam program the program
 * @tparam size the size of the program (number of instructions)
 * @tparam PC the current program counter
 * @tparam registers the registers
 * @tparam memory the memory
 * @tparam instr_count the number of instructions which have been executed since start
 * @tparam max_instructions the maximum numbers of instructions to run
 */
template<Program program, std::size_t size, std::size_t PC, Registers registers, Memory memory, std::size_t instr_count, std::size_t max_instructions>
struct CpuState {
    using val = typename CpuState<
                            program,
                            size,
                            ExecuteInstr<program, PC, registers, memory>::PC,
                            typename ExecuteInstr<program, PC, registers, memory>::Reg,
                            typename ExecuteInstr<program, PC, registers, memory>::Mem,
                            instr_count + 1,
                            max_instructions
                        >::val;
};

/**
 * Specialization if the program terminates normally
 */
template<Program program, std::size_t size, Registers registers, Memory memory, std::size_t instr_count, std::size_t max_instructions>
struct CpuState<program, size, size, registers, memory, instr_count, max_instructions> {
    using val = Result<registers, memory, size, instr_count, false>;
};

/**
 * Specialization for breakpoints
 */
template<Program program, std::size_t size, std::size_t PC, Registers registers, Memory memory, std::size_t max_instructions>
struct CpuState<program, size, PC, registers, memory, max_instructions, max_instructions> {
    using val = Result<registers, memory, PC, max_instructions, true>;
};

/**
 * Main struct for emulating a program.
 * @tparam program the program
 */
template<Program program>
struct Cpu {
    using run = typename CpuState<
                                program,
                                Size<program>::val,
                                0,
                                typename FillVal<static_cast<std::size_t>(Register::LENGTH), base_type, 0>::type,
                                typename FillVal<MEM_SIZE, base_type, 0>::type,
                                0,
                                static_cast<std::size_t>(-1)
                            >::val;
};

/**
 * Main struct for running a program until a certain number of instructions is executed.
 * @tparam program the program
 * @tparam instructions the number of instructions to run
 */
template<Program program, std::size_t instructions>
struct CpuDebug {
    using run = typename CpuState<
            program,
            Size<program>::val,
            0,
            typename FillVal<static_cast<std::size_t>(Register::LENGTH), base_type, 0>::type,
            typename FillVal<MEM_SIZE, base_type, 0>::type,
            0,
            instructions
    >::val;
};

#endif //TEMPLATE_CPU_CPU_HPP
