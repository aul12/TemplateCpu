/**
 * @file instructions.hpp
 * @author paul
 * @date 25.05.20
 * Description here TODO
 */
#ifndef TEMPLATEPROCESSOR_INSTRUCTIONS_HPP
#define TEMPLATEPROCESSOR_INSTRUCTIONS_HPP

#include "cpu_types.hpp"


template<std::size_t res, std::size_t a, std::size_t b>
struct Add {};

template<typename T, std::size_t res, std::size_t a, T b>
struct AddI {};

template<typename T>
struct is_instruction {
    static constexpr bool val = false;
};

template<std::size_t res, std::size_t a, std::size_t b>
struct is_instruction<Add<res, a, b>> {
    static constexpr bool val = true;
};

template<typename T, std::size_t res, std::size_t a, T b>
struct is_instruction<AddI<T, res, a, b>> {
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

template<std::size_t res, std::size_t a, std::size_t b, type_list Registers, std::size_t PC_>
struct InstrImpl<Add<res, a, b>, Registers, PC_> {
    using Reg = typename SetVal<typename Registers::elem::type,
                        Registers,
                        res,
                        GetVal<Registers, a>::val + GetVal<Registers, b>::val
                >::type;
    static constexpr auto PC = PC_ + 1;
};

template<typename T, std::size_t res, std::size_t a, T b, type_list Registers, std::size_t PC_>
struct InstrImpl<AddI<T, res, a, b>, Registers, PC_> {
    using Reg = typename SetVal<typename Registers::elem::type,
                        Registers,
                        res,
                        GetVal<Registers, a>::val + b
                >::type;
    static constexpr auto PC = PC_ + 1;
};

#endif //TEMPLATEPROCESSOR_INSTRUCTIONS_HPP
