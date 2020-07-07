/**
 * @file TypeList.hpp
 * @author paul
 * @date 25.05.20
 * Header used for the declaration of the type list and all related structs and concepts.
 */
#ifndef TEMPLATE_CPU_TYPE_LIST_HPP
#define TEMPLATE_CPU_TYPE_LIST_HPP

#include <cstddef>
#include <type_traits>

/**
 * Declaration of the type used for elements of a type list, which is a singly linked list.
 * @tparam T the type (i.e. element) at the current position
 * @tparam next_ the next element. Should be of type TypeListElem or ListEnd.
 */
template<typename T, typename next_>
struct TypeListElem {
    using elem = T;
    using next = next_;
};

/**
 * Declaration of the type used for signaling the end of a list, in normal runtime languages a nullptr would be used
 * here.
 */
struct ListEnd {};

// list concepts

/**
 * Struct for specifying if a type is type list, i.e. if it is either a instantiation of TypeListElem or ListEnd.
 * This is the general type which is always false, for the correct types the struct is specialized.
 * @tparam T the type to check
 */
template<typename T>
struct IsTypeList {
    static constexpr bool val = false;
};

/**
 * Specialization of IsTypeList for TypeListElem
 * @see IsTypeList
 * @see TypeListElem
 */
template<typename T, typename next>
struct IsTypeList<TypeListElem<T, next>> {
    static constexpr bool val = true;
};

/**
 * Specialization of IsTypeList for ListEnd
 * @see IsTypeList
 * @see TypeListElem
 */
template<>
struct IsTypeList<ListEnd> {
    static constexpr bool val = true;
};

/**
 * Concept that specifies whether a type is a type list
 * @see IsTypeList
 * @tparam T the type to check
 */
template<typename T>
concept TypeList = IsTypeList<T>::val;

// Helper functions

/**
 * Returns the size / length of the list
 * @tparam list the list to use
 */
template<TypeList list>
struct Size {
    static constexpr std::size_t val = Size<typename list::next>::val + 1;
};

template<>
struct Size<ListEnd> {
    static constexpr std::size_t val = 0;
};

/**
 * Get the type at an index
 * @tparam list the list
 * @tparam index the index needs to be less than the size of the list
 */
template<TypeList list, std::size_t index>
struct GetType {
    static_assert(index < Size<list>::val, "GetType out of bounds");
    using type = typename GetType<typename list::next, index - 1>::type;
};

template<TypeList list>
struct GetType<list, 0> {
    using type = typename list::elem;
};

/**
 * Set the type at an index, a new, modified, list is returned
 * @tparam T the type to insert
 * @tparam list the list in which to insert
 * @tparam index the index at which to insert needs to be less than the size of the list
 */
template<typename T, TypeList list, std::size_t index>
struct SetType {
    static_assert(index < Size<list>::val, "SetType out of bounds");
    using type = TypeListElem<typename list::elem, typename SetType<T, typename list::next, index - 1>::type>;
};

template<typename T, TypeList list>
struct SetType<T, list, 0> {
    using type = TypeListElem<T, typename list::next>;
};

/**
 * Check if an list contains a certain type
 * @tparam T the to find
 * @tparam list the list in which to search
 */
template<typename T, TypeList list>
struct ContainsType {
    static constexpr auto val =
            std::is_same<T, typename list::elem>::value || ContainsType<T, typename list::next>::val;
};

template<typename T>
struct ContainsType<T, ListEnd> {
    static constexpr auto val = false;
};

/**
 * Create a list from a variadic type list.
 * @tparam T the first type
 * @tparam Ts the following types
 */
template<typename T, typename ...Ts>
struct FromVariadicType {
    using type = TypeListElem<T, typename FromVariadicType<Ts...>::type>;
};

template<typename T>
struct FromVariadicType<T> {
    using type = TypeListElem<T, ListEnd>;
};

/**
 * Create a list of a certain length of a certain type.
 * @tparam N the number of elements
 * @tparam T the type to use
 */
template<std::size_t N, typename T>
struct FillType {
    using type = TypeListElem<T, typename FillType<N - 1, T>::type>;
};

template<typename T>
struct FillType<0, T> {
    using type = ListEnd;
};

#endif //TEMPLATE_CPU_TYPE_LIST_HPP
