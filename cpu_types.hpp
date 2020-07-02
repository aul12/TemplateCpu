/**
 * @file cpu_types.hpp
 * @author paul
 * @date 25.05.20
 * Types used for the cpu
 */
#ifndef TEMPLATE_CPU_CPU_TYPES_HPP
#define TEMPLATE_CPU_CPU_TYPES_HPP

#include "config.hpp"
#include "value_list.hpp"

/**
 * Registers are a value list of base_type type
 * @tparam T the type to check
 */
template<typename T>
concept Registers = IsValueList<T>::val && ListOfType<base_type, T>::val;

/**
 * Memory is a value list of base_type type
 * @tparam T the type to check
 */
template<typename T>
concept Memory = IsValueList<T>::val && ListOfType<base_type, T>::val;

#endif //TEMPLATE_CPU_CPU_TYPES_HPP
