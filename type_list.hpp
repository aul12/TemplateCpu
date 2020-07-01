/**
 * @file type_list.hpp
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
 * @tparam next_ the next element. Should be of type Type or ListEnd.
 */
template<typename T, typename next_>
struct Type {
    using elem = T;
    using next = next_;
};

/**
 * Declaration of the type used for signaling the end of a list, in normal runtime languages a nullptr would be used
 * here.
 */
struct ListEnd {};

// List concepts

/**
 * Struct for specifying if a type is type list, i.e. if it is either a instantiation of Type or ListEnd.
 * This is the general type which is always false, for the correct types the struct is specialized.
 * @tparam T the type to check
 */
template<typename T>
struct IsTypeList {
    static constexpr bool val = false;
};

/**
 * Specialization of IsTypeList for Type
 * @see ISTypeList
 * @see Type
 */
template<typename T, typename next>
struct IsTypeList<Type<T, next>> {
    static constexpr bool val = true;
};

/**
 * Specialization of IsTypeList for ListEnd
 * @see ISTypeList
 * @see Type
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
concept type_list = IsTypeList<T>::val;

// Helper functions

/**
 * Returns the size / length of the list
 * @tparam List the list to use
 */
template<type_list List>
struct Size {
    static constexpr std::size_t val = Size<typename List::next>::val + 1;
};

template<>
struct Size<ListEnd> {
    static constexpr std::size_t val = 0;
};

/**
 * Get the type at an index
 * @tparam List the list
 * @tparam index the index needs to be less than the size of the list
 */
template<type_list List, std::size_t index>
struct GetType {
    static_assert(index < Size<List>::val, "GetType out of bounds");
    using type = typename GetType<typename List::next, index - 1>::type;
};

template<type_list List>
struct GetType<List, 0> {
    using type = typename List::elem;
};

/**
 * Set the type at an index, a new, modified, list is returned
 * @tparam T the type to insert
 * @tparam List the list in which to insert
 * @tparam index the index at which to insert needs to be less than the size of the list
 */
template<typename T, type_list List, std::size_t index>
struct SetType {
    static_assert(index < Size<List>::val, "SetType out of bounds");
    using type = Type<typename List::elem, typename SetType<T, typename List::next, index - 1>::type>;
};

template<typename T, type_list List>
struct SetType<T, List, 0> {
    using type = Type<T, typename List::next>;
};

/**
 * Check if an list contains a certain type
 * @tparam T the to find
 * @tparam List the list in which to search
 */
template<typename T, type_list List>
struct ContainsType {
    static constexpr auto val =
            std::is_same<T, typename List::elem>::value || ContainsType<T, typename List::next>::val;
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
    using type = Type<T, typename FromVariadicType<Ts...>::type>;
};

template<typename T>
struct FromVariadicType<T> {
    using type = Type<T, ListEnd>;
};

/**
 * Create a list of a certain length of a certain type.
 * @tparam N the number of elements
 * @tparam T the type to use
 */
template<std::size_t N, typename T>
struct FillType {
    using type = Type<T, typename FillType<N-1, T>::type>;
};

template<typename T>
struct FillType<0, T> {
    using type = ListEnd;
};

#endif //TEMPLATE_CPU_TYPE_LIST_HPP
