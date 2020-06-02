/**
 * @file cpu_types.hpp
 * @author paul
 * @date 25.05.20
 * Description here TODO
 */
#ifndef TEMPLATEPROCESSOR_CPU_TYPES_HPP
#define TEMPLATEPROCESSOR_CPU_TYPES_HPP

#include "config.hpp"

template<typename T>
concept Registers = IsValueList<T>::val && ListOfType<base_type, T>::val;

template<typename T>
concept Memory = IsValueList<T>::val && ListOfType<base_type, T>::val;


#endif //TEMPLATEPROCESSOR_CPU_TYPES_HPP
