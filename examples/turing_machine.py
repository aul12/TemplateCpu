TAPE_SIZE = 16
STATE_SIZE = 16
SYMBOL_COUNT = 16
mem = [0] * 1024

a_state = b_tape_index = c_value_at_index_x3 = e_new_symbol = f_new_state = g_head_direction = 0

while True:
    c_value_at_index_x3 = mem[b_tape_index]
    c_value_at_index_x3 *= 3
    e_new_symbol = a_state * 3 * SYMBOL_COUNT
    e_new_symbol += c_value_at_index_x3
    e_new_symbol += TAPE_SIZE
    mem[e_new_symbol] = b_tape_index
    a_state = mem[e_new_symbol + 1]
    g_head_direction = mem[e_new_symbol + 2]
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

    if f_new_state == 0:
        break

