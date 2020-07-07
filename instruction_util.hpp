/**
 * @file instruction_util.hpp
 * @author paul
 * @date 04.06.20
 * Definition of utility structs for the implementation of instructions.
 */
#ifndef TEMPLATE_CPU_INSTRUCTION_UTIL_HPP
#define TEMPLATE_CPU_INSTRUCTION_UTIL_HPP

/**
 * Get the next program counter used for conditional jumps.
 * @tparam cond if the bool is false pc+1 is returned, else target is returned
 * @tparam PC the program counter for the if case
 * @tparam target the program counter for the else case
 */
template<bool cond, std::size_t PC, std::size_t target>
struct GetTarget {
    static constexpr std::size_t val = PC+1;
};

/**
 * Specialization for GetTarget if cond==true
 */
template<std::size_t PC, std::size_t target>
struct GetTarget<true, PC, target> {
    static constexpr std::size_t val = target;
};

/**
 * Struct for implementing a division with exception if the result is undefined
 * @tparam T the type of the operands
 * @tparam a the numerator
 * @tparam b the denominator
 */
template<typename T, T a, T b>
struct DivWithException {
    static_assert(b != 0, "Division by zero!");
    static constexpr auto val = a / b;
};


#endif //TEMPLATE_CPU_INSTRUCTION_UTIL_HPP
