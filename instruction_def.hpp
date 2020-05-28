/**
 * @file instruction_def.hpp
 * @author paul
 * @date 27.05.20
 * Description here TODO
 */
#ifndef TEMPLATECPU_INSTRUCTION_DEF_HPP
#define TEMPLATECPU_INSTRUCTION_DEF_HPP

template<Register res, Register a, Register b>
struct Add {};

template<typename T, Register res, Register a, T b>
struct AddI {};

template<Register a, Register b, Register target>
struct BranchEq {};

template<typename T, Register a, Register b, T target>
struct BranchEqI {};

template<Register a, Register b, Register target>
struct BranchNEq {};

template<typename T, Register a, Register b, T target>
struct BranchNEqI {};

template<Register addr_reg, Register reg>
struct Store {};

template<Register reg, Register addr_reg>
struct Load {};

template<mem_ptr_type addr, Register reg>
struct StoreI {};

template<Register reg, mem_ptr_type addr>
struct LoadI {};

template<typename T>
struct is_instruction {
    static constexpr bool val = false;
};

template<Register res, Register a, Register b>
struct is_instruction<Add<res, a, b>> {
    static constexpr bool val = true;
};

template<typename T, Register res, Register a, T b>
struct is_instruction<AddI<T, res, a, b>> {
    static constexpr bool val = true;
};

template<Register a, Register b, Register target>
struct is_instruction<BranchEq<a, b, target>> {
    static constexpr bool val = true;
};

template<typename T, Register a, Register b, T target>
struct is_instruction<BranchEqI<T, a, b, target>> {
    static constexpr bool val = true;
};

template<Register a, Register b, Register target>
struct is_instruction<BranchNEq<a, b, target>> {
    static constexpr bool val = true;
};

template<typename T, Register a, Register b, T target>
struct is_instruction<BranchNEqI<T, a, b, target>> {
    static constexpr bool val = true;
};

template<mem_ptr_type addr, Register reg>
struct is_instruction<StoreI<addr, reg>> {
    static constexpr bool val = true;
};

template<Register reg, mem_ptr_type addr>
struct is_instruction<LoadI<reg, addr>> {
    static constexpr bool val = true;
};

template<typename T>
concept instruction = is_instruction<T>::val;

#endif //TEMPLATECPU_INSTRUCTION_DEF_HPP
