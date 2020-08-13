/**
 * @file config.hpp
 * @author paul
 * @date 02.06.20
 * Definition of types and parameters of the CPU emulator.
 */
#ifndef TEMPLATE_CPU_CONFIG_HPP
#define TEMPLATE_CPU_CONFIG_HPP

#include <cstddef>

using base_type = int; ///< The type used for registers and memory
using mem_ptr_type = std::size_t; ///< The type used for enumerating addresses in the memory

constexpr auto MEM_SIZE = 1024; ///< Size of the memory

/**
 * Enum used for enumerating the registers
 */
enum class Register {
        ZERO,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        STACK_PTR,
        RET,
        LENGTH
};


#endif //TEMPLATE_CPU_CONFIG_HPP
