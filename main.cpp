#include "cpu.hpp"
#include "util.hpp"

using test_prog =
        Program<
            AddI<int, 1, 0, 1>,
            BranchEqI<int, 0, 1, 0>
        >;

int main() {
    using registers = Cpu<test_prog, 3>::run;
    registerPrinter<registers>::print();

    return 0;
}
