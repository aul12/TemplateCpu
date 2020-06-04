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
#include "instruction_util.hpp"

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

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Sub<res, a, b>, registers, memory, old_pc> {
    using Reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val - GetVal<registers, static_cast<std::size_t>(b)>::val
    >::type;
    static constexpr auto PC = old_pc + 1;
    using Mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<SubI<T, res, a, b>, registers, memory, old_pc> {
    using Reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val - b
    >::type;
    static constexpr auto PC = old_pc + 1;
    using Mem = memory;
};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Mul<res, a, b>, registers, memory, old_pc> {
    using Reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val * GetVal<registers, static_cast<std::size_t>(b)>::val
    >::type;
    static constexpr auto PC = old_pc + 1;
    using Mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<MulI<T, res, a, b>, registers, memory, old_pc> {
    using Reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val * b
    >::type;
    static constexpr auto PC = old_pc + 1;
    using Mem = memory;
};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Div<res, a, b>, registers, memory, old_pc> {
    using Reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            DivWithException<base_type, GetVal<registers, static_cast<std::size_t>(a)>::val, GetVal<registers, static_cast<std::size_t>(b)>::val>::val
    >::type;
    static constexpr auto PC = old_pc + 1;
    using Mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<DivI<T, res, a, b>, registers, memory, old_pc> {
    using Reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            DivWithException<T, GetVal<registers, static_cast<std::size_t>(a)>::val, b>::val
    >::type;
    static constexpr auto PC = old_pc + 1;
    using Mem = memory;
};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Less<res, a, b>, registers, memory, old_pc> {
    using Reg = typename SetVal<typename registers::elem::type,
                        registers,
                        static_cast<std::size_t>(res),
                        GetVal<registers, static_cast<std::size_t>(a)>::val < GetVal<registers, static_cast<std::size_t>(b)>::val
                    >::type;
    static constexpr auto PC = old_pc + 1;
    using Mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<LessI<T, res, a, b>, registers, memory, old_pc> {
    using Reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val < b
    >::type;
    static constexpr auto PC = old_pc + 1;
    using Mem = memory;
};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Greater<res, a, b>, registers, memory, old_pc> {
    using Reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(b)>::val < GetVal<registers, static_cast<std::size_t>(a)>::val
    >::type;
    static constexpr auto PC = old_pc + 1;
    using Mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<GreaterI<T, res, a, b>, registers, memory, old_pc> {
    using Reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            b < GetVal<registers, static_cast<std::size_t>(a)>::val
    >::type;
    static constexpr auto PC = old_pc + 1;
    using Mem = memory;
};

template<Register res, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Jump<res>, registers, memory, old_pc> {
    using Reg = registers;
    static constexpr std::size_t PC = GetVal<registers, static_cast<std::size_t>(res)>::val;
    using Mem = memory;
};

template<typename T, T val, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<JumpI<T, val>, registers, memory, old_pc> {
    using Reg = registers;
    static constexpr std::size_t PC = val;
    using Mem = memory;
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

template<Register addr_reg, Register reg, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Store<addr_reg, reg>, registers, memory, old_pc> {
    using Reg = registers;
    static constexpr std::size_t PC = old_pc + 1;
    using Mem = typename SetVal<
                            base_type,
                            memory,
                            GetVal<registers, static_cast<std::size_t>(addr_reg)>::val,
                            GetVal<registers, static_cast<std::size_t>(reg)>::val
                        >::type;
};

template<Register reg, Register addr_reg, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Load<reg, addr_reg>, registers, memory, old_pc> {
    using Reg = typename SetVal<
                            base_type,
                            registers,
                            static_cast<std::size_t>(reg),
                            GetVal<memory,
                                GetVal<registers, static_cast<std::size_t>(addr_reg)>::val
                            >::val
                        >::type;
    static constexpr std::size_t PC = old_pc + 1;
    using Mem = memory;
};

template<mem_ptr_type addr, Register reg, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<StoreI<addr, reg>, registers, memory, old_pc> {
    using Reg = registers;
    static constexpr std::size_t PC = old_pc + 1;
    using Mem = typename SetVal<base_type, memory, addr, GetVal<registers, static_cast<std::size_t>(reg)>::val>::type;
};

template<Register reg, mem_ptr_type addr, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<LoadI<reg, addr>, registers, memory, old_pc> {
    using Reg = typename SetVal<base_type, registers, static_cast<std::size_t>(reg), GetVal<memory, addr>::val>::type;
    static constexpr std::size_t PC = old_pc + 1;
    using Mem = memory;
};


// Pseudo instructions
template<Register a, Register b>
using Mov = AddI<base_type, a, b, 0>;


#endif //TEMPLATEPROCESSOR_INSTRUCTIONS_HPP
