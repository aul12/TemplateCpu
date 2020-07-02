/**
 * @file turing_machine.hpp
 * @author paul
 * @date 30.06.20
 * Implementation of a turing machine in template assembly.
 *
 * Memory Layout:
 * The first TAPE_SIZE elements are the program (the tape)
 *
 * The next STATE_SIZE * SYMBOL_COUNT elements are the mapping of states and symbols to new symbol,
 * the new state and the head direction (0 is no movement, 1 is left, 2 is right)
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
 * g is head_direction (0: none, 1: left, 2: right)
 *
 * if the next state is 0 the program terminates.
 *
 * See: turing_machine.py for the same code in python (slightly more readable). Additionally the python code can
 * generate the correct memory initialization instructions and offset for the code.
 */
#ifndef TEMPLATECPU_TURING_MACHINE_HPP
#define TEMPLATECPU_TURING_MACHINE_HPP

constexpr auto TAPE_SIZE = 16;
constexpr auto STATE_SIZE = 16;
constexpr auto SYMBOL_COUNT = 16;

static_assert(TAPE_SIZE + SYMBOL_COUNT * STATE_SIZE * 3 <= MEM_SIZE, "Program is to large!");

constexpr auto OFFSET = 23; // Generated from python script

using turing_machine =
        DeclareProgram<
            // Memory initialization see turing_machine.py for the code for generating this initialization
            AddI<int, Register::A, Register::ZERO, 1>,
            StoreI<16, Register::A>,
            AddI<int, Register::A, Register::ZERO, 1>,
            StoreI<17, Register::A>,
            AddI<int, Register::A, Register::ZERO, 2>,
            StoreI<18, Register::A>,
            AddI<int, Register::A, Register::ZERO, 1>,
            StoreI<64, Register::A>,
            AddI<int, Register::A, Register::ZERO, 2>,
            StoreI<65, Register::A>,
            AddI<int, Register::A, Register::ZERO, 2>,
            StoreI<66, Register::A>,
            AddI<int, Register::A, Register::ZERO, 1>,
            StoreI<112, Register::A>,
            AddI<int, Register::A, Register::ZERO, 3>,
            StoreI<113, Register::A>,
            AddI<int, Register::A, Register::ZERO, 2>,
            StoreI<114, Register::A>,
            AddI<int, Register::A, Register::ZERO, 1>,
            StoreI<160, Register::A>,
            AddI<int, Register::A, Register::ZERO, 2>,
            StoreI<162, Register::A>,
            AddI<int, Register::A, Register::ZERO, 0>,

            // Turing machine implementation
            Load<Register::C, Register::B>,                          // 0: c = *b;
            MulI<int, Register::C, Register::C, 3>,                  // 1: c *= 3;

            // Offset calculation
            MulI<int, Register::E, Register::A, 3 * SYMBOL_COUNT>,   // 2: e = a * 3 * SYMBOL_COUNT
            Add<Register::E, Register::E, Register::C>,              // 3: e += c
            AddI<int, Register::E, Register::E, TAPE_SIZE>,          // 4: e += TAPE_SIZE

            // new state
            AddI<int, Register::A, Register::E, 1>,                  // 5: a = e + 1
            Load<Register::A, Register::A>,                          // 6: a = *a

            // head_direction
            AddI<int, Register::G, Register::E, 2>,                  // 7: g = e + 2
            Load<Register::G, Register::G>,                          // 8: g = *g

            // New symbol
            Load<Register::E, Register::E>,                          // 9: e = *e
            Store<Register::B, Register::E>,                         // 10: *b = e;

            // Head control
            BranchEqI<int, Register::G, Register::ZERO, 18+OFFSET>,  // 11: if (g == 0) goto LABEL_3
            LessI<int, Register::G, Register::G, 2>,                 // 12: g = g < 2 (<=> dir == 1)
            BranchNEqI<int, Register::G, Register::ZERO, 15+OFFSET>, // 13: if (g != 0) goto LABEL_1 (<=> dir == 1)
            JumpI<int, 17+OFFSET>,                                   // 14: else goto LABEL_2

            // Left
            SubI<int, Register::B, Register::B, 1>,                  // 15: LABEL_1: b -= 1
            JumpI<int, 18+OFFSET>,                                   // 16: goto LABEL_3

            // Right
            AddI<int, Register::B, Register::B, 1>,                   // 17: LABEL_2: b += 1

            BranchEqI<int, Register::A, Register::ZERO, 20+OFFSET>,   // 18: LABEL_3 if (a == 0) break

            // while true
            JumpI<int, 0+OFFSET>                                      // 19: goto 0

        >;

#endif //TEMPLATECPU_TURING_MACHINE_HPP
