/**
 * @file instruction_util.hpp
 * @author paul
 * @date 04.06.20
 * Description here TODO
 */
#ifndef TEMPLATE_CPU_INSTRUCTION_UTIL_HPP
#define TEMPLATE_CPU_INSTRUCTION_UTIL_HPP

template<bool cond, std::size_t PC, std::size_t target>
struct GetTarget {
    static constexpr std::size_t val = PC+1;
};

template<std::size_t PC, std::size_t target>
struct GetTarget<true, PC, target> {
    static constexpr std::size_t val = target;
};

template<typename T, T a, T b>
struct DivWithException {
    static_assert(b != 0, "Division by zero!");
    static constexpr auto val = a / b;
};


#endif //TEMPLATE_CPU_INSTRUCTION_UTIL_HPP
