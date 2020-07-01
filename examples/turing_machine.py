TAPE_SIZE = 16
STATE_SIZE = 16
SYMBOL_COUNT = 16
mem = [0] * 1024

none = 0
left = 1
right = 2


def set_transition(state, symbol, new_state, new_symbol, direction):
    offset = TAPE_SIZE + SYMBOL_COUNT * state * 3 + symbol * 3
    mem[offset] = new_symbol
    mem[offset + 1] = new_state
    mem[offset + 2] = direction


def print_mem_initialization():
    c = 0
    for a, m in enumerate(mem):
        if m != 0:
            print(f"AddI<int, Register::A, Register::ZERO, {m}>,")
            print(f"StoreI<{a}, Register::A>,")
            c += 2

    print(f"AddI<int, Register::A, Register::ZERO, 0>,")
    print()
    print(f"Offset: {c + 1}")


set_transition(state=0, symbol=0, new_state=1, new_symbol=1, direction=right)
set_transition(state=1, symbol=0, new_state=2, new_symbol=1, direction=right)
set_transition(state=2, symbol=0, new_state=3, new_symbol=1, direction=right)
set_transition(state=3, symbol=0, new_state=0, new_symbol=1, direction=right)

print_mem_initialization()
print()

a_state = b_tape_index = c_value_at_index_x3 = e_new_symbol = f_new_state = g_head_direction = 0

while True:
    c_value_at_index_x3 = mem[b_tape_index]
    c_value_at_index_x3 *= 3
    e_new_symbol = a_state * 3 * SYMBOL_COUNT
    e_new_symbol += c_value_at_index_x3
    e_new_symbol += TAPE_SIZE
    a_state = mem[e_new_symbol + 1]
    g_head_direction = mem[e_new_symbol + 2]
    e_new_symbol = mem[e_new_symbol]
    mem[b_tape_index] = e_new_symbol
    if g_head_direction == 1:
        b_tape_index -= 1
    elif g_head_direction == 2:
        b_tape_index += 1

    print(f"State: {a_state},\t"
          f"Tape Index: {b_tape_index},\t"
          f"Value at Index *3: {c_value_at_index_x3},\t"
          f"New symbol: {e_new_symbol},\t"
          f"New State: {f_new_state},\t"
          f"Head direction: {g_head_direction}")

    if a_state == 0:
        break
