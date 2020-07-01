/**
 * @file type_list.hpp
 * @author paul
 * @date 25.05.20
 * Description here TODO
 */
#ifndef TEMPLATE_CPU_TYPE_LIST_HPP
#define TEMPLATE_CPU_TYPE_LIST_HPP

#include <cstddef>

template<typename T, typename next_>
struct Type {
    using elem = T;
    using next = next_;
};

struct ListEnd {};

// List concepts
template<typename T>
struct IsTypeList {
    static constexpr bool val = false;
};

template<typename T, typename next>
struct IsTypeList<Type<T, next>> {
    static constexpr bool val = true;
};

template<>
struct IsTypeList<ListEnd> {
    static constexpr bool val = true;
};

template<typename T>
concept type_list = IsTypeList<T>::val;

template<type_list List>
struct Size {
    static constexpr std::size_t val = Size<typename List::next>::val + 1;
};

template<>
struct Size<ListEnd> {
    static constexpr std::size_t val = 0;
};

template<type_list List, std::size_t index>
struct GetType {
    static_assert(index < Size<List>::val, "Set out of bounds");
    using type = typename GetType<typename List::next, index - 1>::type;
};

template<type_list List>
struct GetType<List, 0> {
    using type = typename List::elem;
};

template<typename toAdd, type_list List>
struct PrependType {
    using type = Type<toAdd, List>;
};

template<typename T, type_list List, std::size_t index>
struct SetType {
    static_assert(index < Size<List>::val, "Set out of bounds");
    using type = Type<typename List::elem, typename SetType<T, typename List::next, index - 1>::type>;
};

template<typename T, type_list List>
struct SetType<T, List, 0> {
    using type = Type<T, typename List::next>;
};

template<typename T, type_list List>
struct ContainsType {
    static constexpr auto val = std::is_same<T, typename List::elem>::value || ContainsType<T, typename List::next>::val;
};

template<typename T>
struct ContainsType<T, ListEnd> {
    static constexpr auto val = false;
};

template<type_list List, std::size_t steps>
struct ReverseImpl {
    using type = typename PrependType<
                                        typename GetType<
                                                List,
                                                Size<List>::val-1
                                        >::type,
                                        typename ReverseImpl<List, steps-1>::type
                                    >::type;
};

template<type_list List>
struct ReverseImpl<List, 0> {
    using type = List;
};

template<type_list List>
struct Reverse {
    using type = typename ReverseImpl<List, Size<List>::val/2>::type;
};


template<typename T, typename ...Ts>
struct FromVariadicType {
    using type = Type<T, typename FromVariadicType<Ts...>::type>;
};

template<typename T>
struct FromVariadicType<T> {
    using type = Type<T, ListEnd>;
};

template<std::size_t N, typename T>
struct FillType {
    using type = Type<T, typename FillType<N-1, T>::type>;
};

template<typename T>
struct FillType<0, T> {
    using type = ListEnd;
};

#endif //TEMPLATE_CPU_TYPE_LIST_HPP
