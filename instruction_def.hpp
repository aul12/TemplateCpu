/**
 * @file instruction_def.hpp
 * @author paul
 * @date 27.05.20
 * Declaration of the instructions and the corresponding concept.
 */
#ifndef TEMPLATE_CPU_INSTRUCTION_DEF_HPP
#define TEMPLATE_CPU_INSTRUCTION_DEF_HPP

#include "config.hpp"

/**
 * Addition instruction: the register res is set to the value of the register a plus the value of register b
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct Add {};

/**
 * Addition with immediate instruction: the register res is set to the value of the register a plus the value b
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct AddI {};

/**
 * Subtraction instruction: the register res is set to the value of the register a minus the register b
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct Sub {};

/**
 * Subtraction with immediate instruction: the register res is set to the value of the register a minus the value b
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct SubI {};

/**
 * Multiplication instruction: the register res is set to the value of the register a times the register b
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct Mul {};

/**
 * Multiplication with immediate instruction: the register res is set to the value of the register a times the value b
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct MulI {};

/**
 * Division instruction: the register res is set to the value of the register a divided the register b.
 * If the value of the register b is zero a static_assert is triggered and the execution is stopped.
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct Div {};

/**
 * Division with immediate instruction: the register res is set to the value of the register a divided by the value b.
 * If the b is zero a static_assert is triggered and the execution is stopped.
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct DivI {};

/**
 * Binary-And instruction: the register res is set to the value of the binary and of the registers a and b.
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct And {};

/**
 * Binary-And with immediate instruction: the register res is set to the value of the binary and of the register a and
 * the value b.
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct AndI {};

/**
 * Binary-Or instruction: the register res is set to the value of the binary or of the registers a and b.
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct Or {};

/**
 * Binary-Or with immediate instruction: the register res is set to the value of the binary or of the register a and
 * the value b.
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct OrI {};

/**
 * Binary-Exclusive-Or instruction: the register res is set to the value of the binary xor of the registers a and b.
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct XOr {};

/**
 * Binary-Exclusive Or with immediate instruction: the register res is set to the value of the binary or of the register
 * a and the value b.
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
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

#endif //TEMPLATE_CPU_INSTRUCTION_DEF_HPP
