/**
 * @file instructions.hpp
 * @author paul
 * @date 25.05.20
 * Description here TODO
 */
#ifndef TEMPLATEPROCESSOR_INSTRUCTIONS_HPP
#define TEMPLATEPROCESSOR_INSTRUCTIONS_HPP

#include "cpu_types.hpp"

template<Reg res, Reg a, Reg b>
struct Add {};

template<typename T, Reg res, Reg a, T b>
struct AddI {};

template<Reg a, Reg b, Reg target>
struct BranchEq {};

template<typename T, Reg a, Reg b, T target>
struct BranchEqI {};

template<Reg a, Reg b, Reg target>
struct BranchNEq {};

template<typename T, Reg a, Reg b, T target>
struct BranchNEqI {};


template<typename T>
struct is_instruction {
    static constexpr bool val = false;
};

template<Reg res, Reg a, Reg b>
struct is_instruction<Add<res, a, b>> {
    static constexpr bool val = true;
};

template<typename T, Reg res, Reg a, T b>
struct is_instruction<AddI<T, res, a, b>> {
    static constexpr bool val = true;
};

template<Reg a, Reg b, Reg target>
struct is_instruction<BranchEq<a, b, target>> {
    static constexpr bool val = true;
};

template<typename T, Reg a, Reg b, T target>
struct is_instruction<BranchEqI<T, a, b, target>> {
    static constexpr bool val = true;
};

template<Reg a, Reg b, Reg target>
struct is_instruction<BranchNEq<a, b, target>> {
    static constexpr bool val = true;
};

template<typename T, Reg a, Reg b, T target>
struct is_instruction<BranchNEqI<T, a, b, target>> {
    static constexpr bool val = true;
};

template<typename T>
concept instruction = is_instruction<T>::val;


// Implementations
template<instruction Instr, type_list Registers, std::size_t PC_>
struct InstrImpl {
    using Reg = Registers;
    static constexpr auto PC = PC_ + 1;
};

template<Reg res, Reg a, Reg b, type_list Registers, std::size_t PC_>
struct InstrImpl<Add<res, a, b>, Registers, PC_> {
    using Reg = typename SetVal<typename Registers::elem::type,
                        Registers,
                        static_cast<std::size_t>(res),
                        GetVal<Registers, static_cast<std::size_t>(a)>::val + GetVal<Registers, static_cast<std::size_t>(b)>::val
                >::type;
    static constexpr auto PC = PC_ + 1;
};

template<typename T, Reg res, Reg a, T b, type_list Registers, std::size_t PC_>
struct InstrImpl<AddI<T, res, a, b>, Registers, PC_> {
    using Reg = typename SetVal<typename Registers::elem::type,
                        Registers,
                        static_cast<std::size_t>(res),
                        GetVal<Registers, static_cast<std::size_t>(a)>::val + b
                >::type;
    static constexpr auto PC = PC_ + 1;
};


template<bool cond, std::size_t PC_, std::size_t target>
struct GetTarget {
    static constexpr std::size_t val = PC_+1;
};

template<std::size_t PC_, std::size_t target>
struct GetTarget<true, PC_, target> {
    static constexpr std::size_t val = target;
};

template<Reg a, Reg b, Reg target, type_list Register, std::size_t PC_>
struct InstrImpl<BranchEq<a, b, target>, Register, PC_> {
    using Reg = Register;
    static constexpr std::size_t PC = GetTarget<
                                    GetVal<Register, static_cast<std::size_t>(a)>::val == GetVal<Register, static_cast<std::size_t>(b)>::val,
                                    PC_,
                                    GetVal<Register, static_cast<std::size_t>(target)>::val
                                >::val;
};

template<typename T, Reg a, Reg b, T target, type_list Register, std::size_t PC_>
struct InstrImpl<BranchEqI<T, a, b, target>, Register, PC_> {
    using Reg = Register;
    static constexpr std::size_t PC = GetTarget<
                                    GetVal<Register, static_cast<std::size_t>(a)>::val == GetVal<Register, static_cast<std::size_t>(b)>::val,
                                    PC_,
                                    target
                                >::val;
};

template<Reg a, Reg b, Reg target, type_list Register, std::size_t PC_>
struct InstrImpl<BranchNEq<a, b, target>, Register, PC_> {
    using Reg = Register;
    static constexpr std::size_t PC = GetTarget<
            GetVal<Register, static_cast<std::size_t>(a)>::val != GetVal<Register, static_cast<std::size_t>(b)>::val,
            PC_,
            GetVal<Register, static_cast<std::size_t>(target)>::val
    >::val;
};

template<typename T, Reg a, Reg b, T target, type_list Register, std::size_t PC_>
struct InstrImpl<BranchNEqI<T, a, b, target>, Register, PC_> {
    using Reg = Register;
    static constexpr std::size_t PC = GetTarget<
            GetVal<Register, static_cast<std::size_t>(a)>::val != GetVal<Register, static_cast<std::size_t>(b)>::val,
            PC_,
            target
    >::val;
};

#endif //TEMPLATEPROCESSOR_INSTRUCTIONS_HPP
