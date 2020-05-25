/**
 * @file value_list.hpp
 * @author paul
 * @date 25.05.20
 * Description here TODO
 */
#ifndef TEMPLATEPROCESSOR_VALUE_LIST_HPP
#define TEMPLATEPROCESSOR_VALUE_LIST_HPP

#include "type_list.hpp"

namespace static_stl::list {
    template<typename T, T val_>
    struct ValueContainer {
        using type = T;
        static constexpr auto val = val_;
    };

    template<typename T>
    struct IsValueContainer {
        static constexpr auto val = false;
    };

    template<typename T, T val_>
    struct IsValueContainer<ValueContainer<T, val_>> {
        static constexpr auto val = true;
    };

    template<typename T>
    concept value_container = IsValueContainer<T>::val;

    template<type_list T>
    struct IsValueList {
        static constexpr auto val = IsValueContainer<typename T::elem>::val && IsValueList<typename T::next>::val;
    };

    template<>
    struct IsValueList<ListEnd> {
        static constexpr auto val = true;
    };

    template<typename T>
    concept value_list = IsValueList<T>::val;

    template<typename T, value_list List>
    struct ListOfType {
        static constexpr auto val = std::is_same<T, typename List::elem::type>::value && ListOfType<T, typename List::next>::val;
    };

    template<typename T>
    struct ListOfType<T, ListEnd> {
        static constexpr auto val = true;
    };

    template<typename T, typename List>
    concept value_list_of_type = ListOfType<T, List>::val;


    // Helper functions
    template<value_list List, std::size_t index>
    struct GetVal {
        static constexpr auto val = GetType<List, index>::type::val;
    };

    template<typename T, type_list List, T val>
    struct PrependVal {
        using type = typename PrependType<ValueContainer<T, val>, List>::type;
    };

    template<typename T, type_list List, std::size_t index, T val> requires value_list_of_type<T, List>
    struct SetVal {
        using type = typename SetType<ValueContainer<T, val>, List, index>::type;
    };

    template<typename T, T t, T... ts>
    struct FromVariadicVal {
        using type = Type<ValueContainer<T, t>, typename FromVariadicVal<T, ts...>::type>;
    };

    template<typename T, T t>
    struct FromVariadicVal<T, t> {
        using type = Type<ValueContainer<T, t>, ListEnd>;
    };

    template<std::size_t N, typename T, T t>
    struct FillVal {
        using type = typename FillType<N, ValueContainer<T, t>>::type;
    };
}

#endif //TEMPLATEPROCESSOR_VALUE_LIST_HPP
