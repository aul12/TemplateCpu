/**
 * @file instructions.hpp
 * @author paul
 * @date 25.05.20
 * Implementation of all instructions.
 */
#ifndef TEMPLATE_CPU_INSTRUCTIONS_HPP
#define TEMPLATE_CPU_INSTRUCTIONS_HPP

#include "cpu_types.hpp"
#include "instruction_def.hpp"
#include "instruction_util.hpp"

/**
 * Struct used for implementing the different instructions
 * @tparam instr the Instruction to execute
 * @tparam registers the registers at the start of the execution
 * @tparam memory the memory at the start of the execution
 * @tparam old_pc the program counter at the start of the execution
 */
template<Instruction instr, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl {};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Add<res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
                        registers,
                        static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val + GetVal<registers, static_cast<std::size_t>(b)>::val
                >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<AddI<T, res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
                        registers,
                        static_cast<std::size_t>(res),
                        GetVal<registers, static_cast<std::size_t>(a)>::val + b
                >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Sub<res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val - GetVal<registers, static_cast<std::size_t>(b)>::val
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<SubI<T, res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val - b
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Mul<res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val * GetVal<registers, static_cast<std::size_t>(b)>::val
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<MulI<T, res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val * b
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Div<res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            DivWithException<base_type, GetVal<registers, static_cast<std::size_t>(a)>::val, GetVal<registers, static_cast<std::size_t>(b)>::val>::val
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<DivI<T, res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            DivWithException<T, GetVal<registers, static_cast<std::size_t>(a)>::val, b>::val
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<And<res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val & GetVal<registers, static_cast<std::size_t>(b)>::val
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<AndI<T, res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val & b
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Or<res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val | GetVal<registers, static_cast<std::size_t>(b)>::val
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<OrI<T, res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val | b
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<XOr<res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val ^ GetVal<registers, static_cast<std::size_t>(b)>::val
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<XOrI<T, res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val ^ b
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Less<res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
                        registers,
                        static_cast<std::size_t>(res),
                        GetVal<registers, static_cast<std::size_t>(a)>::val < GetVal<registers, static_cast<std::size_t>(b)>::val
                    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<LessI<T, res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(a)>::val < b
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<Register res, Register a, Register b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Greater<res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            GetVal<registers, static_cast<std::size_t>(b)>::val < GetVal<registers, static_cast<std::size_t>(a)>::val
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<typename T, Register res, Register a, T b, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<GreaterI<T, res, a, b>, registers, memory, old_pc> {
    using reg = typename SetVal<typename registers::elem::type,
            registers,
            static_cast<std::size_t>(res),
            b < GetVal<registers, static_cast<std::size_t>(a)>::val
    >::type;
    static constexpr auto pc = old_pc + 1;
    using mem = memory;
};

template<Register res, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Jump<res>, registers, memory, old_pc> {
    using reg = registers;
    static constexpr std::size_t pc = GetVal<registers, static_cast<std::size_t>(res)>::val;
    using mem = memory;
};

template<typename T, T val, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<JumpI<T, val>, registers, memory, old_pc> {
    using reg = registers;
    static constexpr std::size_t pc = val;
    using mem = memory;
};

template<Register a, Register b, Register target, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<BranchEq<a, b, target>, registers, memory, old_pc> {
    using reg = registers;
    static constexpr std::size_t pc = GetTarget<
                                    GetVal<registers, static_cast<std::size_t>(a)>::val == GetVal<registers, static_cast<std::size_t>(b)>::val,
                                    old_pc,
                                    GetVal<registers, static_cast<std::size_t>(target)>::val
                                >::val;
    using mem = memory;
};

template<typename T, Register a, Register b, T target, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<BranchEqI<T, a, b, target>, registers, memory, old_pc> {
    using reg = registers;
    static constexpr std::size_t pc = GetTarget<
            GetVal<registers, static_cast<std::size_t>(a)>::val == GetVal<registers, static_cast<std::size_t>(b)>::val,
                                    old_pc,
                                    target
                                >::val;
    using mem = memory;
};

template<Register a, Register b, Register target, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<BranchNEq<a, b, target>, registers, memory, old_pc> {
    using reg = registers;
    static constexpr std::size_t pc = GetTarget<
            GetVal<registers, static_cast<std::size_t>(a)>::val != GetVal<registers, static_cast<std::size_t>(b)>::val,
            old_pc,
            GetVal<registers, static_cast<std::size_t>(target)>::val
    >::val;
    using mem = memory;
};

template<typename T, Register a, Register b, T target, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<BranchNEqI<T, a, b, target>, registers, memory, old_pc> {
    using reg = registers;
    static constexpr std::size_t pc = GetTarget<
            GetVal<registers, static_cast<std::size_t>(a)>::val != GetVal<registers, static_cast<std::size_t>(b)>::val,
            old_pc,
            target
    >::val;
    using mem = memory;
};

template<Register addr_reg, Register data_reg, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Store<addr_reg, data_reg>, registers, memory, old_pc> {
    using reg = registers;
    static constexpr std::size_t pc = old_pc + 1;
    using mem = typename SetVal<
                            base_type,
                            memory,
                            GetVal<registers, static_cast<std::size_t>(addr_reg)>::val,
                            GetVal<registers, static_cast<std::size_t>(data_reg)>::val
                        >::type;
};

template<Register data_reg, Register addr_reg, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<Load<data_reg, addr_reg>, registers, memory, old_pc> {
    using reg = typename SetVal<
                            base_type,
                            registers,
                            static_cast<std::size_t>(data_reg),
                            GetVal<memory,
                                GetVal<registers, static_cast<std::size_t>(addr_reg)>::val
                            >::val
                        >::type;
    static constexpr std::size_t pc = old_pc + 1;
    using mem = memory;
};

template<mem_ptr_type addr, Register data_reg, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<StoreI<addr, data_reg>, registers, memory, old_pc> {
    using reg = registers;
    static constexpr std::size_t pc = old_pc + 1;
    using mem = typename SetVal<base_type, memory, addr, GetVal<registers, static_cast<std::size_t>(data_reg)>::val>::type;
};

template<Register data_reg, mem_ptr_type addr, Registers registers, Memory memory, std::size_t old_pc>
struct InstrImpl<LoadI<data_reg, addr>, registers, memory, old_pc> {
    using reg = typename SetVal<base_type, registers, static_cast<std::size_t>(data_reg), GetVal<memory, addr>::val>::type;
    static constexpr std::size_t pc = old_pc + 1;
    using mem = memory;
};


// Pseudo instructions

/**
 * Pseudo Instruction for copying the value from a register into another.
 * @tparam a the register to copy to
 * @tparam b the register to copy from
 */
template<Register a, Register b>
using Mov = AddI<base_type, a, b, 0>;


#endif //TEMPLATE_CPU_INSTRUCTIONS_HPP
