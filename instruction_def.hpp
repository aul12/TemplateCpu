/**
 * @file instruction_def.hpp
 * @author paul
 * @date 27.05.20
 * Description here TODO
 */
#ifndef TEMPLATECPU_INSTRUCTION_DEF_HPP
#define TEMPLATECPU_INSTRUCTION_DEF_HPP

#include "config.hpp"

template<Register res, Register a, Register b>
struct Add {};

template<typename T, Register res, Register a, T b>
struct AddI {};

template<Register res, Register a, Register b>
struct Sub {};

template<typename T, Register res, Register a, T b>
struct SubI {};

template<Register res, Register a, Register b>
struct Mul {};

template<typename T, Register res, Register a, T b>
struct MulI {};

template<Register res, Register a, Register b>
struct Div {};

template<typename T, Register res, Register a, T b>
struct DivI {};

template<Register res, Register a, Register b>
struct And {};

template<typename T, Register res, Register a, T b>
struct AndI {};

template<Register res, Register a, Register b>
struct Or {};

template<typename T, Register res, Register a, T b>
struct OrI {};

template<Register res, Register a, Register b>
struct XOr {};

template<typename T, Register res, Register a, T b>
struct XOrI {};

template<Register res, Register a, Register b>
struct Less {};

template<typename T, Register res, Register a, T b>
struct LessI {};

template<Register res, Register a, Register b>
struct Greater {};

template<typename T, Register res, Register a, T b>
struct GreaterI {};

template<Register reg>
struct Jump {};

template<typename T, T val>
struct JumpI{};

template<Register a, Register b, Register target>
struct BranchEq {};

template<typename T, Register a, Register b, T target>
struct BranchEqI {};

template<Register a, Register b, Register target>
struct BranchNEq {};

template<typename T, Register a, Register b, T target>
struct BranchNEqI {};

template<Register addr_reg, Register reg>
struct Store {};

template<Register reg, Register addr_reg>
struct Load {};

template<mem_ptr_type addr, Register reg>
struct StoreI {};

template<Register reg, mem_ptr_type addr>
struct LoadI {};

template<typename T>
struct is_instruction {
    static constexpr bool val = false;
};

template<Register res, Register a, Register b>
struct is_instruction<Add<res, a, b>> {
    static constexpr bool val = true;
};

template<typename T, Register res, Register a, T b>
struct is_instruction<AddI<T, res, a, b>> {
    static constexpr bool val = true;
};

template<Register res, Register a, Register b>
struct is_instruction<Sub<res, a, b>> {
    static constexpr bool val = true;
};

template<typename T, Register res, Register a, T b>
struct is_instruction<SubI<T, res, a, b>> {
    static constexpr bool val = true;
};
template<Register res, Register a, Register b>
struct is_instruction<Mul<res, a, b>> {
    static constexpr bool val = true;
};

template<typename T, Register res, Register a, T b>
struct is_instruction<MulI<T, res, a, b>> {
    static constexpr bool val = true;
};

template<Register res, Register a, Register b>
struct is_instruction<Div<res, a, b>> {
    static constexpr bool val = true;
};

template<typename T, Register res, Register a, T b>
struct is_instruction<DivI<T, res, a, b>> {
    static constexpr bool val = true;
};

template<Register res, Register a, Register b>
struct is_instruction<And<res, a, b>> {
    static constexpr bool val = true;
};

template<typename T, Register res, Register a, T b>
struct is_instruction<AndI<T, res, a, b>> {
    static constexpr bool val = true;
};

template<Register res, Register a, Register b>
struct is_instruction<Or<res, a, b>> {
    static constexpr bool val = true;
};

template<typename T, Register res, Register a, T b>
struct is_instruction<OrI<T, res, a, b>> {
    static constexpr bool val = true;
};

template<Register res, Register a, Register b>
struct is_instruction<XOr<res, a, b>> {
    static constexpr bool val = true;
};

template<typename T, Register res, Register a, T b>
struct is_instruction<XOrI<T, res, a, b>> {
    static constexpr bool val = true;
};

template<Register res, Register a, Register b>
struct is_instruction<Less<res, a, b>> {
    static constexpr bool val = true;
};

template<typename T, Register res, Register a, T b>
struct is_instruction<LessI<T, res, a, b>> {
    static constexpr bool val = true;
};

template<Register res, Register a, Register b>
struct is_instruction<Greater<res, a, b>> {
    static constexpr bool val = true;
};

template<typename T, Register res, Register a, T b>
struct is_instruction<GreaterI<T, res, a, b>> {
    static constexpr bool val = true;
};


template<Register a, Register b, Register target>
struct is_instruction<BranchEq<a, b, target>> {
    static constexpr bool val = true;
};

template<typename T, Register a, Register b, T target>
struct is_instruction<BranchEqI<T, a, b, target>> {
    static constexpr bool val = true;
};

template<Register a, Register b, Register target>
struct is_instruction<BranchNEq<a, b, target>> {
    static constexpr bool val = true;
};

template<typename T, Register a, Register b, T target>
struct is_instruction<BranchNEqI<T, a, b, target>> {
    static constexpr bool val = true;
};

template<mem_ptr_type addr, Register reg>
struct is_instruction<StoreI<addr, reg>> {
    static constexpr bool val = true;
};

template<Register reg, mem_ptr_type addr>
struct is_instruction<LoadI<reg, addr>> {
    static constexpr bool val = true;
};

template<Register addr, Register reg>
struct is_instruction<Store<addr, reg>> {
    static constexpr bool val = true;
};

template<Register reg, Register addr>
struct is_instruction<Load<reg, addr>> {
    static constexpr bool val = true;
};

template<Register reg>
struct is_instruction<Jump<reg>> {
    static constexpr bool val = true;
};

template<typename T, T reg>
struct is_instruction<JumpI<T, reg>> {
    static constexpr bool val = true;
};


template<typename T>
concept instruction = is_instruction<T>::val;

#endif //TEMPLATECPU_INSTRUCTION_DEF_HPP
