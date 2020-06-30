/**
 * @file turing_machine.hpp
 * @author paul
 * @date 30.06.20
 * Description here TODO
 */
#ifndef TEMPLATECPU_TURING_MACHINE_HPP
#define TEMPLATECPU_TURING_MACHINE_HPP

constexpr auto TAPE_SIZE = 16;
constexpr auto STATE_SIZE = 16;
constexpr auto SYMBOL_COUNT = 16;
/*
 * Memory Layout:
 * The first TAPE_SIZE elements are the program (the tape)
 *
 * The next STATE_SIZE * SYMBOL_COUNT elements are the mapping of states and symbols to new symbol,
 * the new state and the head direction (0 is left, 1 is right)
 *
 * For a given state t and a symbol y the values can be calculated as:
 * new_symbol = TAPE_SIZE + SYMBOL_COUNT * state * 3 + symbol * 3 + 0
 * new_state = TAPE_SIZE + SYMBOL_COUNT * state * 3 + symbol * 3 + 1
 * head_direction = TAPE_SIZE + SYMBOL_COUNT * state * 3 + symbol * 3 + 2
 *
 * a is the current state
 * b is the index on the tape
 *
 * c is the value at the current position * 3
 *
 * e is new_symbol
 * f is new_state
 * g is head_direction
 */

static_assert(TAPE_SIZE + SYMBOL_COUNT * STATE_SIZE * 3 <= MEM_SIZE, "Program is to large!");

using turing_machine =
        DeclareProgram<
            Load<Register::C, Register::B>, // 0: c = *b;
            MulI<int, Register::C, Register::C, 3>, // 1: c *= 3;

            // new symbol
            MulI<int, Register::E, Register::A, 3 * SYMBOL_COUNT>, // 2: e = a * 3 * SYMBOL_COUNT
            Add<Register::E, Register::E, Register::C>, // 3: e += c
            AddI<int, Register::E, Register::E, TAPE_SIZE>, // 4: e += TAPE_SIZE
            Store<Register::E, Register::B>, // 5: *e = b CHECK

            // new state
            AddI<int, Register::A, Register::E, 1>, // 6: a = e + 1

            // head_direction
            AddI<int, Register::G, Register::E, 2>, // 7: g = e + 2

            BranchEqI<int, Register::G, Register::ZERO, 10>, // 8: if (g == 0) goto LABEL_1
            JumpI<int, 12>, // 9: else goto LABEL_2

            // Left
            SubI<int, Register::B, Register::B, 1>, // 10 LABEL_1: b -= 1
            JumpI<int, 12>, // 11 goto LABEL_3

            // Right
            AddI<int, Register::B, Register::B, 1>, // 12 LABEL_2: b += 1

            // while true
            JumpI<int, 0>

        >;

#endif //TEMPLATECPU_TURING_MACHINE_HPP
