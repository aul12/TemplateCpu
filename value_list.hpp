/**
 * @file ValueList.hpp
 * @author paul
 * @date 25.05.20
 * Header related to the value list and all related structs and concepts.
 */
#ifndef TEMPLATE_CPU_VALUE_LIST_HPP
#define TEMPLATE_CPU_VALUE_LIST_HPP

#include "type_list.hpp"

/**
 * Container used to wrap a value into a type.
 * @tparam T the type of the value
 * @tparam val_ the value
 */
template<typename T, T val_>
struct ValueContainer {
    using type = T;
    static constexpr auto val = val_;
};

// Concepts

/**
 * Struct to check if a type is a value_container
 * @tparam T the type ti check
 */
template<typename T>
struct IsValueContainer {
    static constexpr auto val = false;
};

template<typename T, T val_>
struct IsValueContainer<ValueContainer<T, val_>> {
    static constexpr auto val = true;
};

/**
 * Check if a type is a value list, that is a type list with elements which are value containers.
 * @tparam T the type to check
 */
template<TypeList T>
struct IsValueList {
    static constexpr auto val = IsValueContainer<typename T::elem>::val && IsValueList<typename T::next>::val;
};

template<>
struct IsValueList<ListEnd> {
    static constexpr auto val = true;
};

/**
 * Concept for the definition of a value list based on IsValueList
 * @tparam T the type to check
 */
template<typename T>
concept ValueList = IsValueList<T>::val;

/**
 * Check if a value list is of a certain type (i.e. all types in the value containers are of the certain type).
 * @tparam T the type to check
 * @tparam list the list to check
 */
template<typename T, ValueList list>
struct ListOfType {
    static constexpr auto val =
            std::is_same<T, typename list::elem::type>::value && ListOfType<T, typename list::next>::val;
};

template<typename T>
struct ListOfType<T, ListEnd> {
    static constexpr auto val = true;
};

/**
 * Concept to check if a value list of type.
 * @tparam T the type
 * @tparam list the list
 */
template<typename T, typename list>
concept value_list_of_type = ListOfType<T, list>::val;


// Helper functions

/**
 * Get the value at a certain index in a ValueList
 * @tparam list the list
 * @tparam index the index needs to be less than the size of the list
 */
template<ValueList list, std::size_t index>
struct GetVal {
    static constexpr auto val = GetType<list, index>::type::val;
};

/**
 * Set a value inside a value list. This will return a new list with the changed value.
 * @tparam T the type of the new value
 * @tparam list the list on which to work
 * @tparam index the index at which to change
 * @tparam val the new value
 */
template<typename T, ValueList list, std::size_t index, T val> requires value_list_of_type<T, list>
struct SetVal {
    using type = typename SetType<ValueContainer<T, val>, list, index>::type;
};

/**
 * Check if value list contains a value. Be careful, the types need to be identical as well. For example
 * 0 of type int is not equal to 0 of type short, long, char, unsigned, float, double...
 * @tparam T the type of the value
 * @tparam val_ the value to find
 * @tparam list the list
 */
template<typename T, T val_, ValueList list>
struct ContainsVal {
    static constexpr auto val = ContainsType<ValueContainer<T, val_>, list>::val;
};

/**
 * Create a value list of a single type of a variadic list of values.
 * @tparam T the type to use
 * @tparam t the first value
 * @tparam ts the other values
 */
template<typename T, T t, T... ts>
struct FromVariadicVal {
    using type = TypeListElem<ValueContainer<T, t>, typename FromVariadicVal<T, ts...>::type>;
};

template<typename T, T t>
struct FromVariadicVal<T, t> {
    using type = TypeListElem<ValueContainer<T, t>, ListEnd>;
};

/**
 * Fill a value list with N values of a fixed type
 * @tparam N the number of elements
 * @tparam T the type of the elements
 * @tparam t the value of the elements
 */
template<std::size_t N, typename T, T t>
struct FillVal {
    using type = typename FillType<N, ValueContainer<T, t>>::type;
};

#endif //TEMPLATE_CPU_VALUE_LIST_HPP
