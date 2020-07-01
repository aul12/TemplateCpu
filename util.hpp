/**
 * @file util.hpp
 * @author paul
 * @date 25.05.20
 * Definition of utility functions for printing the results of program execution.
 */
#ifndef TEMPLATE_CPU_UTIL_HPP
#define TEMPLATE_CPU_UTIL_HPP

#include <iostream>
#include <iomanip>

#include "config.hpp"

/**
 * Macro for generating a case statement which returns the string representation of the enum value
 */
#define ADD_CASE(a) case Register::a: return #a;

/**
 * Get the string representation of a register.
 * @param reg the register
 * @return a string, with the exact name as the enum value
 */
auto getRegisterName(Register reg) -> std::string {
    switch (reg) {
        ADD_CASE(ZERO)
        ADD_CASE(A)
        ADD_CASE(B)
        ADD_CASE(C)
        ADD_CASE(D)
        ADD_CASE(E)
        ADD_CASE(F)
        ADD_CASE(G)
        ADD_CASE(H)
        ADD_CASE(STACK_PTR)
        ADD_CASE(RET)
        default: return "ERROR";
    }
}

/**
 * Implementation of a compile time loop for printing the registers.
 * @tparam registers the register map
 * @tparam c the index at which to print
 */
template<Registers registers, std::size_t c>
struct registerPrinterImpl {
    static void print() {
        std::cout << getRegisterName(static_cast<Register>(c)) << " (" << c << "):\t" << GetVal<registers, 0>::val << std::endl;
        registerPrinterImpl<typename registers::next, c+1>::print();
    }
};

template<std::size_t c>
struct registerPrinterImpl<ListEnd, c> {
    static void print() {}
};

/**
 * Implementation of a compile time loop for printing the memory
 * @tparam memory the memory
 * @tparam c the index at which to print
 */
template<Memory memory, std::size_t c>
struct memoryPrinterImpl {
    static void print() {
        constexpr auto WORDS_PER_LINE = 16;
        std::cout << std::setw(10) << GetVal<memory, 0>::val;
        if (c % WORDS_PER_LINE == (WORDS_PER_LINE - 1)) {
            std::cout << std::endl;
        }
        memoryPrinterImpl<typename memory::next, c+1>::print();
    }
};

template<std::size_t c>
struct memoryPrinterImpl<ListEnd, c> {
    static void print() {}
};

/**
 * Struct used for printing registers and memory from a program result
 * @tparam registers the registers
 * @tparam memory the memory
 */
template<Registers registers, Memory memory>
struct printer {
    /**
     * Runtime function to printing the registers
     */
    static void reg() {
        registerPrinterImpl<registers, 0>::print();
    }

    /**
     * Runtime function for printing the memory
     */
    static void mem() {
        memoryPrinterImpl<memory, 0>::print();
    }
};


#endif //TEMPLATE_CPU_UTIL_HPP
