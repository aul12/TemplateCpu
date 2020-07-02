/**
 * @file fib_iterative.hpp
 * @author paul
 * @date 30.06.20
 * Implementation of an iterative algorithm for calculating fibonacci numbers, for more details see the README.md
 */
#ifndef TEMPLATECPU_FIB_ITERATIVE_HPP
#define TEMPLATECPU_FIB_ITERATIVE_HPP

using fib_iterative =
        DeclareProgram<
            AddI<int, Register::A, Register::ZERO, 40>,// 0: a = 40
            AddI<int, Register::B, Register::ZERO, 1>, // 1: b = 1
            AddI<int, Register::C, Register::ZERO, 0>, // 2: c = 0
            AddI<int, Register::D, Register::ZERO, 0>, // 3: d = 0
            AddI<int, Register::E, Register::ZERO, 1>, // 4: e = 1
            AddI<int, Register::B, Register::B, 1>,    // 5: b += 1
            Mov<Register::C, Register::D>,             // 6: c = d
            Mov<Register::D, Register::E>,             // 7: d = e
            Add<Register::E, Register::C, Register::D>,// 8: e = c + d
            BranchNEqI<int, Register::A, Register::B, 5>, // 9: if a != b -> jmp 5
            StoreI<0, Register::E>
        >;


#endif //TEMPLATECPU_FIB_ITERATIVE_HPP
