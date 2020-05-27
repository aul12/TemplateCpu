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

template<prog Program, std::size_t PC_, reg Registers, mem Mem_>
struct ExecuteInstr {
    static constexpr auto PC = InstrImpl<typename GetType<Program, PC_>::type, Registers, Mem_, PC_>::PC;
    using Reg = typename InstrImpl<typename GetType<Program, PC_>::type, Registers, Mem_, PC_>::Reg;
    using Mem = typename InstrImpl<typename GetType<Program, PC_>::type, Registers, Mem_, PC_>::Mem;
};

template<prog Program, std::size_t size, std::size_t PC, reg Reg, mem Mem>
struct CpuState {
    using val = typename CpuState<
                            Program,
                            size,
                            ExecuteInstr<Program, PC, Reg, Mem>::PC,
                            typename ExecuteInstr<Program, PC, Reg, Mem>::Reg,
                            typename ExecuteInstr<Program, PC, Reg, Mem>::Mem
                        >::val;
};

template<prog Program, std::size_t size, reg Reg, mem Mem>
struct CpuState<Program, size, size, Reg, Mem> {
    using val = Reg;
};

template<prog Program>
struct Cpu {
    using run = typename CpuState<
                                Program,
                                Size<Program>::val,
                                0,
                                typename FillVal<static_cast<std::size_t>(Reg::LENGTH), base_type, 0>::type,
                                typename FillVal<MEM_SIZE, base_type, 0>::type
                            >::val;
};

#endif //TEMPLATEPROCESSOR_CPU_HPP
