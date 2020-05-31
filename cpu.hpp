/**
 * @file cpu.hpp
 * @author paul
 * @date 25.05.20
 * Description here TODO
 */
#ifndef TEMPLATEPROCESSOR_CPU_HPP
#define TEMPLATEPROCESSOR_CPU_HPP

#include "cpu_types.hpp"
#include "instructions.hpp"

template<Registers registers, Memory memory, std::size_t instr_count_>
struct Result {
    using Reg = registers;
    using Mem = memory;
    static constexpr auto instr_count = instr_count_;
};

template<Program program, std::size_t old_pc, Registers registers, Memory memory>
struct ExecuteInstr {
    static constexpr auto PC = InstrImpl<typename GetType<program, old_pc>::type, registers, memory, old_pc>::PC;
    using Reg = typename InstrImpl<typename GetType<program, old_pc>::type, registers, memory, old_pc>::Reg;
    using Mem = typename InstrImpl<typename GetType<program, old_pc>::type, registers, memory, old_pc>::Mem;
};

template<Program program, std::size_t size, std::size_t PC, Registers registers, Memory memory, std::size_t instr_count>
struct CpuState {
    using val = typename CpuState<
                            program,
                            size,
                            ExecuteInstr<program, PC, registers, memory>::PC,
                            typename ExecuteInstr<program, PC, registers, memory>::Reg,
                            typename ExecuteInstr<program, PC, registers, memory>::Mem,
                            instr_count + 1
                        >::val;
};

template<Program program, std::size_t size, Registers registers, Memory memory, std::size_t instr_count>
struct CpuState<program, size, size, registers, memory, instr_count> {
    using val = Result<registers, memory, instr_count>;
};

template<Program Program>
struct Cpu {
    using run = typename CpuState<
                                Program,
                                Size<Program>::val,
                                0,
                                typename FillVal<static_cast<std::size_t>(Register::LENGTH), base_type, 0>::type,
                                typename FillVal<MEM_SIZE, base_type, 0>::type,
                                0
                            >::val;
};

#endif //TEMPLATEPROCESSOR_CPU_HPP
