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

template<reg Reg, std::size_t c>
struct registerPrinterImpl {
    static auto print() {
        std::cout << c << ":\t" << GetVal<Reg, 0>::val << std::endl;
        registerPrinterImpl<typename Reg::next, c+1>::print();
    }
};

template<std::size_t c>
struct registerPrinterImpl<ListEnd, c> {
    static auto print() {}
};

template<reg Reg>
struct registerPrinter {
    static auto print() {
        registerPrinterImpl<Reg, 0>::print();
    }
};


#endif //TEMPLATECPU_UTIL_HPP
