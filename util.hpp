/**
 * @file util.hpp
 * @author paul
 * @date 25.05.20
 * Description here TODO
 */
#ifndef TEMPLATECPU_UTIL_HPP
#define TEMPLATECPU_UTIL_HPP

#include <iostream>
#include <iomanip>

#include "cpu_types.hpp"

#define TO_NAME(a) case Register::a: return #a;

auto getRegisterName(Register reg) -> std::string {
    switch (reg) {
        TO_NAME(ZERO)
        TO_NAME(A)
        TO_NAME(B)
        TO_NAME(C)
        TO_NAME(D)
        TO_NAME(E)
        TO_NAME(STACK_PTR)
        TO_NAME(RET)
        default: return "ERROR";
    }
}

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

template<Memory memory, std::size_t c>
struct memoryPrinterImpl {
    static void print() {
        std::cout << std::setw(10) << GetVal<memory, 0>::val;
        if (c % 8 == 7) {
            std::cout << std::endl;
        }
        memoryPrinterImpl<typename memory::next, c+1>::print();
    }
};

template<std::size_t c>
struct memoryPrinterImpl<ListEnd, c> {
    static void print() {}
};

template<Registers registers, Memory memory>
struct printer {
    static void reg() {
        registerPrinterImpl<registers, 0>::print();
    }

    static void mem() {
        memoryPrinterImpl<memory, 0>::print();
    }
};


#endif //TEMPLATECPU_UTIL_HPP
