/**
 * @file config.hpp
 * @author paul
 * @date 02.06.20
 * Description here TODO
 */
#ifndef TEMPLATECPU_CONFIG_HPP
#define TEMPLATECPU_CONFIG_HPP

#include "value_list.hpp"
#include "type_list.hpp"

using namespace static_stl::list;

using base_type = int;
using mem_ptr_type = std::size_t;

constexpr auto MEM_SIZE = 512;

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


#endif //TEMPLATECPU_CONFIG_HPP
