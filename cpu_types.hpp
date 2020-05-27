/**
 * @file cpu_types.hpp
 * @author paul
 * @date 25.05.20
 * Description here TODO
 */
#ifndef TEMPLATEPROCESSOR_CPU_TYPES_HPP
#define TEMPLATEPROCESSOR_CPU_TYPES_HPP

#include "value_list.hpp"
#include "type_list.hpp"

using namespace static_stl::list;

using base_type = int;
constexpr auto MEM_SIZE = 128;

enum class Reg {
        ZERO,
        A,
        B,
        C,
        D,
        E,
        LENGTH
};

template<typename T>
concept reg = IsValueList<T>::val && ListOfType<base_type, T>::val;

template<typename T>
concept mem = IsValueList<T>::val && ListOfType<base_type, T>::val;

template<typename T>
concept prog = IsTypeList<T>::val;

template<typename...T>
using Program = typename FromVariadicType<T...>::type;


#endif //TEMPLATEPROCESSOR_CPU_TYPES_HPP
