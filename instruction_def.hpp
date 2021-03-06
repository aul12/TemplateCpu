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
 * Addition Instruction: the register res is set to the value of the register a plus the value of register b
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct Add {};

/**
 * Addition with immediate Instruction: the register res is set to the value of the register a plus the value b
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct AddI {};

/**
 * Subtraction Instruction: the register res is set to the value of the register a minus the register b
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct Sub {};

/**
 * Subtraction with immediate Instruction: the register res is set to the value of the register a minus the value b
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct SubI {};

/**
 * Multiplication Instruction: the register res is set to the value of the register a times the register b
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct Mul {};

/**
 * Multiplication with immediate Instruction: the register res is set to the value of the register a times the value b
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct MulI {};

/**
 * Division Instruction: the register res is set to the value of the register a divided the register b.
 * If the value of the register b is zero a static_assert is triggered and the execution is stopped.
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct Div {};

/**
 * Division with immediate Instruction: the register res is set to the value of the register a divided by the value b.
 * If the b is zero a static_assert is triggered and the execution is stopped.
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct DivI {};

/**
 * Binary-And Instruction: the register res is set to the value of the binary and of the registers a and b.
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct And {};

/**
 * Binary-And with immediate Instruction: the register res is set to the value of the binary and of the register a and
 * the value b.
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct AndI {};

/**
 * Binary-Or Instruction: the register res is set to the value of the binary or of the registers a and b.
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct Or {};

/**
 * Binary-Or with immediate Instruction: the register res is set to the value of the binary or of the register a and
 * the value b.
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct OrI {};

/**
 * Binary-Exclusive-Or Instruction: the register res is set to the value of the binary xor of the registers a and b.
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct XOr {};

/**
 * Binary-Exclusive Or with immediate Instruction: the register res is set to the value of the binary or of the register
 * a and the value b.
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct XOrI {};

/**
 * Less Instruction: the register res is set to 1 of the value in register a is less than the one in register b.
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct Less {};

/**
 * Less with immediate Instruction: the register res is set to 1 of the value in register a is less than the value b.
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct LessI {};

/**
 * Greater Instruction: the register res is set to 1 of the value in register a is greater than the one in register b.
 * @tparam res result register
 * @tparam a register of first operand
 * @tparam b register of second operand
 */
template<Register res, Register a, Register b>
struct Greater {};

/**
 * Less with immediate Instruction: the register res is set to 1 of the value in register a is greater than the value b.
 * @tparam T the type of b
 * @tparam res the result register
 * @tparam a register of first operand
 * @tparam b value of the second operand
 */
template<typename T, Register res, Register a, T b>
struct GreaterI {};

/**
 * Jump Instruction: sets the program counter to the value in register reg
 * @tparam reg contains the next program counter
 */
template<Register reg>
struct Jump {};

/**
 * Jump with immediate Instruction: jumps to a fixed program counter address given by val
 * @tparam T the type of val
 * @tparam val the next program counter.
 */
template<typename T, T val>
struct JumpI{};

/**
 * Branch on equal Instruction: jumps if the values in register a and b are equal.
 * @tparam a the first operand of the comparison
 * @tparam b the second operand of the comparison
 * @tparam target the register containing the program counter value at which to jump if the values are equal.
 */
template<Register a, Register b, Register target>
struct BranchEq {};

/**
 * Branch on equal with immediate Instruction: jumps if the values in register a and the value b are equal.
 * @tparam T the type of the target program counter
 * @tparam a the first operand of the comparison
 * @tparam b the second operand of the comparison
 * @tparam target the program counter value at which to jump if the values are equal.
 */
template<typename T, Register a, Register b, T target>
struct BranchEqI {};

/**
 * Branch on not-equal Instruction: jumps if the values in register a and b are not equal.
 * @tparam a the first operand of the comparison
 * @tparam b the second operand of the comparison
 * @tparam target the register containing the program counter value at which to jump if the values are not equal.
 */
template<Register a, Register b, Register target>
struct BranchNEq {};

/**
 * Branch on not-equal with immediate Instruction: jumps if the values in register a and the value b are not equal.
 * @tparam T the type of the target program counter
 * @tparam a the first operand of the comparison
 * @tparam b the second operand of the comparison
 * @tparam target the program counter value at which to jump if the values are not equal.
 */
template<typename T, Register a, Register b, T target>
struct BranchNEqI {};

/**
 * Store Instruction: Stores the value from a register into memory.
 * @tparam addr_reg the register containing the address to write to
 * @tparam reg the register containing the value to write
 */
template<Register addr_reg, Register reg>
struct Store {};

/**
 * Store with immediate Instruction: Stores a value from register into memory.
 * @tparam addr the address at which to write
 * @tparam reg the register containing the value
 */
template<mem_ptr_type addr, Register reg>
struct StoreI {};

/**
 * Load Instruction: Loads a value from memory into a register.
 * @tparam reg the register in which to write
 * @tparam addr_reg the register containing the address to read from
 */
template<Register reg, Register addr_reg>
struct Load {};

/**
 * Load with immediate Instruction: Loads a value from memory into a register.
 * @tparam reg the register in which to write
 * @tparam addr_reg the address to read from
 */
template<Register reg, mem_ptr_type addr>
struct LoadI {};

/**
 * Struct used for defining if a type is an Instruction.
 * @tparam T the type to check
 */
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

/**
 * Concept declaring an Instruction, that is one of the types listed above.
 * @tparam T the type to check
 */
template<typename T>
concept Instruction = is_instruction<T>::val;

#endif //TEMPLATE_CPU_INSTRUCTION_DEF_HPP
