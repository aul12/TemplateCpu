/**
 * @file instructions.hpp
 * @author paul
 * @date 25.05.20
 * Description here TODO
 */
#ifndef TEMPLATEPROCESSOR_INSTRUCTIONS_HPP
#define TEMPLATEPROCESSOR_INSTRUCTIONS_HPP

#include "cpu_types.hpp"
#include "instruction_def.hpp"

template<instruction Instr, Registers Registers, Memory Memory, std::size_t PC_>
struct InstrImpl {};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Add<res, a, b>, registers, memory, old_pc> {
    using Reg = typename SetVal<typename registers::elem::type,
                        registers,
                        static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val + GetVal<registers, static_cast<std::size_t>(b)>::val
                >::type;
    static constexpr auto PC = old_pc + 1;
    using Mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<AddI<T, res, a, b>, registers, memory, old_pc> {
    using Reg = typename SetVal<typename registers::elem::type,
                        registers,
                        static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val + b
                >::type;
    static constexpr auto PC = old_pc + 1;
    using Mem = memory;
};


template<bool cond, std::size_t PC, std::size_t target>
struct GetTarget {
    static constexpr std::size_t val = PC+1;
};

template<std::size_t PC, std::size_t target>
struct GetTarget<true, PC, target> {
    static constexpr std::size_t val = target;
};

template<Register a, Register b, Register target, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<BranchEq<a, b, target>, registers, memory, old_pc> {
    using Reg = registers;
    static constexpr std::size_t PC = GetTarget<
                                    GetVal<registers, static_cast<std::size_t>(a)>::val == GetVal<registers, static_cast<std::size_t>(b)>::val,
                                    old_pc,
                                    GetVal<registers, static_cast<std::size_t>(target)>::val
                                >::val;
    using Mem = memory;
};

template<typename T, Register a, Register b, T target, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<BranchEqI<T, a, b, target>, registers, memory, old_pc> {
    using Reg = registers;
    static constexpr std::size_t PC = GetTarget<
            GetVal<registers, static_cast<std::size_t>(a)>::val == GetVal<registers, static_cast<std::size_t>(b)>::val,
                                    old_pc,
                                    target
                                >::val;
    using Mem = memory;
};

template<Register a, Register b, Register target, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<BranchNEq<a, b, target>, registers, memory, old_pc> {
    using Reg = registers;
    static constexpr std::size_t PC = GetTarget<
            GetVal<registers, static_cast<std::size_t>(a)>::val != GetVal<registers, static_cast<std::size_t>(b)>::val,
            old_pc,
            GetVal<registers, static_cast<std::size_t>(target)>::val
    >::val;
    using Mem = memory;
};

template<typename T, Register a, Register b, T target, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<BranchNEqI<T, a, b, target>, registers, memory, old_pc> {
    using Reg = registers;
    static constexpr std::size_t PC = GetTarget<
            GetVal<registers, static_cast<std::size_t>(a)>::val != GetVal<registers, static_cast<std::size_t>(b)>::val,
            old_pc,
            target
    >::val;
    using Mem = memory;
};

template<std::size_t addr, Register reg, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Store<addr, reg>, registers, memory, old_pc> {
    using Reg = registers;
    static constexpr std::size_t PC = old_pc + 1;
    using Mem = typename SetVal<base_type, memory, addr, GetVal<registers, static_cast<std::size_t>(reg)>::type>::type;
};


// Pseudo instructions
template<Register a, Register b>
using Mov = AddI<base_type, a, b, 0>;


#endif //TEMPLATEPROCESSOR_INSTRUCTIONS_HPP
