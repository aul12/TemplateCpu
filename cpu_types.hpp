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

template<typename T>
concept reg = IsValueList<T>::val && ListOfType<base_type, T>::val;

template<typename T>
concept prog = IsTypeList<T>::val;

#endif //TEMPLATEPROCESSOR_CPU_TYPES_HPP
