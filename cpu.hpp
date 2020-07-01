/**
 * @file cpu.hpp
 * @author paul
 * @date 25.05.20
 * Description here TODO
 */
#ifndef TEMPLATE_CPU_CPU_HPP
#define TEMPLATE_CPU_CPU_HPP

#include "instructions.hpp"

template<typename T>
concept Program = IsTypeList<T>::val;

template<instruction ... instructions>
using DeclareProgram = typename FromVariadicType<instructions...>::type;


template<Registers registers, Memory memory, std::size_t PC_, std::size_t instr_count_, bool breakpoint>
struct Result {
    using Reg = registers;
    using Mem = memory;
    static constexpr auto PC = PC_;
    static constexpr auto instr_count = instr_count_;
    static constexpr auto is_breakpoint = breakpoint;
};

template<Program program, std::size_t old_pc, Registers registers, Memory memory>
struct ExecuteInstr {
    static constexpr auto PC = InstrImpl<typename GetType<program, old_pc>::type, registers, memory, old_pc>::PC;
    using Reg = typename InstrImpl<typename GetType<program, old_pc>::type, registers, memory, old_pc>::Reg;
    using Mem = typename InstrImpl<typename GetType<program, old_pc>::type, registers, memory, old_pc>::Mem;
};

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

template<Program program, std::size_t size, Registers registers, Memory memory, std::size_t instr_count, std::size_t max_instructions>
struct CpuState<program, size, size, registers, memory, instr_count, max_instructions> {
    using val = Result<registers, memory, size, instr_count, false>;
};

template<Program program, std::size_t size, std::size_t PC, Registers registers, Memory memory, std::size_t max_instructions>
struct CpuState<program, size, PC, registers, memory, max_instructions, max_instructions> {
    using val = Result<registers, memory, PC, max_instructions, true>;
};

template<Program Program>
struct Cpu {
    using run = typename CpuState<
                                Program,
                                Size<Program>::val,
                                0,
                                typename FillVal<static_cast<std::size_t>(Register::LENGTH), base_type, 0>::type,
                                typename FillVal<MEM_SIZE, base_type, 0>::type,
                                0,
                                static_cast<std::size_t>(-1)
                            >::val;
};

template<Program Program, std::size_t instructions>
struct CpuDebug {
    using run = typename CpuState<
            Program,
            Size<Program>::val,
            0,
            typename FillVal<static_cast<std::size_t>(Register::LENGTH), base_type, 0>::type,
            typename FillVal<MEM_SIZE, base_type, 0>::type,
            0,
            instructions
    >::val;
};

#endif //TEMPLATE_CPU_CPU_HPP
