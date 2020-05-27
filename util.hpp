/**
 * @file util.hpp
 * @author paul
 * @date 25.05.20
 * Description here TODO
 */
#ifndef TEMPLATECPU_UTIL_HPP
#define TEMPLATECPU_UTIL_HPP

#include <iostream>

#include "cpu_types.hpp"

template<Registers registers, std::size_t c>
struct registerPrinterImpl {
    static auto print() {
        std::cout << c << ":\t" << GetVal<registers, 0>::val << std::endl;
        registerPrinterImpl<typename registers::next, c+1>::print();
    }
};

template<std::size_t c>
struct registerPrinterImpl<ListEnd, c> {
    static auto print() {}
};

template<Registers registers>
struct registerPrinter {
    static auto print() {
        registerPrinterImpl<registers, 0>::print();
    }
};


#endif //TEMPLATECPU_UTIL_HPP
