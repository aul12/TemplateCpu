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

template<prog Program, std::size_t PC_, typename Registers>
struct ExecuteInstr {
    using Reg = typename InstrImpl<typename GetType<Program, PC_>::type, Registers, PC_>::Reg;
    static constexpr auto PC = InstrImpl<typename GetType<Program, PC_>::type, Registers, PC_>::PC;
};

template<prog Program, std::size_t size, std::size_t PC, reg Reg>
struct CpuState {
    using val = typename CpuState<
                            Program,
                            size,
                            ExecuteInstr<Program, PC, Reg>::PC,
                            typename ExecuteInstr<Program, PC, Reg>::Reg
                        >::val;
};

template<prog Program, std::size_t size, reg Reg>
struct CpuState<Program, size, size, Reg> {
    using val = Reg;
};

template<prog Program>
struct Cpu {
    using type = typename CpuState<
                                Program,
                                Size<Program>::val,
                                0,
                                FillVal<16, int, 0>::type
                            >::val;
};

#endif //TEMPLATEPROCESSOR_CPU_HPP
